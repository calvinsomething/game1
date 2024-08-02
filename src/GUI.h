#pragma once

#include "Graphics.h"

class GUI : GfxAccess
{
  public:
    GUI(HWND hWnd);
    ~GUI();

    void Render();
};
