cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME} WIN32
	src/main.cpp
	src/Exception.cpp
	src/Window.cpp
	src/MainWindow.cpp
	src/Graphics.cpp
	src/resources.rc)

target_link_libraries(${PROJECT_NAME}
	d3d11.lib)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE src/pch.h)
