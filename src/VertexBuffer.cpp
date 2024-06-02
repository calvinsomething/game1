#include "VertexBuffer.h"

VertexBuffers::VertexBuffers(std::initializer_list<VertexBufferBase *> vertex_buffers)
{
    Set(vertex_buffers);
}

void VertexBuffers::Set(std::initializer_list<VertexBufferBase *> input)
{
    unsigned n = input.size();

    vertex_buffers.clear();
    vertex_buffers.reserve(n);
    strides.clear();
    strides.reserve(n);
    offsets.clear();
    offsets.reserve(n);

    for (VertexBufferBase *b : input)
    {
        vertex_buffers.push_back(b->pBuffer.Get());
        strides.push_back(b->stride);
        offsets.push_back(b->offset);
    }
}

VertexBufferBase::VertexBufferBase(size_t stride) : stride(stride), offset(0)
{
}

void VertexBufferBase::Bind()
{
    pCtx->IASetVertexBuffers(0, 1, pBuffer.GetAddressOf(), &stride, &offset);
    CHECK_ERRORS();
}

void VertexBuffers::Bind()
{
    assert(initialized && "attempt to bind uninitialized VertexBuffers");
    pCtx->IASetVertexBuffers(0, vertex_buffers.size(), vertex_buffers.data(), strides.data(), offsets.data());
    CHECK_ERRORS();
}
