add_library(WICTextureLoader STATIC
	Microsoft/WICTextureLoader.h
	Microsoft/WICTextureLoader.cpp)

add_library(ImGui STATIC
	imgui/imgui.h
	imgui/imgui.cpp
	imgui/imgui_demo.cpp
	imgui/backends/imgui_impl_dx11.h
	imgui/backends/imgui_impl_dx11.cpp
	imgui/backends/imgui_impl_win32.h
	imgui/backends/imgui_impl_win32.cpp
	imgui/imconfig.h
	imgui/imgui_draw.cpp
	imgui/imgui_internal.h
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h
	imgui/imgui_tables.cpp
	imgui/imgui_widgets.cpp)

target_include_directories(ImGui PRIVATE
	${PROJECT_SOURCE_DIR}/vendor)
