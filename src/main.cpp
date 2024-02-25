#include <windows.h>

#include "MainWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
	try {
		MainWindow window{};

		MSG msg{};
		while (GetMessageA(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} catch (const std::exception& e) {
	}
	return 0;
}
