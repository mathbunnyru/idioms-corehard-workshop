#include "is_array.h"
#include "remove_extent.h"
#include "ebo_helper.h"
#include <memory>
#include <type_traits>
#include <utility>

template<typename T, typename Deleter = std::default_delete<T>>
class smart_ptr : private ebo_helper<Deleter> {
  using Base = ebo_helper<Deleter>;

public:
  using element = remove_extent_t<T>;
  using pointer = element*;

  smart_ptr() = default;

  explicit smart_ptr(pointer ptr, Deleter deleter  = Deleter()) noexcept :
      Base(deleter),
      ptr_(ptr) {}

  smart_ptr(smart_ptr&& other) noexcept :
      Base(std::move(static_cast<Base&>(other))),
      ptr_(std::exchange(other.ptr_, nullptr)) {}

  smart_ptr& operator=(smart_ptr&& other) noexcept {
    destroy();
    Base::operator=(std::move(other));
    ptr_ = std::exchange(other.ptr_, nullptr);
    return *this;
  }

  [[nodiscard]] element& operator*() const noexcept {
    return *ptr_;
  }

  pointer operator->() const noexcept {
    return ptr_;
  }

  explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }

  [[nodiscard]] pointer get() const noexcept {
    return ptr_;
  }

  void reset(pointer ptr = nullptr) noexcept {
    if (ptr_ != ptr) {
      destroy();
      ptr_ = ptr;
    }
  }

  friend void swap(smart_ptr& lhs, smart_ptr& rhs) noexcept {
    using std::swap;
    swap(lhs.get_deleter(), rhs.get_deleter());
    swap(lhs.ptr_, rhs.ptr_);
  }

  ~smart_ptr() {
    destroy();
  }

private:
  pointer ptr_{};

  void destroy() {
    if (!ptr_) {
      return;
    }
    if constexpr (std::is_array_v<T>) {
      Base::get()(ptr_);
    } else {
      Base::get()(ptr_);
    }
  }

  Deleter& get_deleter() { return Base::get(); }
};

#include <iostream>

int main() {
  // std::cout << 0 << std::endl;
  smart_ptr<int> a(new int(5));
  // std::cout << 10 << std::endl;
  smart_ptr<int> b(std::move(a));
  // std::cout << 20 << std::endl;

  smart_ptr<int[]> array{new int[3]};
}
