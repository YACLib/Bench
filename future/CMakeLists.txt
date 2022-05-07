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
if (ARANGODB)
  add_subdirectory(bind/arangodb)
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
