#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

// Microsoft
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <hidusage.h>
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>

// STD
#include <array>
#include <cassert>
#include <chrono>
#include <exception>
#include <iterator>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Vendor
#include "Microsoft/WICTextureLoader.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "imgui/imgui.h"
