#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
  public:
    VertexShader(Graphics &gfx, const wchar_t *file_name);

    void Bind() override;
};
