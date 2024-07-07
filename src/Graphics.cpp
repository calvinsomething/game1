#include "Graphics.h"

// needed for THROW_IF_DEVICE_REMOVED
#include "Window.h"

namespace dx = DirectX;

// GfxAccess
ID3D11Device *GfxAccess::pDevice = nullptr;
ID3D11DeviceContext *GfxAccess::pCtx = nullptr;
dx::XMMATRIX GfxAccess::ProjectionMatrix = dx::XMMatrixPerspectiveLH(1.0f, 0.75f, 1.0f, 80.0f);
dx::XMMATRIX GfxAccess::ViewProjectionMatrix;

dx::XMMATRIX GfxAccess::ToNDCSpace(dx::XMMATRIX mat)
{
    return dx::XMMatrixMultiplyTranspose(mat, ViewProjectionMatrix);
}

// Graphics
Graphics::Graphics(HWND hWnd)
{
    using namespace Microsoft::WRL;

    DXGI_SWAP_CHAIN_DESC scd{};

    // scd.BufferDesc.Width = 0;
    // scd.BufferDesc.Height = 0;
    // scd.BufferDesc.RefreshRate.Numerator = 0;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    // scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hWnd;
    scd.Windowed = TRUE;
    // TODO Should use below... need to find out why it crashes.
    // scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = 0;

    unsigned create_device_flags = 0;
#ifndef NDEBUG
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    GFX_DEBUG(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, create_device_flags, nullptr, 0,
                                            D3D11_SDK_VERSION, &scd, pSwapChain.GetAddressOf(), pDevice.GetAddressOf(),
                                            nullptr, pCtx.GetAddressOf()));

    ComPtr<ID3D11Resource> pSurface;

    GFX_DEBUG(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void **>(pSurface.GetAddressOf())));

    GFX_DEBUG(pDevice->CreateRenderTargetView(pSurface.Get(), nullptr, pTarget.GetAddressOf()));

    GfxAccess::pDevice = pDevice.Get();
    GfxAccess::pCtx = pCtx.Get();

    D3D11_DEPTH_STENCIL_DESC dsd = {};
    dsd.DepthEnable = TRUE;
    dsd.DepthFunc = D3D11_COMPARISON_LESS;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pStencilState;
    GFX_DEBUG(pDevice->CreateDepthStencilState(&dsd, pStencilState.GetAddressOf()));

    pCtx->OMSetDepthStencilState(pStencilState.Get(), 0);
    CHECK_ERRORS();

    // fill scd with width/height values
    THROW_IF_FAILED(pSwapChain->GetDesc(&scd));

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_D32_FLOAT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    td.SampleDesc.Count = 1;
    td.SampleDesc.Quality = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pStencil;
    GFX_DEBUG(pDevice->CreateTexture2D(&td, nullptr, pStencil.GetAddressOf()));

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
    dsvd.Format = DXGI_FORMAT_D32_FLOAT;
    dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsvd.Texture2D = {};

    GFX_DEBUG(pDevice->CreateDepthStencilView(pStencil.Get(), &dsvd, pStencilView.GetAddressOf()));

    // set render target
    pCtx->OMSetRenderTargets(1, pTarget.GetAddressOf(), pStencilView.Get());
    CHECK_ERRORS();

    // set viewport
    D3D11_VIEWPORT vp;
    vp.Width = scd.BufferDesc.Width;
    vp.Height = scd.BufferDesc.Height;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;

    pCtx->RSSetViewports(1, &vp);
    CHECK_ERRORS();
}

Graphics::~Graphics()
{
}

void Graphics::Clear(Color<float> color)
{
    color.a = 1;
    pCtx->ClearRenderTargetView(pTarget.Get(), reinterpret_cast<float *>(&color));
    pCtx->ClearDepthStencilView(pStencilView.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Graphics::EndFrame()
{
    THROW_IF_DEVICE_REMOVED(pSwapChain->Present(1, 0));
}
