cmake_minimum_required(VERSION 3.15)
project(light)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(${luajit_include})
include_directories(${imgui_include})
include_directories(${imgui_sfml_include})

#include_directories(${LUAJIT_INCLUDE_DIRS})
#message(${LUAJIT_LIBRARIES})

set(light_include "${CMAKE_SOURCE_DIR}/light/include" CACHE INTERNAL "light include location")

file(GLOB imgui ${imgui_include}/*.cpp)
file(GLOB imgui_sfml ${imgui_sfml_include}/imgui-SFML.cpp)

file(GLOB sources sources/*.cpp)
file(GLOB core sources/core/*.cpp)
file(GLOB systems sources/systems/*.cpp)
file(GLOB im_systems sources/systems/imgui/*.cpp)

add_library(light SHARED ${sources} ${core} ${systems} ${imgui} ${imgui_sfml} ${im_systems})

target_link_libraries(light flecs_static yaml-cpp spdlog OpenGL ${LUAJIT_LIBRARIES}
        sfml-audio
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics)