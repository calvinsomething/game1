#include "PixelShader.h"

PixelShader::PixelShader(Graphics &gfx, const wchar_t *file_name) : Shader(gfx, file_name)
{
    THROW_IF_FAILED(
        Shader::pDevice->CreatePixelShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                           reinterpret_cast<ID3D11PixelShader **>(pDxShader.GetAddressOf())));
}

void PixelShader::Bind()
{
    Shader::pCtx->PSSetShader(reinterpret_cast<ID3D11PixelShader *>(pDxShader.Get()), nullptr, 0);
}
