#pragma once

#include "Buffer.h"

class VertexBuffer : public Buffer
{
  public:
    VertexBuffer(Graphics &gfx, Vec4 *vertices, unsigned byte_width);
};
