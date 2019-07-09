#ifndef CYP_STATIC_OPERATORS_HPP
#define CYP_STATIC_OPERATORS_HPP

#include <cyp/config.hpp>
#include <cyp/traits.hpp>
#include <cyp/hasattr.hpp>

namespace cyp {

template <typename T>
str __str__(T const& x) {
  static_assert(hasattr__str__<T>::value, "");
  return x.__str__();
}

// -------------------------------------------------------------------------------------------------

template <typename T, typename Value>
bool __contains__(T const& x, Value const& v) {
  static_assert(hasattr__contains__<T, Value>::value, "");
  return x.__contains__(v);
}

template <typename T, typename Value>
bool in(Value const& v, T const& x) {
  // Flip the arguments here (v in x)
  return __contains__(x, v);
}

// -------------------------------------------------------------------------------------------------

namespace detail {

template <typename Lhs, typename Rhs>
struct hasttr__eq__case {
  enum {
    lhs  =  hasattr__eq__<Lhs, Rhs>::value && !hasattr__eq__<Rhs, Lhs>::value,
    rhs  = !hasattr__eq__<Lhs, Rhs>::value &&  hasattr__eq__<Rhs, Lhs>::value,
    both =  hasattr__eq__<Lhs, Rhs>::value &&  hasattr__eq__<Rhs, Lhs>::value,
    none = !hasattr__eq__<Lhs, Rhs>::value && !hasattr__eq__<Rhs, Lhs>::value,
  };
};

} // ::detail

// In python, == is always evaluating to something, so if there is overloads,
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::lhs, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return lhs.__eq__(rhs);
}

// Rhs has __eq__ overload
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::rhs, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return rhs.__eq__(lhs);
}

// Both have __eq__ overloads
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::both, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  // Call whatever here
  return lhs.__eq__(rhs);
}

// None have __eq__ overloads
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::none, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return false;
}

// -------------------------------------------------------------------------------------------------

} // ::cyp

#endif
