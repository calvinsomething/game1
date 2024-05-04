#include "Shader.h"

// Static Definitions
ID3D11Device *Shader::pDevice;
ID3D11DeviceContext *Shader::pCtx;

Shader::Shader(Graphics &gfx, const wchar_t *file_name)
#ifndef NDEBUG
    : debug(gfx.debug)
#endif
{
    THROW_IF_FAILED(D3DReadFileToBlob(file_name, pByteCode.GetAddressOf()));
};

const void *Shader::GetByteCode()
{
    return pByteCode->GetBufferPointer();
}

unsigned long long Shader::GetByteCodeSize()
{
    return pByteCode->GetBufferSize();
}
