#include <type_traits>

template<typename T>
struct is_array : std::false_type {};

template<typename T>
struct is_array<T[]> : std::true_type {};

template<typename T, std::size_t N>
struct is_array<T[N]> : std::true_type {};

template<typename T>
inline constexpr bool is_array_v = is_array<T>::value;

static_assert(!is_array_v<int>);
static_assert(is_array_v<int[]>);
static_assert(is_array_v<int[3]>);
