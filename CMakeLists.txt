cmake_minimum_required(VERSION 3.11)

project(bench)

set(BENCH_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BENCH_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Include guards
if (BENCH_SOURCE_DIR STREQUAL BENCH_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif ()

# Set variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


message("COMPILE_OPTIONS: ${COMPILE_OPTIONS}")
message("LINK_OPTIONS   : ${LINK_OPTIONS}")
add_definitions(${DEFINITIONS})

add_subdirectory(future)
