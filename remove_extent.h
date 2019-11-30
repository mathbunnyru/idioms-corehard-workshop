#include <type_traits>

template<typename T>
struct remove_extent {
  using type = T;
};

template<typename T>
struct remove_extent<T[]> {
  using type = T;
};

template<typename T, std::size_t N>
struct remove_extent<T[N]> {
  using type = T;
};

template<typename T>
using remove_extent_t = typename remove_extent<T>::type;

static_assert(std::is_same_v<remove_extent_t<int>, int>);
static_assert(std::is_same_v<remove_extent_t<int[]>, int>);
static_assert(std::is_same_v<remove_extent_t<int[3]>, int>);
