#include "Box.h"

using namespace Microsoft::WRL;
using namespace DirectX;

Box::Box(float radius, decltype(deltas) deltas)
    : radius(radius), deltas(deltas), pitch(), yaw(), roll(), theta(), psi(), phi()
{
}

void Box::move(float dtime)
{
    pitch += dtime * deltas[0];
    yaw += dtime * deltas[1];
    roll += dtime * deltas[2];
    theta += dtime * deltas[3];
    psi += dtime * deltas[4];
    phi += dtime * deltas[5];

    *transform = XMMatrixMultiplyTranspose(XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
                                               XMMatrixTranslation(radius, 0.0f, 0.0f),
                                           XMMatrixRotationRollPitchYaw(theta, psi, phi));
}

DirectX::XMVECTOR Box::GetPosition()
{
    return XMVector4Transform(XMVECTOR{0, 0, 0, 1}, XMMatrixTranspose(*transform));
}
