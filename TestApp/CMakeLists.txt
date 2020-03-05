cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(TestApp)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(config "debug")
else()
	set(config "release")
endif()

link_directories("${CMAKE_CURRENT_LIST_DIR}/../Engine/build/${config}")
link_directories("${CMAKE_CURRENT_LIST_DIR}/../Engine/vendor/SDL2/lib/x64")
link_directories("${CMAKE_CURRENT_LIST_DIR}/vendor/LuaJit/lib/x64")

list(APPEND source "${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp")

add_executable(TestApp ${source})

target_link_libraries(TestApp "yeno" "SDL2" "SDL2main")
target_include_directories(TestApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../Engine/include")
target_include_directories(TestApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../Engine/vendor/glad_debug/include")
target_include_directories(TestApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../Engine/vendor/SDL2/include")
target_include_directories(TestApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../Engine/vendor/GLM")
target_include_directories(TestApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../Engine/vendor/LuaJit/include")

set_target_properties(TestApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/release")
set_target_properties(TestApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_BINARY_DIR}/debug")