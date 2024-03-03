#include <windows.h>
#include <exception>

#include "MainWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
	int exitCode = 1;
	try {
		MainWindow window{};

		MSG msg{};
		while ((exitCode = GetMessageA(&msg, NULL, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			window.doFrame();
		}
	} catch (const std::exception& e) {
	}
	return exitCode;
}
