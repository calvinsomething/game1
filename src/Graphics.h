#pragma once

#include "pch.h"

#include "structs.h"

#ifndef NDEBUG
#include "GfxDebug.h"
extern GfxDebug gfxDebug;
#endif

class GfxAccess
{
    friend class Graphics;

  protected:
    static ID3D11Device *pDevice;
    static ID3D11DeviceContext *pCtx;
};

class Graphics
{
    Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> pCtx;

    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pStencilView;

  public:
    Graphics(HWND hWnd);
    ~Graphics();
    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    DirectX::XMMATRIX ProjectionMatrix;

    void Clear(Color<float> color);
    void EndFrame();
};
