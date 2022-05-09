#pragma once

#include <cstddef>

namespace bench {

template <std::size_t Size>
struct Blob {
  std::byte buffer[Size];
};

}  // namespace bench
