#include <string>
#include <type_traits>
#include <iostream>

template<typename T>
struct wrapper {
  T data_;
};

template<typename T>
void swap(
  wrapper<T>& lhs,
  wrapper<T>& rhs
) noexcept(std::is_nothrow_swappable_v<T>) {
  using std::swap;
  swap(lhs.data_, rhs.data_);
}

struct X {};

void swap(X&, X&) {
  std::cout << "my swap\n";
}

int main() {
  wrapper<std::string> s1, s2;
  swap(s1, s2);

  wrapper<X> x1, x2;
  swap(x1, x2);

  wrapper<int> i1, i2;
  swap(i1, i2);
}
