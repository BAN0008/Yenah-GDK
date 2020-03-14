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
list(APPEND sources "src/Shader.cpp")
list(APPEND sources "src/Log.cpp")
list(APPEND sources "src/Lua.cpp")
list(APPEND sources "src/Lua/LuaWrapper.cpp")

list(APPEND sources "vendor/${glad_dir}/src/glad.c")

add_executable(Yenah ${sources})

target_include_directories(Yenah PRIVATE "vendor/${glad_dir}/include")
target_include_directories(Yenah PRIVATE "vendor/glm/include")
target_include_directories(Yenah PRIVATE "vendor/LuaJit/include")
target_include_directories(Yenah PRIVATE "vendor/imgui/include")

file(READ "src/Lua/private/ffi.lua" lua_ffi)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/lua/lua_ffi.h" "const char lua_ffi_code[] = R\"(${lua_ffi})\";")

if(UNIX)
	target_include_directories(Yenah PRIVATE "/usr/include/SDL2")
	target_compile_definitions(Yenah PRIVATE UNIX)

	target_link_libraries(Yenah "dl" "luajit-5.1")
endif()
if(WIN32)
	target_include_directories(Yenah PRIVATE "vendor/SDL2/include")
	target_compile_definitions(Yenah PRIVATE WIN32 _CRT_SECURE_NO_WARNINGS)

	target_link_libraries(Yenah "SDL2main" "opengl32" "luajit" "lua51")
endif()

target_link_libraries(Yenah "SDL2")

set_target_properties(Yenah PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(Yenah PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")

if (WIN32)
	add_custom_command(TARGET Yenah POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2/lib/x64/SDL2.dll"
			$<TARGET_FILE_DIR:Yenah>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/lib/x64/lua51.dll"
			$<TARGET_FILE_DIR:Yenah>)
endif()
