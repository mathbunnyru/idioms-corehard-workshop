#include <type_traits>

template<typename T>
inline constexpr bool is_array_v = false;

template<typename T>
inline constexpr bool is_array_v<T[]> = true;

template<typename T, std::size_t N>
inline constexpr bool is_array_v<T[N]> = true;

static_assert(!is_array_v<int>);
static_assert(is_array_v<int[]>);
static_assert(is_array_v<int[3]>);
