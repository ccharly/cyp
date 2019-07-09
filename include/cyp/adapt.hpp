#ifndef CYP_ADAPT_HPP
#define CYP_ADAPT_HPP

#include <cyp/config.hpp>

namespace cyp {

template <typename T>
struct adapt;

template <>
struct adapt<int> {

};

template <typename T>
struct is_adaptable {
  template <typename U>
  static auto maybe(U*)  -> decltype(sizeof(adapt<U>), true_t{});
  static auto maybe(...) -> false_t;
  enum { value = decltype(maybe(static_cast<T*>(0))){} };
};

cyp::enable_if_t<is_adaptable<T>::value, adapt<T>> adapt(T const& x) {
  return {x};
}

} // ::cyp

#endif
