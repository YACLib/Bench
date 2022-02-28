#include <atomic>

namespace bench {

class BusySemaphoreSPSC {
 public:
  void Release() noexcept {
    _count.fetch_add(1, std::memory_order_release);
  }
  void Acquire() noexcept {
    while (_count.load(std::memory_order_relaxed) == 0) {
    }
    _count.fetch_sub(1, std::memory_order_acquire);
  }

 private:
  std::atomic_uint64_t _count = 0;
};

}  // namespace bench