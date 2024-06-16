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

// Exception Handling
#ifndef THROW_IF_DEVICE_REMOVED
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
#endif

#ifdef NDEBUG
#define CHECK_ERRORS()

#else
#undef THROW_IF_FAILED
#define THROW_IF_FAILED(fn)                                                                                            \
    {                                                                                                                  \
        gfxDebug.SetIndex();                                                                                           \
        HRESULT hr = fn;                                                                                               \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            throw gfxDebug.GetException(hr, __FILE__, __LINE__);                                                       \
        }                                                                                                              \
    }
#define CHECK_ERRORS() gfxDebug.CheckErrors(__FILE__, __LINE__)

#endif
