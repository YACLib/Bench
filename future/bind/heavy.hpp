#pragma once

#include <array>
#include <cstddef>

#ifdef HEAVY
#define SIZEOF_F                                                                                                       \
  sizeof_f = std::array<size_t, 3> {}
#else
#define SIZEOF_F
#endif
