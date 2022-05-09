cmake_minimum_required(VERSION 3.11)

project(bench)

set(BENCH_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BENCH_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Include guards
if (BENCH_SOURCE_DIR STREQUAL BENCH_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif ()

# Set variables
set(CMAKE_CXX_STANDARD 20)
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
if (LIBCXX)
  add_compile_options(-stdlib=libc++)
  add_link_options(-stdlib=libc++ -lc++abi)
endif ()

set(UTIL_HEADERS
  ${BENCH_SOURCE_DIR}/util/bench.hpp
  ${BENCH_SOURCE_DIR}/util/semaphore.hpp
  )

find_package(benchmark QUIET)

if (NOT BENCHMARK_FOUND)
  include(FetchContent)
  if (NOT BENCHMARK_FOUND)
    set(BENCHMARK_ENABLE_TESTING NO)
    FetchContent_Declare(
      benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(benchmark)
  endif ()
endif ()

function(add_bench BENCH_PATH)
  string(REPLACE "/" "_" BENCH_NAME ${BENCH_PATH})
  add_executable(${BENCH_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${BENCH_PATH}.cpp)
  target_link_libraries(${BENCH_NAME}
    PRIVATE ${GTEST_BOTH_LIBRARIES}
    PRIVATE benchmark::benchmark
    PRIVATE ${PROJECT_NAME}
    )

  if (STD)
    target_compile_definitions(${BENCH_NAME} PUBLIC STD_ENABLE)
  endif ()
  if (YACLIB)
    target_compile_definitions(${BENCH_NAME} PUBLIC YACLIB_ENABLE)
  endif ()
  if (FOLLY)
    target_compile_definitions(${BENCH_NAME} PUBLIC FOLLY_ENABLE)
  endif ()
  if (ARANGODB)
    target_compile_definitions(${BENCH_NAME} PUBLIC ARANGODB_ENABLE)
  endif ()
  if (BOOST_THREAD)
    target_compile_definitions(${BENCH_NAME} PUBLIC BOOST_THREAD_ENABLE)
  endif ()
  if (QT)
    target_compile_definitions(${BENCH_NAME} PUBLIC QT_ENABLE)
  endif ()
  if (EXPERIMENTAL)
    target_compile_definitions(${BENCH_NAME} PUBLIC EXPERIMENTAL_ENABLE)
  endif ()

  add_test(NAME ${BENCH_NAME} COMMAND ${BENCH_NAME})
endfunction()

find_package(Threads REQUIRED)
link_libraries(Threads::Threads)
include_directories(vendor)

if (YACLIB)
  FetchContent_Declare(yaclib
    GIT_REPOSITORY https://github.com/YACLib/YACLib.git
    GIT_TAG "${YACLIB}"
    )
  list(APPEND YACLIB_FLAGS "ATOMIC_EVENT")
  FetchContent_MakeAvailable(yaclib)
  link_libraries(yaclib)
endif ()
if (FOLLY)
  find_package(glog CONFIG REQUIRED)  # Ad-hoc
  find_package(folly CONFIG REQUIRED)
  include_directories(${FOLLY_INCLUDE_DIR})
  link_libraries(Folly::folly)
endif ()
if (ARANGODB)
  add_library(arangodb STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/arangodb/futures/Future.cpp
    )
endif ()
if (BOOST_THREAD)
  find_package(Boost COMPONENTS thread REQUIRED)
  link_libraries(Boost::thread)
endif ()
if (QT)
  find_package(Qt6 COMPONENTS Concurrent REQUIRED)
  link_libraries(Qt6::Concurrent)
endif ()
if (EXPERIMENTAL)
  add_link_options(-lc++experimental)
endif ()


add_subdirectory(future)
