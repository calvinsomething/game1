cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} WIN32
	${SOURCE_DIR}/ConstantBuffer.cpp
	${SOURCE_DIR}/Cube.cpp
	${SOURCE_DIR}/Exception.cpp
	${SOURCE_DIR}/GfxDebug.cpp
	${SOURCE_DIR}/Graphics.cpp
	${SOURCE_DIR}/GUI.cpp
	${SOURCE_DIR}/IndexBuffer.cpp
	${SOURCE_DIR}/InputDevices.cpp
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/MainWindow.cpp
	${SOURCE_DIR}/PixelShader.cpp
	${SOURCE_DIR}/SamplerState.cpp
	${SOURCE_DIR}/Shader.cpp
	${SOURCE_DIR}/Texture.cpp
	${SOURCE_DIR}/utils.cpp
	${SOURCE_DIR}/VertexBuffer.cpp
	${SOURCE_DIR}/VertexShader.cpp
	${SOURCE_DIR}/Window.cpp

	${SOURCE_DIR}/resources.rc)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE ${SOURCE_DIR}/pch.h)

add_subdirectory(shaders)
add_subdirectory(vendor)

add_dependencies(${PROJECT_NAME}
	assets
	shaders)

add_custom_target(assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets ${PROJECT_BINARY_DIR}/assets)

target_include_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/vendor)

target_link_libraries(${PROJECT_NAME}
	d3d11.lib
	d3dcompiler.lib
	dxguid.lib
	windowscodecs.lib

	ImGui
	WICTextureLoader)

