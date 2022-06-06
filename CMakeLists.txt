cmake_minimum_required(VERSION 3.0)
project(imlog CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(imgui CONFIG)
find_package(glfw3 CONFIG)
find_package(spdlog CONFIG)

add_executable(imlog
    bindings/imgui_impl_opengl3.h
    bindings/imgui_impl_opengl3.cpp
    bindings/imgui_impl_glfw.h
    bindings/imgui_impl_glfw.cpp
    bindings/imgui_impl_opengl3_loader.h
    src/main.cpp
)

target_link_libraries(imlog
    imgui::imgui
    glfw::glfw
    spdlog::spdlog
)

target_include_directories(imlog PUBLIC
    include
)