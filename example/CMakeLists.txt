cmake_minimum_required(VERSION 3.15)
project(example)

include_directories(${light_include})

file(GLOB sources sources/*.cpp)

add_executable(example ${sources})

target_link_libraries(example light)