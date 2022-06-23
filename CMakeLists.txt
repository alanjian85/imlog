cmake_minimum_required(VERSION 3.0)
project(imlog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
endif()

add_subdirectory(deps/glfw)
add_subdirectory(deps/volk)
add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/tinyobjloader)

add_executable(imlog
    src/main.cpp
    deps/imgui/imgui.cpp
    deps/imgui/imgui_demo.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_tables.cpp
    deps/imgui/imgui_widgets.cpp
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_vulkan.cpp
)

target_include_directories(imlog PUBLIC
    include
    deps/imgui
    deps/stb
    deps/tinyobjloader
)

target_link_libraries(imlog
    volk
    glfw
    glm::glm
    spdlog::spdlog
)

target_compile_definitions(imlog PRIVATE
    VK_NO_PROTOTYPES
)