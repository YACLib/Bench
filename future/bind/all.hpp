#pragma once

#ifdef STD_ENABLE
#include <bind/std/future.hpp>
#endif

#ifdef YACLIB_ENABLE
#include <bind/yaclib/future.hpp>
#endif

#ifdef FOLLY_ENABLE
#include <bind/folly/future.hpp>
#endif

#ifdef BOOST_THREAD_ENABLE
#include <bind/boost_thread/future.hpp>
#endif

#ifdef QT_ENABLE
#include <bind/qt/future.hpp>
#endif

#ifdef EXPERIMENTAL_ENABLE
#include <bind/experimental/future.hpp>
#endif
