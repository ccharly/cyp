#ifndef CYP_LEN_HPP
#define CYP_LEN_HPP

#include <cstddef>
#include <cyp/str.hpp>

namespace cyp {

inline std::size_t len(std::string const& s) {
  return s.length();
}

inline std::size_t len(const char* s) {
  return ::strlen(s);
}

inline std::size_t len(char) {
  return 1;
}

}

#endif
