#pragma once

#include "Graphics.h"

class ConstantBuffer : private GfxAccess
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;

  public:
    ConstantBuffer(size_t byte_width);

    template <typename T> ConstantBuffer(const T &input)
    {
        D3D11_BUFFER_DESC bd = {};
        bd.ByteWidth = sizeof(input);
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.Usage = D3D11_USAGE_DEFAULT;

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = &input;

        THROW_IF_FAILED(pDevice->CreateBuffer(&bd, &sd, pBuffer.GetAddressOf()));
    }

    template <typename T> void Update(const T &input)
    {
        D3D11_MAPPED_SUBRESOURCE msr{};
        THROW_IF_FAILED(pCtx->Map(pBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr));

        memcpy(msr.pData, &input, sizeof(input));

        pCtx->Unmap(pBuffer.Get(), 0);
    }

    ID3D11Buffer *GetBuffer();
};
