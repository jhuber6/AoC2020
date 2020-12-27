cmake_minimum_required(VERSION 3.13.4)
project(compiler LANGUAGES CXX)

# Standard Settings
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Build type
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -fno-rtti -fno-exceptions")

# Compiler flags
set(COMPILER_WARNINGS
    -Wall
    -Wextra
    -Wpedantic
    -Wunused
    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wold-style-cast
    -Wcast-align
    -Wconversion
    -Wnull-dereference
    -Wdouble-promotion)

# Compilation targets
set(PROJECTS Day1 Day2 Day3 Day4 Day5 Day6 Day7 Day8 Day9 Day10 Day11 Day12 Day13 Day14 Day15 Day16 Day17 Day18 Day19 Day20 Day21 Day22 Day23 Day24 Day25)

foreach(PROJECT ${PROJECTS})
    add_executable(${PROJECT})
    set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_include_directories(${PROJECT} PRIVATE include)
    target_compile_options(${PROJECT} PRIVATE ${COMPILER_WARNINGS})
endforeach()

add_subdirectory(src)
