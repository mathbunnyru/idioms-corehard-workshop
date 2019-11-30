#include <type_traits>
#include <utility>

// Could use [[no_unique_address]]

template<typename T, int Idx = 0, bool UseEbo = !std::is_final_v<T> && std::is_empty_v<T>>
struct ebo_helper;

template<typename T, int Idx>
struct ebo_helper<T, Idx, true> : private T {
  template<typename U>
  constexpr explicit ebo_helper(U&& t) : T{std::forward<U>(t)} {}
  constexpr T& get() { return *this; }
};

template<typename T, int Idx>
struct ebo_helper<T, Idx, false> {
  template<typename U>
  constexpr explicit ebo_helper(U&& t) : t_{std::forward<U>(t)} {}
  constexpr T& get() { return t_; }
private:
  T t_;
};
