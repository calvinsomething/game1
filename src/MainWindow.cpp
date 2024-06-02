#include "MainWindow.h"

// Static
LRESULT CALLBACK MainWindow::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

// Methods
MainWindow::MainWindow()
    : Window("MainWindow", 0, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, wndProc,
             "world_icon")
{
    pGfx = std::make_unique<Graphics>(hWnd);

    cubes.reserve(1);
    cubes.push_back(std::make_unique<Cube>());
}

MainWindow::~MainWindow()
{
}

void MainWindow::RenderFrame()
{
    pGfx->Clear({0.2f, 1.0f, 0.3f});

    for (auto &c : cubes)
    {
        c->Draw();
    }

    pGfx->EndFrame();
}
