#ifndef CYP_OBJECT_HPP
#define CYP_OBJECT_HPP

#include <cyp/str.hpp>
#include <iostream>
#include <string>

namespace cyp {

class str;

class object {
  public:
  virtual str const& __repr__() const;
  virtual str const& __str__() const;
};

}

#endif
