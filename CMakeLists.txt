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

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("COMPILE_OPTIONS: ${COMPILE_OPTIONS}")
message("LINK_OPTIONS   : ${LINK_OPTIONS}")

include(FetchContent)

if (LIBCXX)
  add_compile_options(-stdlib=libc++ -fno-inline)
  add_link_options(-stdlib=libc++ -lc++abi)
endif ()

set(UTIL_HEADERS
  ${BENCH_SOURCE_DIR}/util/bench.hpp
  ${BENCH_SOURCE_DIR}/util/semaphore.hpp
  )

find_package(benchmark QUIET)

if (NOT BENCHMARK_FOUND)
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

function(add_bench BENCH_NAME)
  add_executable(${BENCH_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/test/${BENCH_NAME}/${BENCH_NAME}.cpp)
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
  if (CPPCORO)
    target_compile_definitions(${BENCH_NAME} PUBLIC CPPCORO_ENABLE)
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

if (YACLIB) # v2022.08.31
  FetchContent_Declare(yaclib
    GIT_REPOSITORY https://github.com/YACLib/YACLib.git
    GIT_TAG "${YACLIB}"
    )
  list(APPEND YACLIB_FLAGS "CORO")
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
if (CPPCORO)
  FetchContent_Declare(cppcoro
    GIT_REPOSITORY https://github.com/YACLib/cppcoro-for-benchmark.git
    GIT_TAG main
    )
  FetchContent_MakeAvailable(cppcoro)
  link_libraries(cppcoro)
endif ()

macro(add_files)
  set(BENCH_HEADERS ${BENCH_HEADERS} PARENT_SCOPE)
  set(BENCH_SOURCES ${BENCH_SOURCES} PARENT_SCOPE)
endmacro()

add_subdirectory(bind)
add_subdirectory(bench)
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PRIVATE ${BENCH_SOURCES}
  PRIVATE ${BENCH_HEADERS}
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${GTEST_BOTH_LIBRARIES}
  PUBLIC benchmark::benchmark
  )

add_bench(future)
add_bench(coro)
