#include <type_traits>

struct A{};

struct B{B() = default;};

struct C{
    C() {}
};

static_assert(std::is_trivially_constructible_v<A>);
static_assert(std::is_trivially_constructible_v<B>);
static_assert(!std::is_trivially_constructible_v<C>);

static_assert(std::is_nothrow_constructible_v<A>);
static_assert(std::is_nothrow_constructible_v<B>);
static_assert(!std::is_nothrow_constructible_v<C>);

struct D{
    D(const D&) = default;
};

struct E{
    E(E&&) = default;
};

static_assert(std::is_copy_constructible_v<A>);
static_assert(std::is_copy_constructible_v<D>);
static_assert(!std::is_copy_constructible_v<E>);

static_assert(std::is_copy_assignable_v<A>);
static_assert(std::is_copy_assignable_v<D>);
static_assert(!std::is_copy_assignable_v<E>);

static_assert(std::is_move_constructible_v<A>);
static_assert(std::is_move_constructible_v<D>);
static_assert(std::is_move_constructible_v<E>);

static_assert(std::is_move_assignable_v<A>);
static_assert(std::is_move_assignable_v<D>);
static_assert(!std::is_move_assignable_v<E>);
