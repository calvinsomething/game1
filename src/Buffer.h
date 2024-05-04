#pragma once

#include "Graphics.h"

class Buffer
{
  public:
    Buffer(Graphics &gfx)
        : pDevice(gfx.pDevice.Get()), pCtx(gfx.pCtx.Get())
#ifndef NDEBUG
          ,
          debug(gfx.debug)
#endif
              {};

    ID3D11Buffer *GetDxBuffer()
    {
        return pBuffer.Get();
    }

  protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;

    ID3D11Device *pDevice;
    ID3D11DeviceContext *pCtx;
#ifndef NDEBUG
    GfxDebug &debug;
#endif
};
