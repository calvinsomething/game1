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

  protected:
    static ID3D11Device *pDevice;
    static ID3D11DeviceContext *pCtx;

    struct GlobalData
    {
        DirectX::XMMATRIX tf_view_proj;
        uint32_t light_count;
        DirectX::XMVECTOR light_positions[4];
    };

    static const GlobalData &get_global_data();

  private:
    static DirectX::XMMATRIX tf_projection;
    static DirectX::XMMATRIX tf_camera;

    static GlobalData global_data;
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

    void SetLightCount(size_t count);
    void SetLightPosition(size_t i, DirectX::XMVECTOR position);

    void Clear(Color<float> color);
    void EndFrame();
};
