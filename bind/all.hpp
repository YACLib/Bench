#pragma once

#ifdef STD_ENABLE
#  include <bind/std/library.hpp>
#endif

#ifdef YACLIB_ENABLE
#  include <bind/yaclib/library.hpp>
#endif

#ifdef CPPCORO_ENABLE
#  include <bind/cppcoro/library.hpp>
#endif

#ifdef FOLLY_ENABLE
#  include <bind/folly/library.hpp>
#endif

#ifdef ARANGODB_ENABLE
#  include <bind/arangodb/library.hpp>
#endif

#ifdef BOOST_THREAD_ENABLE
#  include <bind/boost_thread/library.hpp>
#endif

#ifdef QT_ENABLE
#  include <bind/qt/library.hpp>
#endif

#ifdef EXPERIMENTAL_ENABLE
#  include <bind/experimental/library.hpp>
#endif
