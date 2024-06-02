#pragma once

#include "Buffer.h"

#include "pch.h"

class IndexBuffer : public Buffer
{
    bool initialized;

  public:
    IndexBuffer();
    IndexBuffer(const unsigned *indices, size_t byte_width);
    void Init(const unsigned *indices, size_t byte_width);

    void Bind() override;
};
