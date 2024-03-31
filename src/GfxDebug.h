#pragma once

#include "dxgidebug.h"

#include "Exception.h"

class GfxDebug
{
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pInfoQueue;
	char info_desc[512];

	bool GetAllMessages();
	void GetDebugMessage();

	unsigned long long msg_index;
	unsigned info_desc_index;
	bool full;
public:
	GfxDebug();

	void SetIndex();
	void Clear();
	Exception GetException(unsigned error_code, const char* file, unsigned line);
	void CheckErrors(const char* file, unsigned line);
};



