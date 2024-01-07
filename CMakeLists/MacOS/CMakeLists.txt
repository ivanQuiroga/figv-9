cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME FIGV)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

file( GLOB SOURCE_FILES src/*.cpp src/*.c lib/*.cpp lib/*.c lib/imgui/*.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/backends/imgui_impl_glfw.cpp /usr/local/glad/src/*.c )

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)


add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )

include_directories(lib lib/imgui lib/imgui/backends /opt/homebrew/include /usr/local/glad/include )
link_directories( /opt/homebrew/lib )
target_link_libraries( ${PROJECT_NAME} OpenGL::GL glfw assimp::assimp )

