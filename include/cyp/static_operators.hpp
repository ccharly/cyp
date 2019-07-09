#ifndef CYP_STATIC_OPERATORS_HPP
#define CYP_STATIC_OPERATORS_HPP

#include <cyp/config.hpp>
#include <cyp/traits.hpp>
#include <cyp/hasattr.hpp>

namespace cyp {

template <typename T>
str __str__(T const& x) {
  static_assert(hasattr__str__<T>::value, "__str__ not implemented");
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
struct hasattr__eq__case {
  enum {
    lhs  =     hasattr__eq__<Lhs, Rhs>::value && not hasattr__eq__<Rhs, Lhs>::value,
    rhs  = not hasattr__eq__<Lhs, Rhs>::value &&     hasattr__eq__<Rhs, Lhs>::value,
    both =     hasattr__eq__<Lhs, Rhs>::value &&     hasattr__eq__<Rhs, Lhs>::value,
    none = not hasattr__eq__<Lhs, Rhs>::value && not hasattr__eq__<Rhs, Lhs>::value,
  };
};

} // ::detail

// In python, == is always evaluating to something, so if there is overloads,

// -------------------------------------------------------------------------------------------------
// Lhs has __eq__ overload

template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::lhs, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return lhs.__eq__(rhs);
}

// -------------------------------------------------------------------------------------------------
// Rhs has __eq__ overload

template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::rhs, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return rhs.__eq__(lhs);
}

// -------------------------------------------------------------------------------------------------
// Both have __eq__ overloads (pick lhs)

template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::both, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  // Call whatever here
  return lhs.__eq__(rhs);
}

// -------------------------------------------------------------------------------------------------
// None have __eq__ overloads

// Case when we can use ==
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::is_equal_comparable<Lhs, Rhs>::value, bool>
__eq__case_none(Lhs const& lhs, Rhs const& rhs) {
  return lhs == rhs;
}

// When there is nothing to do
template <typename Lhs, typename Rhs>
cyp::disable_if_t<cyp::is_equal_comparable<Lhs, Rhs>::value, bool>
__eq__case_none(Lhs const&, Rhs const&) {
  return false;
}

// Dispatch to one of the default case (== or not)
template <typename Lhs, typename Rhs>
cyp::enable_if_t<cyp::detail::hasattr__eq__case<Lhs, Rhs>::none, bool>
__eq__(Lhs const& lhs, Rhs const& rhs) {
  return __eq__case_none(lhs, rhs);
}

// Shortand
template <typename Lhs, typename Rhs>
bool eq(Lhs const& lhs, Rhs const& rhs) {
  return __eq__(lhs, rhs);
}

// -------------------------------------------------------------------------------------------------

} // ::cyp

#endif
