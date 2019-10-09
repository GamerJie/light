cmake_minimum_required(VERSION 3.15)
project(light)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(${luajit_include})
include_directories(${imgui_include})
include_directories(${imgui_sfml_include})

set(light_include "${CMAKE_SOURCE_DIR}/light/include" CACHE INTERNAL "light include location")

file(GLOB imgui ${imgui_include}/*.cpp)
file(GLOB imgui_sfml ${imgui_sfml_include}/imgui-SFML.cpp)

file(GLOB sources sources/*.cpp)
file(GLOB core sources/core/*.cpp)
file(GLOB systems sources/systems/*.cpp)

#link_directories(${luajit_librany})

add_executable(light ${sources} ${core} ${systems} ${imgui} ${imgui_sfml})

target_link_libraries(light flecs_static yaml-cpp spdlog OpenGL lua-static
        sfml-audio
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics)