#pragma once

#include "Graphics.h"

class Camera : public GfxAccess
{
    float pitch = 0, yaw = 0, roll = 0;
    float theta = 0, psi = 0, phi = 0;

    DirectX::XMMATRIX rotation;
    DirectX::XMMATRIX translation;

  public:
    Camera() : rotation(DirectX::XMMatrixIdentity()), translation(DirectX::XMMatrixTranslation(0, 0, 50))
    {
    }

    void Revolve(float theta, float psi)
    {
        rotation = rotation * DirectX::XMMatrixRotationRollPitchYaw(psi, theta, 0);
        tf_camera = rotation * translation;
    }

    void Done()
    {
        global_data.camera_position =
            DirectX::XMVectorScale(DirectX::XMVector4Transform(global_data.camera_position, tf_camera), -1);
    }
};
