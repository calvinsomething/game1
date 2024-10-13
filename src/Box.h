#pragma once

#include "Graphics.h"

#define TC(c1, c2)                                                                                                     \
    {                                                                                                                  \
        c1##.0f * 0.25f, c2##.0f * 0.333333f                                                                           \
    }

class Box : protected GfxAccess
{
  protected:
    void move(float dtime);

    DirectX::XMMATRIX transform;

  private:
    unsigned indices_count;

    float radius;
    float pitch, yaw, roll;
    float theta, psi, phi;

    std::array<float, 6> deltas;

  public:
    Box(float radius, std::array<float, 6> deltas);

    virtual void Update(float dtime) = 0;
    virtual void Draw() = 0;
};
