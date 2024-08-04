#include "Box.h"

using namespace Microsoft::WRL;
using namespace DirectX;

Box::Box(float radius, decltype(deltas) deltas)
    : radius(radius), deltas(deltas), yaw(), pitch(), roll(), psi(), theta(), phi()
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
