#ifndef CYP_TYPED_OBJECT_HPP
#define CYP_TYPED_OBJECT_HPP

#include <iostream>
#include <string>
#include <cyp/hasattr.hpp>
#include <cyp/str.hpp>

namespace cyp {

class str;

template <typename T>
class typed_object {
  public:
  T& cast() {
    return *static_cast<T*>(this);
  }

  T const& cast() const {
    return *static_cast<const T*>(this);
  }

  public:
  static const str __name__ = []() { return typeid(T).name(); }();

  str __repr__() const {
    return cyp::str("<{} instance at {}>", cast().__name__, this);
  }
};

}

#endif
