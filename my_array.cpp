#include <algorithm>
#include <iostream>

template<typename C>
void print(const C& c) {
  for(const auto& s : c) {
    std::cout << s << ' ';
  }
  std::cout << '\n';
}

template<typename T, size_t Size>
struct my_array {
  T data[Size];

  T& operator[](size_t i) {
    return data[i];
  }

  const T* begin() const { return std::begin(data); }
  const T* end() const { return std::end(data); }
};

static_assert(std::is_pod_v<my_array<int, 3>>);
static_assert(std::is_trivial_v<my_array<int, 3>>);
static_assert(std::is_aggregate_v<my_array<int, 3>>);

int main() {
  my_array<int, 3> a{};
  a[0] = 1;
  print(a);
}
