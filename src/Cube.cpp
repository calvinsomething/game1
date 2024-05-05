#include "Cube.h"

using namespace Microsoft::WRL;
using namespace DirectX;

Cube::Cube(Graphics &gfx)
    : pDevice(gfx.pDevice.Get()), pCtx(gfx.pCtx.Get()), ib{gfx, indices, sizeof(indices)},
      vb{gfx, vertices, sizeof(vertices)}, vs{gfx, L"shaders/vertex.cso"}, vsTransform(gfx),
      ps{gfx, L"shaders/pixel.cso"}, psColors(gfx)
#ifndef NDEBUG
      ,
      debug(gfx.debug)
#endif
{
    // vertex buffer input layout
    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    pDevice->CreateInputLayout(ied, std::size(ied), vs.GetByteCode(), vs.GetByteCodeSize(),
                               pInputLayout.GetAddressOf());

    // vs constant buffer
    XMMATRIX transform =
        XMMatrixMultiplyTranspose(XMMatrixRotationX(0.3) * XMMatrixRotationY(0.5),
                                  XMMatrixTranslation(0, 0, 7) * XMMatrixPerspectiveLH(1, 0.75, 1, 10));
    vsTransform.Init(&transform, sizeof(transform));

    // ps constant buffer
    Color<float> face_colors[] = {
        {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {0, 1, 0}, {1, 1, 0}, {0, 1, 1},
    };
    psColors.Init(&face_colors, sizeof(face_colors));

    vertex_buffers[0] = vb.GetDxBuffer();
    vs_c_buffers[0] = vsTransform.GetDxBuffer();
    ps_c_buffers[0] = psColors.GetDxBuffer();
}

void Cube::Draw()
{
    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    unsigned stride = sizeof(vertices[0]), offset = 0;
    pCtx->IASetVertexBuffers(0, 1, vertex_buffers, &stride, &offset);

    pCtx->IASetIndexBuffer(ib.GetDxBuffer(), DXGI_FORMAT_R32_UINT, 0);

    vs.Bind();

    pCtx->IASetInputLayout(pInputLayout.Get());

    pCtx->VSSetConstantBuffers(0, 1, vs_c_buffers);

    ps.Bind();

    pCtx->PSSetConstantBuffers(0, 1, ps_c_buffers);

    pCtx->DrawIndexed(std::size(indices), 0, 0);
    CHECK_ERRORS();
}
