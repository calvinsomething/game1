#include "Graphics.h"

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Window.h"

namespace dx = DirectX;

// Graphics
Graphics::Graphics(HWND hWnd)
{
    using namespace Microsoft::WRL;

    DXGI_SWAP_CHAIN_DESC scd{};

    scd.BufferDesc.Width = 0;
    scd.BufferDesc.Height = 0;
    scd.BufferDesc.RefreshRate.Numerator = 0;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hWnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = 0;

    unsigned create_device_flags = 0;
#ifndef NDEBUG
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    THROW_IF_FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, create_device_flags,
                                                  nullptr, 0, D3D11_SDK_VERSION, &scd, pSwapChain.GetAddressOf(),
                                                  pDevice.GetAddressOf(), nullptr, pCtx.GetAddressOf()));

    ComPtr<ID3D11Resource> pSurface;

    THROW_IF_FAILED(
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void **>(pSurface.GetAddressOf())));

    THROW_IF_FAILED(pDevice->CreateRenderTargetView(pSurface.Get(), nullptr, pTarget.GetAddressOf()));
}

Graphics::~Graphics()
{
}

void Graphics::Clear(Color<float> color)
{
    color.a = 1;
    pCtx->ClearRenderTargetView(pTarget.Get(), reinterpret_cast<float *>(&color));
}

void Graphics::EndFrame()
{
    THROW_IF_DEVICE_REMOVED(pSwapChain->Present(1, 0));
}

void Graphics::DrawCube()
{
    using namespace Microsoft::WRL;

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Vec4 vertices[] = {
        {-1, 1, -1, 1}, {1, 1, -1, 1}, {1, -1, -1, 1}, {-1, -1, -1, 1},
        {-1, 1, 1, 1},  {1, 1, 1, 1},  {1, -1, 1, 1},  {-1, -1, 1, 1},
    };

    unsigned indices[] = {5, 4, 7, 7, 6, 5, 4, 5, 1, 1, 0, 4, 1, 5, 6, 6, 2, 1,
                          4, 0, 3, 3, 7, 4, 3, 2, 6, 6, 7, 3, 0, 1, 2, 2, 3, 0};

    IndexBuffer ib{*this, indices, sizeof(indices)};
    pCtx->IASetIndexBuffer(ib.get_dx_addr(), DXGI_FORMAT_R32_UINT, 0);

    VertexBuffer vb{*this, vertices, sizeof(vertices)};
    unsigned stride = sizeof(vertices[0]), offset = 0;
    ID3D11Buffer *vertex_buffers[] = {vb.get_dx_addr()};
    pCtx->IASetVertexBuffers(0, 1, vertex_buffers, &stride, &offset);

    // vertex shader
    ComPtr<ID3DBlob> pBlob;

    ComPtr<ID3D11VertexShader> pVertexShader;
    THROW_IF_FAILED(D3DReadFileToBlob(L"shaders/vertex.cso", pBlob.GetAddressOf()));
    THROW_IF_FAILED(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr,
                                                pVertexShader.GetAddressOf()));
    pCtx->VSSetShader(pVertexShader.Get(), nullptr, 0);

    // vertex buffer input layout
    ComPtr<ID3D11InputLayout> pInputLayout;
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    pDevice->CreateInputLayout(ied, std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(),
                               pInputLayout.GetAddressOf());
    pCtx->IASetInputLayout(pInputLayout.Get());

    // vs constant buffer
    dx::XMMATRIX transform =
        dx::XMMatrixMultiplyTranspose(dx::XMMatrixRotationX(0.3) * dx::XMMatrixRotationY(0.5),
                                      dx::XMMatrixTranslation(0, 0, 7) * dx::XMMatrixPerspectiveLH(1, 0.75, 1, 10));

    ConstantBuffer<D3D11_USAGE_DYNAMIC> vsTransform = {*this, &transform, sizeof(transform)};
    ID3D11Buffer *vs_c_buffers[] = {vsTransform.get_dx_addr()};
    pCtx->VSSetConstantBuffers(0, 1, vs_c_buffers);

    // pixel shader
    ComPtr<ID3D11PixelShader> pPixelShader;
    THROW_IF_FAILED(D3DReadFileToBlob(L"shaders/pixel.cso", pBlob.ReleaseAndGetAddressOf()));
    THROW_IF_FAILED(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr,
                                               pPixelShader.GetAddressOf()));
    pCtx->PSSetShader(pPixelShader.Get(), nullptr, 0);

    // ps constant buffer
    Color<float> face_colors[] = {
        {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {0, 1, 0}, {1, 1, 0}, {0, 1, 1},
    };

    ConstantBuffer<D3D11_USAGE_DEFAULT> psColors = {*this, &face_colors, sizeof(face_colors)};
    ID3D11Buffer *ps_c_buffers[] = {psColors.get_dx_addr()};
    pCtx->PSSetConstantBuffers(0, 1, ps_c_buffers);

    pCtx->OMSetRenderTargets(1, pTarget.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    pCtx->RSSetViewports(1, &vp);

    pCtx->DrawIndexed(std::size(indices), 0, 0);
    CHECK_ERRORS();
}
