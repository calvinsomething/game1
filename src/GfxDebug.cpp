#include "GfxDebug.h"

#include "Window.h"

// Global Debug object
GfxDebug gfxDebug;

GfxDebug::GfxDebug() : msg_index(), info_desc_index(), full()
{
    HMODULE lib = LoadLibraryA("Dxgidebug.dll");
    THROW_IF_FALSE(lib);

    typedef HRESULT (*DebugInterfaceGetter)(const IID &riid, void **ppDebug);
    DebugInterfaceGetter DXGIGetDebugInterface =
        reinterpret_cast<DebugInterfaceGetter>(GetProcAddress(lib, "DXGIGetDebugInterface"));

    THROW_IF_FAILED(
        DXGIGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void **>(pInfoQueue.GetAddressOf())));

    DXGI_INFO_QUEUE_MESSAGE_SEVERITY deny_list[3] = {
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE,
        DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING,
    };

    DXGI_INFO_QUEUE_FILTER filter = {};
    filter.DenyList = {};
    filter.DenyList.NumSeverities = 3;
    filter.DenyList.pSeverityList = deny_list;

    pInfoQueue->PushEmptyStorageFilter(DXGI_DEBUG_ALL);
    pInfoQueue->PushRetrievalFilter(DXGI_DEBUG_ALL, &filter);

    memset(info_desc, 0, sizeof(info_desc));
}

void GfxDebug::SetIndex()
{
    msg_index = pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL);
}

void GfxDebug::Clear()
{
    pInfoQueue->ClearStoredMessages(DXGI_DEBUG_ALL);
}

bool GfxDebug::GetAllMessages()
{
    for (; msg_index < pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL); msg_index++)
    {
        if (!full)
        {
            GetDebugMessage();
        }
    }
    return info_desc_index;
}

Exception GfxDebug::GetException(unsigned error_code, const char *file, unsigned line)
{
    if (GetAllMessages())
    {
        return Exception(info_desc, error_code, file, line);
    }
    return Exception("no DXGI debug messages", error_code, file, line);
}

void GfxDebug::GetDebugMessage()
{
    SIZE_T msgSize = 0;
    THROW_IF_FAILED(pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, msg_index, nullptr, &msgSize));

    DXGI_INFO_QUEUE_MESSAGE *msg = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE *>(alloca(msgSize));
    THROW_IF_FAILED(pInfoQueue->GetMessageA(DXGI_DEBUG_ALL, msg_index, msg, &msgSize));

    if (msg->DescriptionByteLength)
    {
        if (info_desc_index)
        {
            memcpy(info_desc + info_desc_index, "\n\n", 2);
            info_desc_index += 2;
        }

        int len = msg->DescriptionByteLength;
        if (len > sizeof(info_desc) - info_desc_index - 2)
        {
            len = sizeof(info_desc) - info_desc_index - 1;
        }

        memcpy(info_desc + info_desc_index, msg->pDescription, len);
        info_desc_index += len;

        full = sizeof(info_desc) - info_desc_index < 30;
    }
}

void GfxDebug::CheckErrors(const char *file, unsigned line)
{
    if (GetAllMessages())
    {
        throw Exception(info_desc, 999999999, file, line);
    }
}
