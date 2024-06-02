#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
  public:
    VertexShader(const wchar_t *file_name);
    VertexShader(const wchar_t *file_name, std::vector<ConstantBuffer> &&constant_buffers);

    void Bind() override;
};
