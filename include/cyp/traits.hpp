#ifndef CYP_TRAITS_HPP
#define CYP_TRAITS_HPP

#include <cyp/exceptions.hpp>
#include <type_traits>
#include <limits>

namespace cyp {

// Basic traits
// -----------------------------------------------------------------------------------------------

template <typename T>
using ref_t = std::reference_wrapper<T>;

template <int N>
using static_int_t = std::integral_constant<int, N>;

template <bool B>
using static_bool_t = std::integral_constant<bool, B>;

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template <bool B, typename T = void>
using disable_if_t = typename std::enable_if<not B, T>::type;

using true_t  = std::true_type;
using false_t = std::false_type;

template <typename T>
struct is_stringable {
  enum { value = std::is_floating_point<T>::value || std::is_integral<T>::value };
};

template <typename Lhs, typename Rhs>
struct is_equal_comparable {
  template <typename U>
  static auto maybe(U*)  -> decltype(std::declval<U>() == std::declval<Rhs>(), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe(static_cast<Lhs*>(0))){} };
};

namespace detail {

// Static to runtime helpers
// -----------------------------------------------------------------------------------------------

constexpr std::size_t as_static_int_max_case = 3;

struct no_return_type_t {};

template <typename R, std::size_t MaxCase, std::size_t Shift>
struct as_static_int;

template <typename R, std::size_t Shift>
struct as_static_int<R, 0, Shift> {
  template <typename F>
  static R then(std::size_t n, F f) {
    (void)n;
    (void)f;
    throw IndexError();
  }
};

template <typename R, std::size_t Shift>
struct as_static_int<R, 1, Shift> {
  template <typename F>
  static R then(std::size_t n, F f) {
    switch (n) {
      case 0: return f(static_int_t<Shift + 0>{});
      default: throw IndexError();
    }
  }
};

template <typename R, std::size_t Shift>
struct as_static_int<R, 2, Shift> {
  template <typename F>
  static R then(std::size_t n, F f) {
    switch (n) {
      case 0: return f(static_int_t<Shift + 0>{});
      case 1: return f(static_int_t<Shift + 1>{});
      default: throw IndexError();
    }
  }
};

template <typename R, std::size_t MaxCase, std::size_t Shift>
struct as_static_int {
  template <typename F>
  static R then(std::size_t n, F f) {
    switch (n) {
      case 0: return f(static_int_t<Shift + 0>{});
      case 1: return f(static_int_t<Shift + 1>{});
      case 2: return f(static_int_t<Shift + 2>{});
      default:
          return as_static_int<
              // The return type
              R,
              // Calculate new max case
              MaxCase - as_static_int_max_case,
              // Calculate new shift case
              Shift + as_static_int_max_case
              // Same goes for the index
              >::then(n - as_static_int_max_case, f);
    }
  }
};

} // ::detail

template <typename R, std::size_t MaxCase, typename F>
R as_static_int(std::size_t n, F f) {
  return detail::as_static_int<R, MaxCase, 0>::then(n, f);
}

template <typename R, typename F>
R as_static_int(std::size_t n, F f) {
  return detail::as_static_int<R, std::numeric_limits<std::size_t>::max(), 0>::then(n, f);
}

// Constexpr statements
// -----------------------------------------------------------------------------------------------

template <std::size_t... N> struct index_sequence {};

namespace detail {

  template <typename A, typename B> struct append;
  template <typename A, typename B> using append_t = typename append<A, B>::type;

  template <std::size_t... A, std::size_t... B>
  struct append<index_sequence<A...>, index_sequence<B...>> { using type = index_sequence<A..., B...>; };

  template <std::size_t A, std::size_t B, bool Min = A < B> struct min;
  template <std::size_t A, std::size_t B> struct min<A, B, true>  { enum { value = A }; };
  template <std::size_t A, std::size_t B> struct min<A, B, false> { enum { value = B }; };

} // .detail

template <std::size_t N, std::size_t Which = detail::min<6, N>::value> struct make_index_sequence;
template <std::size_t N> using make_index_sequence_t = typename make_index_sequence<N>::type;

template <std::size_t N>
struct make_index_sequence<N, 6>
{
  using lhs  = make_index_sequence_t<N - 6>;
  using rhs  =        index_sequence<N - 6, N - 5, N - 4, N - 3, N - 2, N - 1>;
  using type = detail::append_t<lhs, rhs>;
};

template <std::size_t N> struct make_index_sequence<N, 5> { using type = index_sequence<0, 1, 2, 3, 4>; };
template <std::size_t N> struct make_index_sequence<N, 4> { using type = index_sequence<0, 1, 2, 3>; };
template <std::size_t N> struct make_index_sequence<N, 3> { using type = index_sequence<0, 1, 2>; };
template <std::size_t N> struct make_index_sequence<N, 2> { using type = index_sequence<0, 1>; };
template <std::size_t N> struct make_index_sequence<N, 1> { using type = index_sequence<0>; };
template <std::size_t N> struct make_index_sequence<N, 0> { using type = index_sequence<>; };

template <template <class...> class Container, typename... Types, std::size_t... N, typename F>
void for_constexpr(Container<Types...> const& x, F f, index_sequence<N...> const&) {
  (void)std::initializer_list<int>{ ((void)f(std::get<N>(x)), 0)... };
}

template <template <class...> class Container, typename... Types, typename F>
void for_constexpr(Container<Types...> const& x, F f) {
  for_constexpr(x, f, make_index_sequence_t<sizeof...(Types)>());
}

template <template <class...> class Container, typename... Types, std::size_t... N, typename F>
void for_constexpr_i(Container<Types...> const& x, F f, index_sequence<N...> const&) {
  (void)std::initializer_list<int>{ ((void)f(std::get<N>(x, static_int_t<N>{})), 0)... };
}

template <template <class...> class Container, typename... Types, typename F>
void for_constexpr_i(Container<Types...> const& x, F f) {
  for_constexpr_i(x, f, make_index_sequence_t<sizeof...(Types)>());
}

template <template <class...> class Container, typename... Types, typename F>
bool any_constexpr(Container<Types...> const& x, F f) {
  bool maybe = false;
  for_constexpr(x, [&](auto e) {
      maybe = maybe || f(e);
      });
  return maybe;
}

template <template <class...> class Container, typename... Types, typename F>
bool any_constexpr_i(Container<Types...> const& x, F f) {
  bool maybe = false;
  for_constexpr(x, [&](auto e, auto i) {
      maybe = maybe || f(e, i);
      });
  return maybe;
}

template <template <class...> class Container, typename... Types, typename F>
bool all_constexpr(Container<Types...> const& x, F f) {
  bool maybe = true;
  for_constexpr(x, [&](auto e) {
      maybe = maybe && f(e);
      });
  return maybe;
}

template <template <class...> class Container, typename... Types, typename F>
bool all_constexpr_i(Container<Types...> const& x, F f) {
  bool maybe = true;
  for_constexpr(x, [&](auto e, auto i) {
      maybe = maybe && f(e, i);
      });
  return maybe;
}

} // ::cyp

#endif
