#pragma once

#include "Graphics.h"

class Camera : public GfxAccess
{
    float yaw = 0, pitch = 0, roll = 0;
    float psi = 0, theta = 0, phi = 0;

    DirectX::XMMATRIX Rotation;
    DirectX::XMMATRIX Translation;

  public:
    Camera() : Rotation(DirectX::XMMatrixIdentity()), Translation(DirectX::XMMatrixTranslation(0, 0, 50))
    {
    }

    void Revolve(float yaw, float pitch)
    {
        Rotation = Rotation * DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0);
        GfxAccess::tf_camera = Rotation * Translation;
    }
};
