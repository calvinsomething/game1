#pragma once

#include "Cube.h"
#include "Graphics.h"
#include "Window.h"

class MainWindow : public Window
{
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    std::unique_ptr<Graphics> pGfx;

    std::vector<std::unique_ptr<Cube>> cubes;

  public:
    MainWindow();
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    void RenderFrame();
};
