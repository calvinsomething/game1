#pragma once

#include "pch.h"

#include "structs.h"

#ifndef NDEBUG
#include "GfxDebug.h"
#endif

class Graphics
{
    friend class Buffer;
    friend class Shader;

    Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> pCtx;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;

#ifndef NDEBUG
    GfxDebug debug;
#endif

  public:
    Graphics(HWND hWnd);
    ~Graphics();
    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    void Clear(Color<float> color);
    void EndFrame();
    void DrawCube();
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
        debug.SetIndex();                                                                                              \
        HRESULT hr = fn;                                                                                               \
        if (FAILED(hr))                                                                                                \
        {                                                                                                              \
            throw debug.GetException(hr, __FILE__, __LINE__);                                                          \
        }                                                                                                              \
    }
#define CHECK_ERRORS() debug.CheckErrors(__FILE__, __LINE__)

#endif
