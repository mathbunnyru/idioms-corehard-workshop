#include <iostream>

template<typename Derived>
class equality_comparable {
  friend bool operator==(const Derived& lhs, const Derived& rhs) {
    return lhs.equal_to(rhs);
  }

  friend bool operator!=(const Derived& lhs, const Derived& rhs) {
    return !lhs.equal_to(rhs);
  }
};

template<typename T>
class smart_ptr: equality_comparable<smart_ptr<T>> {
public:
  using pointer = T*;

  smart_ptr(pointer ptr) : ptr_(ptr) {}

  bool equal_to(const smart_ptr& other) const {
    return ptr_ == other.ptr_;
  }

private:
  T* ptr_;
};

int main() {
  int a = 0;
  int b = 0;
  smart_ptr<int> a_ptr(&a);
  smart_ptr<int> b_ptr(&b);
  smart_ptr<int> a_ptr_copy(&a);

  std::cout << (&a == &b) << " " << (a_ptr == b_ptr) << " " << (a_ptr == a_ptr_copy);
}
