add_custom_target(shaders)

set(SHADER_FILES
	vertex.hlsl
	v_texture.hlsl
	pixel.hlsl
	p_texture.hlsl)
set_source_files_properties(vertex.hlsl PROPERTIES PROFILE "vs_4_0")
set_source_files_properties(v_texture.hlsl PROPERTIES PROFILE "vs_4_0")
set_source_files_properties(pixel.hlsl PROPERTIES PROFILE "ps_4_0")
set_source_files_properties(p_texture.hlsl PROPERTIES PROFILE "ps_4_0")

foreach(FILE ${SHADER_FILES})
	get_source_file_property(PROFILE ${FILE} PROFILE)
	get_filename_component(FILE_WE ${FILE} NAME_WE)
	add_custom_command(TARGET shaders
		COMMAND fxc /nologo /T ${PROFILE} /Fd ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.pdb /Fo ${CMAKE_BINARY_DIR}/shaders/${FILE_WE}.cso /Zi ${FILE}
		MAIN_DEPENDENCY ${FILE}
		COMMENT "Compiling Shader: ${FILE}"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		VERBATIM)
endforeach()
