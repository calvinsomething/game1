#include "GfxDebug.h"

#include "Window.h"

GfxDebug::GfxDebug()
{
	HMODULE lib = LoadLibraryA("Dxgidebug.dll");
	THROW_IF_FALSE(lib);

	typedef HRESULT (*DebugInterfaceGetter)(const IID& riid, void** ppDebug);
	DebugInterfaceGetter DXGIGetDebugInterface = reinterpret_cast<DebugInterfaceGetter>(GetProcAddress(lib, "DXGIGetDebugInterface"));

	THROW_IF_FAILED(DXGIGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(pInfoQueue.GetAddressOf())));

	pInfoQueue->PushEmptyStorageFilter(DXGI_DEBUG_ALL);
	pInfoQueue->PushEmptyRetrievalFilter(DXGI_DEBUG_ALL);
}

Exception GfxDebug::GetException(unsigned error_code, const char* file, unsigned line)
{
	memset(info_desc, 0, sizeof(info_desc));
	for (int i = 0; i < pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL); i++)
	{
		SIZE_T msgSize = 0;
		THROW_IF_FAILED(pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, i, nullptr, &msgSize));

		DXGI_INFO_QUEUE_MESSAGE* msg = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(alloca(msgSize));
		THROW_IF_FAILED(pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, i, msg, &msgSize));

		if (msg->DescriptionByteLength)
		{
			int len = msg->DescriptionByteLength;
			if (len >= sizeof(info_desc))
			{
				len = sizeof(info_desc);
				info_desc[len - 1] = 0;
			}
			memcpy(info_desc, msg->pDescription, len);
			return Exception(info_desc, msg->ID, file, line);
		}
	}
	return Exception("no DXGI messages", error_code, file, line);
}
