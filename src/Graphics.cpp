#include "Graphics.h"

#include "Window.h"

namespace dx = DirectX;

// Static definitions
ID3D11Device *GfxAccess::pDevice = nullptr;
ID3D11DeviceContext *GfxAccess::pCtx = nullptr;

// Graphics
Graphics::Graphics(HWND hWnd) : ProjectionMatrix(dx::XMMatrixPerspectiveLH(1, 0.75, 1, 50))
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

    GfxAccess::pDevice = pDevice.Get();
    GfxAccess::pCtx = pCtx.Get();

    // set render target
    pCtx->OMSetRenderTargets(1, pTarget.GetAddressOf(), nullptr);

    // set viewport
    D3D11_VIEWPORT vp;
    vp.Width = 800;
    vp.Height = 600;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    pCtx->RSSetViewports(1, &vp);
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
