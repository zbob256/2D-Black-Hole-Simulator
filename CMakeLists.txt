cmake_minimum_required(VERSION 3.20)

project(2D-Black-Hole-Simulator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_library(glad STATIC external/glad/src/gl.c)

target_include_directories(glad PUBLIC external/glad/include)

add_executable(2D-Black-Hole-Simulator src/main.cpp)

target_link_libraries(2D-Black-Hole-Simulator PRIVATE glfw glad)