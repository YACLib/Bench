#pragma once

#ifdef QT_ENABLE
#include "bind/qt/future.hpp"
#endif

#ifdef FOLLY_ENABLE
#include "bind/folly/future.hpp"
#endif

#ifdef YACLIB_ENABLE
#include "bind/yaclib/future.hpp"
#endif

#ifdef STD_ENABLE
#include "bind/std/future.hpp"
#endif
