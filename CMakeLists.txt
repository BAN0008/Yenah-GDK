cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Yenah)

link_directories("vendor/SDL2/lib/x64")
link_directories("vendor/LuaJit/lib/x64")
link_directories("vendor/chipmunk/lib/x64")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(glad_dir "glad_debug")
else()
	set(CMAKE_BUILD_TYPE "Release")
	set(glad_dir "glad")
endif()

list(APPEND sources "src/Main.cpp")
list(APPEND sources "src/Window.cpp")
list(APPEND sources "src/Camera.cpp")
list(APPEND sources "src/Renderer.cpp")
list(APPEND sources "src/Profiler.cpp")
list(APPEND sources "src/RenderBatch.cpp")
list(APPEND sources "src/Shader.cpp")
list(APPEND sources "src/Texture.cpp")
list(APPEND sources "src/Log.cpp")
list(APPEND sources "src/Lua.cpp")
list(APPEND sources "src/Config.cpp")

list(APPEND sources "vendor/${glad_dir}/src/glad.c")

list(APPEND sources "vendor/stb_image/src/stb_image.cpp")

list(APPEND sources "vendor/imgui/src/imgui.cpp")
list(APPEND sources "vendor/imgui/src/imgui_draw.cpp")
list(APPEND sources "vendor/imgui/src/imgui_widgets.cpp")
list(APPEND sources "vendor/imgui/src/imgui_impl_opengl3.cpp")
list(APPEND sources "vendor/imgui/src/imgui_impl_sdl.cpp")

add_executable(Yenah ${sources})

target_include_directories(Yenah PRIVATE "vendor/${glad_dir}/include")
target_include_directories(Yenah PRIVATE "vendor/glm/include")
target_include_directories(Yenah PRIVATE "vendor/LuaJit/include")
target_include_directories(Yenah PRIVATE "vendor/imgui/include")
target_include_directories(Yenah PRIVATE "vendor/stb_image/include")
target_include_directories(Yenah PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/lua")
target_include_directories(Yenah PRIVATE "vendor/chipmunk/include")

function(embed_text_file)
	set(in_path "${ARGV0}")
	set(out_path "${ARGV1}")
	
	get_filename_component(in_fname "${in_path}" NAME)
	string(REGEX REPLACE "[^A-Za-z0-9]" "_" var_name "${in_fname}")
	set(max_part_length 1000)
	file(REMOVE "${out_path}")
	file(READ "${in_path}" file_string)
	string(LENGTH "${file_string}" file_length)
	math(EXPR part_count "${file_length} / ${max_part_length}")
	set(length_addition_string "")
	set(concat_string "")
	file(APPEND "${out_path}" "#include <cstring>\n\n")
	foreach(i RANGE ${part_count})
		math(EXPR part_index "${i} * ${max_part_length}")
		string(SUBSTRING "${file_string}" ${part_index} ${max_part_length} part_string)
		file(APPEND "${out_path}" "const char ${var_name}_p${i}[] = R\"(${part_string})\";\n\n")
		string(CONCAT length_addition_string "${length_addition_string}" "length += strlen(${var_name}_p${i});\n\t")
		if(${i} GREATER 0)
			string(CONCAT concat_string "${concat_string}" "strcat(string, ${var_name}_p${i});\n\t")
		else()
			string(CONCAT concat_string "${concat_string}" "strcpy(string, ${var_name}_p${i});\n\t")
		endif()
	endforeach(i)
	file(APPEND "${out_path}" "char *${var_name}()\n\
{\n\
	size_t length = 0;\n\
	${length_addition_string}\n\
	char *string = new char[length + ${part_count}];\n\
	${concat_string}\n\
	return string;\n\
}")
endfunction(embed_text_file)

file(READ "src/lua/main.lua" main_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/main_lua.h" "const char main_lua_code[] = R\"(${main_lua})\";")

file(READ "src/lua/object.lua" object_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/object_lua.h" "const char object_lua_code[] = R\"(${object_lua})\";")

#file(READ "src/lua/physics.lua" physics_lua)
#file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/physics_lua.h" "const char physics_lua_code[] = R\"(${physics_lua})\";")
embed_text_file("src/lua/physics.lua" "${CMAKE_CURRENT_BINARY_DIR}/lua/physics_lua.h")

file(READ "src/lua/vector.lua" vector_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/vector_lua.h" "const char vector_lua_code[] = R\"(${vector_lua})\";")

file(READ "src/lua/linked_list.lua" linked_list_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/linked_list_lua.h" "const char linked_list_lua_code[] = R\"(${linked_list_lua})\";")

file(READ "src/lua/input.lua" input_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/input_lua.h" "const char input_lua_code[] = R\"(${input_lua})\";")

file(READ "src/lua/texture.lua" texture_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/texture_lua.h" "const char texture_lua_code[] = R\"(${texture_lua})\";")

file(READ "src/lua/camera.lua" camera_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/camera_lua.h" "const char camera_lua_code[] = R\"(${camera_lua})\";")

file(READ "src/lua/renderer.lua" renderer_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/renderer_lua.h" "const char renderer_lua_code[] = R\"(${renderer_lua})\";")

if(UNIX)
	target_include_directories(Yenah PRIVATE "/usr/include/SDL2")
	target_compile_definitions(Yenah PRIVATE UNIX)

	target_link_libraries(Yenah "dl" "luajit-5.1" "m" "stdc++")
endif()
if(WIN32)
	target_include_directories(Yenah PRIVATE "vendor/SDL2/include")
	target_compile_definitions(Yenah PRIVATE WIN32 _CRT_SECURE_NO_WARNINGS)

	target_link_libraries(Yenah "SDL2main" "opengl32" "luajit" "lua51")
endif()

target_link_libraries(Yenah "SDL2" "chipmunk")

#target_compile_features(Yenah PRIVATE cxx_nullptr)
target_compile_features(Yenah PRIVATE cxx_std_11)

set_target_properties(Yenah PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(Yenah PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(Yenah PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(Yenah PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(Yenah PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(Yenah PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")

if (WIN32)
	add_custom_command(TARGET Yenah POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2/lib/x64/SDL2.dll"
			$<TARGET_FILE_DIR:Yenah>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/lib/x64/lua51.dll"
			$<TARGET_FILE_DIR:Yenah>)
endif()
