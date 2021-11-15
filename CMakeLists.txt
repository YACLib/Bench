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
if (ENABLE_LTO)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
else ()
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
endif ()

if (MSVC)
  list(APPEND COMPILE_OPTIONS /W3)
  #TODO(MBkkt) We have to use /Wall. But MSVC is dumb and uses this flag for external projects, like gtest.
  if (SANITIZER)
    message("Sanitizer's work only on Linux")
  endif ()
else ()
  list(APPEND COMPILE_OPTIONS -Wall -Wextra -pedantic)
  if (SANITIZER STREQUAL ASAN)
    set(SANITIZER_ENABLE_OPTION -fsanitize=address)
    set(SANITIZER_COMPILE_OPTIONS
      # -fsanitize-address-use-after-return=runtime
      -fsanitize-recover=address
      -fsanitize-address-use-after-scope
      )
  elseif (SANITIZER STREQUAL TSAN)
    set(SANITIZER_ENABLE_OPTION -fsanitize=thread)
    set(SANITIZER_COMPILE_OPTIONS
      -gcolumn-info
      )
  elseif (SANITIZER STREQUAL UBSAN)
    set(SANITIZER_ENABLE_OPTION -fsanitize=undefined)
  elseif (SANITIZER STREQUAL MEMSAN) # Memory Santizer doesn't work with GTest (https://github.com/google/sanitizers/issues/648)
    set(SANITIZER_ENABLE_OPTION -fsanitize=memory)
  endif ()
  list(APPEND COMPILE_OPTIONS
    ${SANITIZER_ENABLE_OPTION}
    ${SANITIZER_COMPILE_OPTIONS}
    )
  list(APPEND LINK_OPTIONS ${SANITIZER_ENABLE_OPTION})
endif ()
if (COVERAGE AND CMAKE_SYSTEM_NAME STREQUAL Linux)
  list(APPEND COMPILE_OPTIONS
    --coverage
    )
  list(APPEND LINK_OPTIONS
    --coverage
    )
endif ()
message("COMPILE_OPTIONS: ${COMPILE_OPTIONS}")
message("LINK_OPTIONS   : ${LINK_OPTIONS}")
add_definitions(${DEFINITIONS})

find_package(GTest QUIET)
find_package(benchmark QUIET)

if (NOT GTEST_FOUND OR NOT BENCHMARK_FOUND)
  if (YACLIB_ENABLE_LTO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
  endif ()

  include(FetchContent)
  if (NOT GTEST_FOUND)
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.11.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll")
    FetchContent_MakeAvailable(googletest)
    set(GTEST_BOTH_LIBRARIES GTest::gtest GTest::gtest_main)
  endif ()
  if (NOT BENCHMARK_FOUND)
    set(BENCHMARK_ENABLE_TESTING NO)
    FetchContent_Declare(
      benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_TAG v1.6.0
    )
    FetchContent_MakeAvailable(benchmark)
  endif ()

  if (YACLIB_ENABLE_LTO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  endif ()
endif ()

function(add_bench BENCH_PATH)
  string(REPLACE "/" "_" BENCH_NAME ${BENCH_PATH})
  add_executable(${BENCH_NAME} ${BENCH_SOURCE_DIR}/${BENCH_PATH}.cpp)
  target_link_libraries(${BENCH_NAME}
    PRIVATE ${GTEST_BOTH_LIBRARIES}
    PRIVATE benchmark::benchmark
    PRIVATE ${${PROJECT_NAME}}
    )
  add_test(NAME ${BENCH_NAME} COMMAND ${BENCH_NAME})
endfunction()

macro(add_files)
  set(BENCH_SOURCES ${BENCH_SOURCES} PARENT_SCOPE)
endmacro()

# YACLib ###############################################################################################################
FetchContent_Declare(yaclib
  GIT_REPOSITORY https://github.com/YACLib/YACLib.git
  GIT_TAG madoka/lock-free-threadpool
  )
FetchContent_MakeAvailable(yaclib)
link_libraries(yaclib)

# Folly ################################################################################################################
find_package(glog CONFIG REQUIRED)  # Ad-hoc
find_package(folly CONFIG REQUIRED)
include_directories(${FOLLY_INCLUDE_DIR})
link_libraries(Folly::folly)

# Bench ################################################################################################################
set(BENCH_HEADERS
  utils/threadpool_runner.hpp
  utils/threadpool_suite.hpp
  threadpool_problems/simple_fluid_solver.hpp
  yaclib/threadpool.hpp
  std/threadpool.hpp
  std/progschj_threadpool.hpp
  folly/threadpool.hpp
  )
set(BENCH_SOURCES
  utils/threadpool_runner.cpp
  utils/threadpool_suite.cpp
  threadpool_problems/simple_fluid_solver.cpp
  yaclib/threadpool.cpp
  std/threadpool.cpp
  folly/threadpool.cpp
  )
add_library(${PROJECT_NAME} STATIC
  ${BENCH_SOURCES}
  )
target_sources(${PROJECT_NAME}
  PRIVATE ${BENCH_HEADERS}
  )
link_libraries(${PROJECT_NAME})

#add_bench(future)
add_bench(lock_free_threadpool)
