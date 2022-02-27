find_package(GTest QUIET)
find_package(benchmark QUIET)

if (NOT GTEST_FOUND OR NOT BENCHMARK_FOUND)
  if (BENCH_ENABLE_LTO)
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
endif ()

function(add_bench BENCH_PATH)
  string(REPLACE "/" "_" BENCH_NAME ${BENCH_PATH})
  add_executable(${BENCH_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${BENCH_PATH}.cpp)
  target_link_libraries(${BENCH_NAME}
    PRIVATE ${GTEST_BOTH_LIBRARIES}
    PRIVATE benchmark::benchmark
    PRIVATE ${PROJECT_NAME}
    )

  if (${YACLIB})
    target_compile_definitions(${BENCH_NAME} PUBLIC YACLIB_ENABLE)
  endif ()
  if (${FOLLY})
    target_compile_definitions(${BENCH_NAME} PUBLIC FOLLY_ENABLE)
  endif ()
  if (${QT})
    target_compile_definitions(${BENCH_NAME} PUBLIC QT_ENABLE)
  endif ()
  if (${STD})
    target_compile_definitions(${BENCH_NAME} PUBLIC STD_ENABLE)
  endif ()

  add_test(NAME ${BENCH_NAME} COMMAND ${BENCH_NAME})
endfunction()

find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

if (${YACLIB})
  # YACLib ###############################################################################################################
  FetchContent_Declare(yaclib
    GIT_REPOSITORY https://github.com/YACLib/YACLib.git
    GIT_TAG main
    )
  FetchContent_MakeAvailable(yaclib)
  link_libraries(yaclib)
endif ()

# Folly ################################################################################################################
# if (${FOLLY})
# TODO(kononovk): delete this dependency from folly in all benchmarks
  find_package(glog CONFIG REQUIRED)  # Ad-hoc
  find_package(folly CONFIG REQUIRED)
  include_directories(${FOLLY_INCLUDE_DIR})
  link_libraries(Folly::folly)
# endif ()


# QT ###################################################################################################################
if (${QT})
  find_package(Qt6 COMPONENTS Concurrent REQUIRED)
  link_libraries(Qt6::Concurrent)
endif ()

# Bench ################################################################################################################
set(BENCH_HEADERS ${BENCH_SOURCE_DIR}/util/bench.hpp ${BENCH_SOURCE_DIR}/future/bind/all.hpp)
set(BENCH_SOURCES)

macro(add_files)
  set(BENCH_HEADERS ${BENCH_HEADERS} PARENT_SCOPE)
  set(BENCH_SOURCES ${BENCH_SOURCES} PARENT_SCOPE)
endmacro()

if (${YACLIB})
  add_subdirectory(bind/yaclib)
endif ()
if (${STD})
  add_subdirectory(bind/std)
endif ()
if (${QT})
  add_subdirectory(bind/qt)
endif ()
if (${FOLLY})
  add_subdirectory(bind/folly)
endif ()

add_subdirectory(bench)

add_library(${PROJECT_NAME} STATIC
  ${BENCH_SOURCES}
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_NAME} PUBLIC ${BENCH_SOURCE_DIR}/util)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${GTEST_BOTH_LIBRARIES}
  PUBLIC benchmark::benchmark
  )

target_sources(${PROJECT_NAME}
  PRIVATE ${BENCH_HEADERS}
  )

add_bench(future)
