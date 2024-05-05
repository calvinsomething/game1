#pragma once

#include "Buffer.h"

template <D3D11_USAGE U> class ConstantBuffer : public Buffer
{
  public:
    ConstantBuffer(Graphics &gfx) : Buffer(gfx)
    {
        // defer resource creation
    }
    ConstantBuffer(Graphics &gfx, void *data, unsigned byte_width) : Buffer(gfx)
    {
        Init(data, byte_width);
    }

    D3D11_BUFFER_DESC create_buffer_desc(unsigned byte_width);

    void Init(void *data, unsigned byte_width)
    {
        D3D11_BUFFER_DESC bd = create_buffer_desc(byte_width);

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = data;

        THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
    }
};
