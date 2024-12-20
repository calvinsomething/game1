#pragma once

#include "Box.h"
#include "Camera.h"
#include "GUI.h"
#include "Graphics.h"
#include "InputDevices.h"
#include "Window.h"

class MainWindow : public Window
{
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    std::unique_ptr<Graphics> pGfx;
    std::unique_ptr<GUI> pGUI;
    Camera camera;

    std::mutex mouse_mutex;

    std::vector<std::unique_ptr<Box>> lights;
    std::vector<DirectX::XMVECTOR> light_positions;

    std::vector<std::unique_ptr<Box>> boxes;

  public:
    MainWindow();
    ~MainWindow();

    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;

    void RenderFrame();
    InputDevices::Mouse mouse = {};

    std::vector<char> raw_input;
};
