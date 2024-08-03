#pragma once

#include "VertexShader.h"

#define TC(c1, c2)                                                                                                     \
    {                                                                                                                  \
        c1##.0f * 0.25f, c2##.0f * 0.333333f                                                                           \
    }

class Box : protected GfxAccess
{
  protected:
    static std::vector<std::unique_ptr<Bindable>> bindables;
    static VertexShader *vs;

    void move(float dtime);

    DirectX::XMMATRIX transform;

  private:
    unsigned indices_count;

    float radius;
    float yaw, pitch, roll;
    float psi, theta, phi;

    std::array<float, 6> deltas;

  public:
    Box(float radius, std::array<float, 6> deltas, unsigned indices_count);

    virtual void Update(float dtime) = 0;
    void Draw();
};
