#include "MainWindow.h"

#include "utils.h"

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
             "world_icon", 1280, 720)
{
    pGfx = std::make_unique<Graphics>(hWnd);

    auto &rfg = RFG::Get();

    const unsigned cubesCt = 10;

    cubes.reserve(cubesCt);
    for (int i = 0; i < cubesCt; i++)
    {
        cubes.push_back(std::make_unique<Cube>(rfg(1.0f, 10.0f), std::array<float, 6>{
                                                                     rfg(0.0f, 1.0f),
                                                                     rfg(0.0f, 1.0f),
                                                                     rfg(0.0f, 1.0f),
                                                                     rfg(0.0f, 1.0f),
                                                                     rfg(0.0f, 1.0f),
                                                                     rfg(0.0f, 1.0f),
                                                                 }));
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::RenderFrame()
{
    pGfx->Clear({0.3f, 0.6f, 0.4f});

    for (auto &c : cubes)
    {
        c->Update(0.03f);
        c->Draw();
    }

    pGfx->EndFrame();
}
