#pragma once

#include "Buffer.h"

class IndexBuffer : public Buffer
{
  public:
    IndexBuffer(Graphics &gfx, const unsigned *indices, unsigned byte_width);
};
