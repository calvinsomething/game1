#include "Shader.h"

Shader::Shader(const wchar_t *file_name)
{
    THROW_IF_FAILED(D3DReadFileToBlob(file_name, pByteCode.GetAddressOf()));
};

Shader::Shader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers)
    : constant_buffers(std::move(constant_buffers))
{
    THROW_IF_FAILED(D3DReadFileToBlob(file_name, pByteCode.GetAddressOf()));

    dx_constant_buffers.reserve(this->constant_buffers.size());
    for (auto &cb : this->constant_buffers)
    {
        dx_constant_buffers.push_back(cb.GetBuffer());
    }
};
