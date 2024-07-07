#include "MainWindow.h"

#include "utils.h"

// Static
LRESULT CALLBACK MainWindow::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_NCCREATE: {
        CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT *>(lParam);
        SetWindowLongPtrA(hWnd, 0, reinterpret_cast<long long>(cs->lpCreateParams));
        break;
    }
    case WM_MOUSEMOVE: {
        reinterpret_cast<MainWindow *>(GetWindowLongPtrA(hWnd, 0))->MouseMove(lParam);
        break;
    }
    case WM_LBUTTONDOWN: {
        reinterpret_cast<MainWindow *>(GetWindowLongPtrA(hWnd, 0))->mouse.left_button_down = true;
        break;
    }
    case WM_LBUTTONUP: {
        reinterpret_cast<MainWindow *>(GetWindowLongPtrA(hWnd, 0))->mouse.left_button_down = false;
        break;
    }
    // case WM_INPUT: {
    //     unsigned size;
    //     if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)))
    //     {
    //         break;
    //     }

    //    void *ri = malloc(size);
    //    if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, ri, &size, sizeof(RAWINPUTHEADER)) !=
    //    size)
    //    {
    //        break;
    //    }

    //    const RAWINPUT &raw_input = *reinterpret_cast<RAWINPUT *>(ri);
    //    if (raw_input.header.dwType)
    //    {
    //        MainWindow *w = reinterpret_cast<MainWindow *>(GetWindowLongPtrA(hWnd, 0));
    //        w->mouse.left_button_down =
    //            (w->mouse.left_button_down || (raw_input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)) &&
    //            !(raw_input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP);
    //        w->mouse.Delta.x = raw_input.data.mouse.lLastX;
    //        w->mouse.Delta.y = raw_input.data.mouse.lLastY;
    //    }

    //    break;
    //}
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}

void MainWindow::log()
{
    char buf[50] = {};
    sprintf(buf, "l button = %d", mouse.left_button_down);

    throw std::exception(buf);
}

void MainWindow::MouseMove(LPARAM lParam)
{
    short x = GET_X_LPARAM(lParam);
    short y = GET_Y_LPARAM(lParam);

    if (mouse.left_button_down)
    {
        mouse.Delta.x = x - mouse.Position.x;
        mouse.Delta.y = y - mouse.Position.y;
    }
    else
    {
        mouse.Delta = {};
    }

    mouse.Position.x = x;
    mouse.Position.y = y;
};

// Methods
MainWindow::MainWindow()
    : Window("MainWindow", 0, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, wndProc,
             "world_icon", 1280, 720, this)
{
    pGfx = std::make_unique<Graphics>(hWnd);
    pCamera = std::make_unique<Camera>();

    // mouse = InputDevices::GetMouse();

    auto &rng = RNG::Get();

    const unsigned cubesCt = 10;

    cubes.reserve(cubesCt);
    for (int i = 0; i < cubesCt; i++)
    {
        cubes.push_back(std::make_unique<Cube>(rng(1.0f, 15.0f), std::array<float, 6>{
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                     rng(0.0f, 1.0f),
                                                                 }));
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::RenderFrame()
{
    pGfx->Clear({0.3f, 0.6f, 0.4f});

    const float mouse_speed = 0.01f * mouse.left_button_down;

    pCamera->Revolve(mouse_speed * mouse.Delta.x, mouse_speed * mouse.Delta.y);
    mouse.Delta = {};

    for (auto &c : cubes)
    {
        c->Update(0.03f);
        c->Draw();
    }

    pGfx->EndFrame();
}
