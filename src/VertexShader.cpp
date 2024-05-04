#include "VertexShader.h"

VertexShader::VertexShader(Graphics &gfx, const wchar_t *file_name) : Shader(gfx, file_name)
{
    THROW_IF_FAILED(
        Shader::pDevice->CreateVertexShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                            reinterpret_cast<ID3D11VertexShader **>(pDxShader.GetAddressOf())));
}

void VertexShader::Bind()
{
    Shader::pCtx->VSSetShader(reinterpret_cast<ID3D11VertexShader *>(pDxShader.Get()), nullptr, 0);
}
