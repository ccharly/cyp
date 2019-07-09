#ifndef CYP_FOR_CONSTEXPR_HPP
#define CYP_FOR_CONSTEXPR_HPP

#include <cyp/exceptions.hpp>
#include <type_traits>
#include <limits>

namespace cyp {

template <typename T>
using ref_t = std::reference_wrapper<T>;

template <int N>
using static_int_t = std::integral_constant<int, N>;

template <bool B>
using static_bool_t = std::integral_constant<bool, B>;

struct true_t  : std::true_type {};
struct false_t : std::false_type {};

template <typename T>
struct is_stringable {
  enum { value = std::is_floating_point<T>::value || std::is_integral<T>::value };
};

template <typename T>
struct has___str__ {
  template <typename U>
  static auto maybe(U*)  -> decltype(std::declval<U>().__str__(), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe<T>(0)){} };
};

namespace detail {

constexpr std::size_t as_static_int_max_case = 3;

struct no_return_type_t {};

template <typename R, std::size_t MaxCase, std::size_t Shift>
struct as_static_int;

template <typename R, std::size_t Shift>
struct as_static_int<R, 0, Shift> {
  template <typename F>
  static R then(std::size_t n, F f) {
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

} // ::cyp

#endif
