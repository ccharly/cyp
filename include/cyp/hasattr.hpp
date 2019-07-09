#ifndef CYP_HASATTR_HPP
#define CYP_HASATTR_HPP

#include <cyp/traits.hpp>

namespace cyp {

template <typename T>
struct hasattr__str__ {
  template <typename U>
  static auto maybe(U*)  -> decltype(std::declval<U>().__str__(), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe(static_cast<T*>(0))){} };
};

template <typename T, typename Value>
struct hasattr__contains__ {
  template <typename U>
  static auto maybe(U*)  -> decltype(std::declval<U>().__contains__(std::declval<Value>()), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe(static_cast<T*>(0))){} };
};

template <typename Lhs, typename Rhs>
struct hasattr__eq__ {
  template <typename U>
  static auto maybe(U*)  -> decltype(std::declval<U>().__eq__(std::declval<Rhs>()), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe(static_cast<Lhs*>(0))){} };
};

} // ::cyp

#endif
