#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
  public:
    PixelShader(Graphics &gfx, const wchar_t *file_name);

    void Bind() override;
};
