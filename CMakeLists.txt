cmake_minimum_required(VERSION 3.28)
project(game1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME} WIN32
	src/main.cpp
	src/Window.cpp
	src/MainWindow.cpp
	src/resources.rc)
