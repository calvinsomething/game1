#pragma once

#include "Graphics.h"

class Box : protected GfxAccess
{
  protected:
    void move(float dtime);

    DirectX::XMMATRIX *transform;

  private:
    unsigned indices_count;

    float radius;
    float pitch, yaw, roll;
    float theta, psi, phi;

    std::array<float, 6> deltas;

  public:
    Box(float radius, std::array<float, 6> deltas);

    DirectX::XMVECTOR GetPosition();

    virtual void Update(float dtime) = 0;
    virtual void Draw() = 0;
};
