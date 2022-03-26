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

if (YACLIB)
  FetchContent_Declare(yaclib
    GIT_REPOSITORY https://github.com/YACLib/YACLib.git
    GIT_TAG "${YACLIB}"
    )
  set(YACLIB_CXX_STANDARD 20)
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
# Bench ################################################################################################################
macro(add_files)
  set(BENCH_HEADERS ${BENCH_HEADERS} PARENT_SCOPE)
  set(BENCH_SOURCES ${BENCH_SOURCES} PARENT_SCOPE)
endmacro()
set(BENCH_HEADERS
  ${BENCH_SOURCE_DIR}/future/bind/all.hpp
  )
set(BENCH_SOURCES
  )

if (STD)
  add_subdirectory(bind/std)
endif ()
if (YACLIB)
  add_subdirectory(bind/yaclib)
endif ()
if (FOLLY)
  add_subdirectory(bind/folly)
endif ()
if (BOOST_THREAD)
  add_subdirectory(bind/boost_thread)
endif ()
if (QT)
  add_subdirectory(bind/qt)
endif ()
if (EXPERIMENTAL)
  add_subdirectory(bind/experimental)
endif ()

add_subdirectory(bench)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PRIVATE ${BENCH_SOURCES}
  PRIVATE ${BENCH_HEADERS}
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ${BENCH_SOURCE_DIR}/util
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE ${GTEST_BOTH_LIBRARIES}
  PUBLIC benchmark::benchmark
  )

add_bench(future) # TODO separate
