#pragma once

#include "Buffer.h"

class VertexBuffer : public Buffer
{
  public:
    VertexBuffer(Graphics &gfx, const Vec4 *vertices, unsigned byte_width);
};
