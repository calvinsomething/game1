#include "Graphics.h"

#include "Window.h"

// Exception Handling
#define THROW_IF_DEVICE_REMOVED(fn)                                                                                    \
    {                                                                                                                  \
        HRESULT hr = fn;                                                                                               \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            if (hr == DXGI_ERROR_DEVICE_REMOVED)                                                                       \
            {                                                                                                          \
                hr = pDevice->GetDeviceRemovedReason();                                                                \
            }                                                                                                          \
            throw get_windows_exception(hr, __FILE__, __LINE__);                                                       \
        }                                                                                                              \
    }

#ifdef NDEBUG
#define CHECK_ERRORS()

#else
#undef THROW_IF_FAILED
#define THROW_IF_FAILED(fn)                                                                                            \
    {                                                                                                                  \
        debug.SetIndex();                                                                                              \
        HRESULT hr = fn;                                                                                               \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            throw debug.GetException(hr, __FILE__, __LINE__);                                                          \
        }                                                                                                              \
    }
#define CHECK_ERRORS() debug.CheckErrors(__FILE__, __LINE__)

#endif

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

void Graphics::Clear(Color color)
{
    color.alpha = 1;
    pCtx->ClearRenderTargetView(pTarget.Get(), reinterpret_cast<float *>(&color));
}

void Graphics::EndFrame()
{
    THROW_IF_DEVICE_REMOVED(pSwapChain->Present(1, 0));
}

void Graphics::DrawTriangle()
{
    using namespace Microsoft::WRL;

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Vertex vertices[] = {{0.0f, 0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {-0.5f, -0.5f, 0.0f, 1.0f}};

    ComPtr<ID3D11Buffer> pVertexBuffer;
    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth = sizeof(vertices);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = vertices;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pVertexBuffer.GetAddressOf()));

    unsigned stride = sizeof(Vertex), offset = 0;
    pCtx->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);

    ComPtr<ID3DBlob> pBlob;

    ComPtr<ID3D11VertexShader> pVertexShader;
    THROW_IF_FAILED(D3DReadFileToBlob(L"shaders/vertex.cso", pBlob.GetAddressOf()));
    THROW_IF_FAILED(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr,
                                                pVertexShader.GetAddressOf()));
    pCtx->VSSetShader(pVertexShader.Get(), nullptr, 0);

    ComPtr<ID3D11InputLayout> pInputLayout;
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    pDevice->CreateInputLayout(ied, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), pInputLayout.GetAddressOf());
    pCtx->IASetInputLayout(pInputLayout.Get());

    pCtx->IASetInputLayout(pInputLayout.Get());
    ComPtr<ID3D11PixelShader> pPixelShader;
    THROW_IF_FAILED(D3DReadFileToBlob(L"shaders/pixel.cso", pBlob.ReleaseAndGetAddressOf()));
    THROW_IF_FAILED(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr,
                                               pPixelShader.GetAddressOf()));
    pCtx->PSSetShader(pPixelShader.Get(), nullptr, 0);

    pCtx->OMSetRenderTargets(1, pTarget.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    pCtx->RSSetViewports(1, &vp);

    pCtx->Draw(3, 0);
    CHECK_ERRORS();
}
