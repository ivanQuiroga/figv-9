cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME FIGV)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

file( GLOB SOURCE_FILES src/*.cpp src/*.c lib/imgui/*.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_glfw.cpp /usr/src/glad/src/*.c )
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

include_directories( lib lib/imgui lib/imgui/backends /usr/src/glad/include )
link_directories( /usr/lib/x86_64-linux-gnu )
target_link_libraries( ${PROJECT_NAME} GL glfw assimp )

