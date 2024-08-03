#include "Box.h"

using namespace Microsoft::WRL;
using namespace DirectX;

std::vector<std::unique_ptr<Bindable>> Box::bindables;
VertexShader *Box::vs;

Box::Box(float radius, decltype(deltas) deltas, unsigned indices_count)
    : radius(radius), deltas(deltas), yaw(), pitch(), roll(), psi(), theta(), phi(), indices_count(indices_count)
{
}

void Box::move(float dtime)
{
    yaw += dtime * deltas[0];
    pitch += dtime * deltas[1];
    roll += dtime * deltas[2];
    psi += dtime * deltas[3];
    theta += dtime * deltas[4];
    phi += dtime * deltas[5];

    transform = ToNDCSpace(XMMatrixRotationRollPitchYaw(yaw, pitch, roll) * XMMatrixTranslation(radius, 0.0f, 0.0f) *
                           XMMatrixRotationRollPitchYaw(psi, theta, phi));
}

void Box::Draw()
{
    for (auto &b : bindables)
    {
        b->Bind();
    }

    pCtx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CHECK_ERRORS();

    pCtx->DrawIndexed(indices_count, 0, 0);
    CHECK_ERRORS();
}
