#pragma once

#include <yaclib/util/detail/node.hpp>

#include <cassert>
#include <cstddef>
#include <utility>

namespace bench::detail::yb {

template <typename T>
class List final {
 public:
  List& operator=(const List&) = delete;
  List& operator=(List&&) = delete;
  List(const List&) = delete;

  List() noexcept = default;
  List(List&& other) noexcept {
    if (this == &other || other.Empty()) {
      return;
    }
    _head.next = std::exchange(other._head.next, nullptr);
    _tail = std::exchange(other._tail, &other._head);
  }

  void PushFront(yaclib::detail::Node& node) noexcept {
    if (Empty()) {
      _tail = &node;
    }
    node.next = _head.next;
    _head.next = &node;
  }
  void PushBack(yaclib::detail::Node& node) noexcept {
    // for circular should be node.next = _tail->next;
    assert(_tail->next == nullptr);
    node.next = nullptr;
    _tail->next = &node;
    _tail = &node;
  }

  [[nodiscard]] bool Empty() const noexcept {
    assert((_head.next == nullptr) == (_tail == &_head));
    return _head.next == nullptr;  // valid
  }
  [[nodiscard]] T& PopFront() noexcept {
    assert(!Empty());
    auto* node = _head.next;
    _head.next = node->next;
    if (node->next == nullptr) {  // valid only for linear
      _tail = &_head;
    }
    return static_cast<T&>(*node);
  }

 private:
  yaclib::detail::Node _head;
  yaclib::detail::Node* _tail = &_head;  // need for PushBack
};

}  // namespace bench::detail::yb
