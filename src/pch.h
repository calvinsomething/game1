#define WIN32_LEAN_AND_MEAN

// Microsoft
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <windows.h>
#include <wrl.h>

// STD
#include <array>
#include <cassert>
#include <chrono>
#include <exception>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Vendor
#include "Microsoft/WICTextureLoader.h"
