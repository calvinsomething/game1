#pragma once

#include "Buffer.h"

class IndexBuffer : public Buffer
{
  public:
    IndexBuffer(Graphics &gfx, unsigned *indices, unsigned byte_width);
};
