cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME} WIN32
	src/main.cpp

	src/ConstantBuffer.cpp
	src/Cube.cpp
	src/Exception.cpp
	src/GfxDebug.cpp
	src/Graphics.cpp
	src/IndexBuffer.cpp
	src/MainWindow.cpp
	src/PixelShader.cpp
	src/SamplerState.cpp
	src/Shader.cpp
	src/Texture.cpp
	src/utils.cpp
	src/VertexBuffer.cpp
	src/VertexShader.cpp
	src/Window.cpp

	src/resources.rc)

add_subdirectory(shaders)
add_subdirectory(vendor)

add_dependencies(${PROJECT_NAME}
	assets
	shaders)

add_custom_target(assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/assets)

target_include_directories(${PROJECT_NAME} PRIVATE
	vendor)

target_link_libraries(${PROJECT_NAME}
	d3d11.lib
	d3dcompiler.lib
	dxguid.lib
	windowscodecs.lib

	WICTextureLoader)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE src/pch.h)
