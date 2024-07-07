#pragma once

#include "pch.h"

#include "structs.h"

#ifndef NDEBUG
#include "GfxDebug.h"
extern GfxDebug gfxDebug;
#endif

class GfxAccess
{
    friend class Camera;
    friend class Graphics;

    static DirectX::XMMATRIX ProjectionMatrix;
    static DirectX::XMMATRIX ViewProjectionMatrix;

  protected:
    static ID3D11Device *pDevice;
    static ID3D11DeviceContext *pCtx;

    DirectX::XMMATRIX ToNDCSpace(DirectX::XMMATRIX mat);
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

    void Clear(Color<float> color);
    void EndFrame();
};
