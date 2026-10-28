cmake_minimum_required(VERSION 3.23)

project(RenderingEngine LANGUAGES CXX OBJCXX)

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
        src/geometry/Object.cpp
        src/geometry/Vec3D.cpp
        src/scene/Camera.cpp
        src/scene/Scene.cpp
)

target_link_libraries(RenderingEngine
    PRIVATE
        glfw
)

if(APPLE)

    target_compile_definitions(RenderingEngine PRIVATE USE_METAL)
    target_link_libraries(RenderingEngine
    PRIVATE
        "-framework Cocoa"
        "-framework Metal"
        "-framework QuartzCore"
    )
    target_sources(RenderingEngine
    PRIVATE
        src/platform/macos/MetalRenderer.mm
    )

elseif(WIN32)

    target_compile_definitions(RenderingEngine PRIVATE USE_VULKAN)
    target_sources(RenderingEngine
    PRIVATE
        src/platform/windows/VulkanRenderer.cpp
    )

endif()

target_include_directories(RenderingEngine
    PRIVATE
        src
)

target_compile_options(RenderingEngine 
    PRIVATE
        "$<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>"
)