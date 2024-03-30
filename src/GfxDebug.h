#pragma once

#include "dxgidebug.h"

#include "Exception.h"

class GfxDebug
{
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pInfoQueue;
	char info_desc[512];
public:
	GfxDebug();

	Exception GetException(unsigned error_code, const char* file, unsigned line);
};



