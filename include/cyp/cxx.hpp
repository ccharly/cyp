#ifndef CYP_CXX_HPP
#define CYP_CXX_HPP

#include <cyp/config.hpp>
#include <cyp/traits.hpp>
#include <cyp/hasattr.hpp>

// In python, == is always evaluating to something, so if there is overloads, we try to call
// .__eq__ from lhs (or rhs), the default case evaluates to false
/*
template <typename Lhs, typename Rhs>
bool operator==(Lhs const& lhs, Rhs const& rhs) {
  return cyp::__eq__(lhs, rhs);
}
*/


#endif
