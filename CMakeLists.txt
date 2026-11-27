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

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC
    include
    external
    external/glad/include
)

add_executable(2D-Black-Hole-Simulator
    src/main.cpp
    src/render.cpp
    src/config.cpp
)

target_compile_definitions(2D-Black-Hole-Simulator PRIVATE
    SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets"
    CONFIG_DIR="${CMAKE_CURRENT_SOURCE_DIR}/config"
)

target_link_libraries(2D-Black-Hole-Simulator PRIVATE
    glfw
    glad
    nlohmann_json::nlohmann_json
)