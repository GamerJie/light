cmake_minimum_required(VERSION 3.13.2)
project(LIGHT)

set(CMAKE_CXX_STANDARD 14)

if (APPLE)
add_definitions(-DCMAKE_OSX_ARCHITECTURES=x86_64)
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_MACOSX_RPATH 1)
set(MACOSX_DEPLOYMENT_TARGET 10.14)
add_subdirectory(extlibs/flecs-1.0)
include_directories(extlibs/flecs-1.0/include)

set(STATIC_SFML TRUE)
set(BUILD_SHARED_LIBS FALSE)
add_definitions(-DSFML_STATIC)
add_subdirectory(extlibs/SFML-2.5.1)

add_subdirectory(extlibs/spdlog-1.4.1)
add_subdirectory(extlibs/yaml-cpp-yaml-cpp-0.6.3)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    # Required for luajit.
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")
    set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -image_base 100000000")
    set(CMAKE_MODULE_LINKER_FLAGS
            "${CMAKE_MODULE_LINKER_FLAGS} -image_base 100000000")
endif()

find_package(luajit REQUIRED)

#add_subdirectory(extlibs/luajit-2.0.5)
set(luajit_include "${CMAKE_SOURCE_DIR}/extlibs/luajit-2.0.5/src" CACHE INTERNAL "luajit include location")

set(imgui_include "${CMAKE_SOURCE_DIR}/extlibs/imgui-1.73" CACHE INTERNAL "imgui include location")
set(imgui_sfml_include "${CMAKE_SOURCE_DIR}/extlibs/imgui-sfml-2.1" CACHE INTERNAL "sfml-imgui include location")

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(light)
add_subdirectory(example)