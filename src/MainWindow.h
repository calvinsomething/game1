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

    std::mutex mouse_mutex;

    std::vector<std::unique_ptr<Cube>> cubes;

  public:
    MainWindow();
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    void MouseMove(short x, short y);
    void SetMouseLeftButtonDown(bool left_button_down);

    void RenderFrame();
    InputDevices::Mouse mouse = {};

    std::vector<char> raw_input;
    void log();
};
