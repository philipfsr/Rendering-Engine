cmake_minimum_required(VERSION 3.23)

project(RenderingEngine LANGUAGES CXX)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

add_executable(RenderingEngine)

target_sources(RenderingEngine
    PRIVATE
        src/main.cpp
)

target_link_libraries(RenderingEngine
    PRIVATE
        glfw
)