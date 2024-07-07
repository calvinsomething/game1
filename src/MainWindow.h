#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Graphics.h"
#include "InputDevices.h"
#include "Window.h"

class MainWindow : public Window
{
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    std::unique_ptr<Graphics> pGfx;
    std::unique_ptr<Camera> pCamera;

    std::vector<std::unique_ptr<Cube>> cubes;

  public:
    MainWindow();
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    void MouseMove(LPARAM lParam);

    void RenderFrame();
    InputDevices::Mouse mouse = {};

    std::vector<char> raw_input;
    void log();
};
