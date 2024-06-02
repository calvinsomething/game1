#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(size_t byte_width)
{
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = byte_width;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    THROW_IF_FAILED(pDevice->CreateBuffer(&bd, nullptr, pBuffer.GetAddressOf()));
}

ID3D11Buffer *ConstantBuffer::GetBuffer()
{
    return pBuffer.Get();
}
