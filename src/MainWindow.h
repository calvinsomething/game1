#pragma once

#include "Cube.h"
#include "Graphics.h"
#include "Window.h"

class MainWindow : public Window
{
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    std::unique_ptr<Graphics> pGfx;
    std::unique_ptr<Cube> cube;

  public:
    MainWindow();
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    void RenderFrame()
    {
        pGfx->Clear({0.2f, 1.0f, 0.3f});
        cube->Draw();
        pGfx->EndFrame();
    }
};
