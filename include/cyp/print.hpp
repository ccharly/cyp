#ifndef CYP_PRINT_HPP
#define CYP_PRINT_HPP

#include <cyp/str.hpp>

namespace cyp {

template <typename T>
cyp::enable_if_t<hasattr__str__<T>::value, std::ostream&> operator<<(std::ostream& os, T const& x) {
  os << x.__str__().c_str();
  return os;
}

template <typename T>
void print(T const& x) {
  std::cout << str(x) << std::endl;
}

}

#endif
