cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Yeno-Engine)

link_directories("${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2/lib/x64")
link_directories("${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/lib/x64")

list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Window.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Shader.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/RenderBatch.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Camera.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Log.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Config.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Scripting.cpp")

list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/src/imgui.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/src/imgui_draw.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/src/imgui_widgets.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/src/imgui_impl_sdl.cpp")
list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/src/imgui_impl_opengl3.cpp")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(glad_dir "glad_debug")
else()
	set(glad_dir "glad")
endif()

list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/vendor/${glad_dir}/src/glad.c")

if(STATIC)
	set(target yeno_static)
	add_library(${target} STATIC ${source})
else()
	set(target yeno)
	add_library(${target} SHARED ${source})
endif()

list(APPEND libraries "SDL2")

if (UNIX)
	list(APPEND libraries "dl" "luajit-5.1" "m")
endif()
if (WIN32)
	list(APPEND libraries "opengl32" "SDL2main" "luajit" "lua51")
endif()

target_link_libraries(${target} ${libraries})
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/vendor/${glad_dir}/include")
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/vendor/glm/include")
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/include")

if(WIN32)
	target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2/include")
endif()
if(UNIX)
	target_include_directories(${target} PUBLIC "/usr/include/SDL2")
endif()
target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/include")

target_compile_features(${target} PUBLIC cxx_nullptr)

set_target_properties(${target} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS       ON)
set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")

if (WIN32)
add_custom_command(TARGET yeno POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		"$<TARGET_FILE_DIR:yeno>/yeno.dll"
		"${CMAKE_CURRENT_LIST_DIR}/../TestApp/build/debug/yeno.dll")
endif()
