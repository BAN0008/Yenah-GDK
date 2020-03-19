cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Yeno)

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

list(APPEND sources "vendor/${glad_dir}/src/glad.c")

list(APPEND sources "vendor/stb_image/src/stb_image.cpp")

list(APPEND sources "vendor/imgui/src/imgui.cpp")
list(APPEND sources "vendor/imgui/src/imgui_draw.cpp")
list(APPEND sources "vendor/imgui/src/imgui_widgets.cpp")
list(APPEND sources "vendor/imgui/src/imgui_impl_opengl3.cpp")
list(APPEND sources "vendor/imgui/src/imgui_impl_sdl.cpp")

add_executable(Yeno ${sources})

target_include_directories(Yeno PRIVATE "vendor/${glad_dir}/include")
target_include_directories(Yeno PRIVATE "vendor/glm/include")
target_include_directories(Yeno PRIVATE "vendor/LuaJit/include")
target_include_directories(Yeno PRIVATE "vendor/imgui/include")
target_include_directories(Yeno PRIVATE "vendor/stb_image/include")

if(UNIX)
	target_include_directories(Yeno PRIVATE "/usr/include/SDL2")
	target_compile_definitions(Yeno PRIVATE UNIX)

	target_link_libraries(Yeno "dl" "luajit-5.1" "m" "stdc++")
endif()
if(WIN32)
	target_include_directories(Yeno PRIVATE "vendor/SDL2/include")
	target_compile_definitions(Yeno PRIVATE WIN32 _CRT_SECURE_NO_WARNINGS)

	target_link_libraries(Yeno "SDL2main" "opengl32" "luajit" "lua51")
endif()

target_link_libraries(Yeno "SDL2")

#target_compile_options(Yeno PRIVATE "-O3")
target_compile_features(Yeno PRIVATE cxx_nullptr)

set_target_properties(Yeno PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(Yeno PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")

if (WIN32)
	add_custom_command(TARGET Yeno POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2/lib/x64/SDL2.dll"
			$<TARGET_FILE_DIR:Yeno>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			"${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/lib/x64/lua51.dll"
			$<TARGET_FILE_DIR:Yeno>)
endif()
