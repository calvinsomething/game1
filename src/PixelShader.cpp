#include "PixelShader.h"

PixelShader::PixelShader(const wchar_t *file_name) : Shader(file_name)
{
    GFX_DEBUG(pDevice->CreatePixelShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                         reinterpret_cast<ID3D11PixelShader **>(pDxShader.GetAddressOf())));
}

PixelShader::PixelShader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers)
    : Shader(file_name, std::move(constant_buffers))
{
    GFX_DEBUG(pDevice->CreatePixelShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                         reinterpret_cast<ID3D11PixelShader **>(pDxShader.GetAddressOf())));
};

void PixelShader::Bind()
{
    pCtx->PSSetShader(reinterpret_cast<ID3D11PixelShader *>(pDxShader.Get()), nullptr, 0);
    CHECK_ERRORS();

    pCtx->PSSetConstantBuffers(0, dx_constant_buffers.size(), dx_constant_buffers.data());
    CHECK_ERRORS();
}
