#pragma once

#include "pch.h"

#include "GfxDebug.h"
#include "Graphics.h"

class Shader
{
    friend class Graphics;

  protected:
    Microsoft::WRL::ComPtr<ID3DBlob> pByteCode;
    Microsoft::WRL::ComPtr<IUnknown> pDxShader;

    static ID3D11Device *pDevice;
    static ID3D11DeviceContext *pCtx;
#ifndef NDEBUG
    GfxDebug &debug;
#endif
  public:
    Shader(Graphics &gfx, const wchar_t *file_name);
    // virtual ~Shader() = default;

    virtual void Bind() = 0;

    const void *GetByteCode();
    unsigned long long GetByteCodeSize();
};
