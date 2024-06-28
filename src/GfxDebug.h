#pragma once

#include "dxgidebug.h"

#include "Exception.h"

class GfxDebug
{
    Microsoft::WRL::ComPtr<IDXGIInfoQueue> pInfoQueue;
    char info_desc[512];

    bool GetAllMessages();
    void GetDebugMessage();

    unsigned long long msg_index;
    unsigned info_desc_index;
    bool full;

  public:
    GfxDebug();

    void SetIndex();
    void Clear();
    Exception GetException(unsigned error_code, const char *file, unsigned line);
    void CheckErrors(const char *file, unsigned line);
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
#define GFX_DEBUG(fn) fn

#else
#define GFX_DEBUG(fn)                                                                                                  \
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
