#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
  public:
    PixelShader(const wchar_t *file_name);
    PixelShader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers);

    void Bind() override;
};
