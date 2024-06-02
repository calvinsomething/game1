#pragma once

#include "Graphics.h"

class Bindable : protected GfxAccess
{
  public:
    virtual void Bind() = 0;
};
