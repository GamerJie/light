cmake_minimum_required(VERSION 3.15)
project(LIGHT)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MACOSX_RPATH 1)
add_subdirectory(extlibs/flecs-1.0)
include_directories(extlibs/flecs-1.0/include)

add_definitions(-DSFML_STATIC)
add_subdirectory(extlibs/SFML-2.5.1)

add_subdirectory(extlibs/spdlog-1.4.1)
add_subdirectory(extlibs/yaml-cpp-yaml-cpp-0.6.3)

if (APPLE)
set (CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000")
endif()

add_subdirectory(extlibs/luajit-2.0.5)
set(luajit_include "${CMAKE_SOURCE_DIR}/extlibs/luajit-2.0.5/src" CACHE INTERNAL "luajit include location")
#set(luajit_librany "${CMAKE_SOURCE_DIR}/extlibs/luajit-2.0.5/libs" CACHE INTERNAL "luajit librany location")

set(imgui_include "${CMAKE_SOURCE_DIR}/extlibs/imgui-1.73" CACHE INTERNAL "imgui include location")
set(imgui_sfml_include "${CMAKE_SOURCE_DIR}/extlibs/imgui-sfml-2.1" CACHE INTERNAL "sfml-imgui include location")

#set(IMGUI_SFML_FIND_SFML OFF)
#set(IMGUI_DIR ${imgui_include})
#add_subdirectory(extlibs/imgui-sfml-2.1)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(light)