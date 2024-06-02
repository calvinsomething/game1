#include "VertexShader.h"

VertexShader::VertexShader(const wchar_t *file_name) : Shader(file_name)
{
    THROW_IF_FAILED(pDevice->CreateVertexShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                                reinterpret_cast<ID3D11VertexShader **>(pDxShader.GetAddressOf())));
}

VertexShader::VertexShader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers)
    : Shader(file_name, std::move(constant_buffers))
{
    THROW_IF_FAILED(pDevice->CreateVertexShader(pByteCode->GetBufferPointer(), pByteCode->GetBufferSize(), nullptr,
                                                reinterpret_cast<ID3D11VertexShader **>(pDxShader.GetAddressOf())));
};

void VertexShader::Bind()
{
    pCtx->VSSetShader(reinterpret_cast<ID3D11VertexShader *>(pDxShader.Get()), nullptr, 0);
    CHECK_ERRORS();

    pCtx->VSSetConstantBuffers(0, dx_constant_buffers.size(), dx_constant_buffers.data());
    CHECK_ERRORS();

    pCtx->IASetInputLayout(pInputLayout.Get());
    CHECK_ERRORS();
}
