cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Yenah)

link_directories("vendor/SDL2/lib/x64")
link_directories("vendor/LuaJit/lib/x64")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(glad_dir "glad_debug")
else()
	set(CMAKE_BUILD_TYPE "Release")
	set(glad_dir "glad")
endif()

list(APPEND sources "src/Main.cpp")
list(APPEND sources "src/Window.cpp")
list(APPEND sources "src/Renderer.cpp")
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

file(READ "src/lua/main.lua" main_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/main_lua.h" "const char main_lua_code[] = R\"(${main_lua})\";")

file(READ "src/lua/texture.lua" texture_lua)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/texture_lua.h" "const char texture_lua_code[] = R\"(${texture_lua})\";")

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

target_link_libraries(Yenah "SDL2")

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
