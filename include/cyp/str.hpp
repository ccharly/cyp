#ifndef CYP_STR_HPP
#define CYP_STR_HPP

#include <cyp/config.hpp>
#include <cyp/traits.hpp>
#include <cyp/hasattr.hpp>
#include <cyp/object.hpp>
#include <cyp/exceptions.hpp>
#include <cyp/len.hpp>
#include <iostream>
#include <string>

namespace cyp {

class str {
  std::string _str;

  // Constructors
  // -----------------------------------------------------------------------------------------------
  public:

  str() = default;
  str(str&&) = default;
  str(str const&) = default;

  str(const char* x) : _str(x) {
  }

  str(std::string const& x) : _str(x) {
  }

  str(object const& x) : _str(x.__str__().c_str()) {
  }

  template <typename T>
  str(T const& x) {
    // Calls operator= cause we cannot use SFINAE in constructors as it involves at least
    // two overloads.
    (*this) = x;
  }

  // Functions
  // -----------------------------------------------------------------------------------------------
  public:
  const char* c_str() const {
    return _str.c_str();
  }

  template <typename... Args>
  str format(Args&&... args) const {
    std::string formatted; // Resulting string
    std::string parsed; // String parsed inside brackets
    int counter = 0; // Number of matched brackets
    int automatic_field_index = 0; // {} notation index
    //
    enum mode_e { AutomaticFields, ManualFields, NoMode };
    mode_e mode = NoMode;

    // Wrap it into a tuple and map runtime value to static ones
    // TODO: Add named parameters
    auto tuple_args = std::make_tuple(std::forward<Args>(args)...);
    auto get_arg = [&tuple_args](int n) {
      // TODO: Use .__format__ here
      switch (n) {
        case 0: return str("0");
        case 1: return str("1");
        case 2: return str("2");
        case 3: return str("3");
        default:
            throw ValueError("Cannot format more than 9 values for now!");
      }
    };

    // Use char* so we're sure to have a null terminated string (useful when we want
    // to look forward by one character)
    const char* s = c_str();
    for (std::size_t i = 0; i < _str.size(); ++i) {
      char c = s[i];

      // Special token {{ or }} (check before actually update the counter brackets)
      if (counter == 0) {
        // {{ or }}
        if ((c == '{' or c == '}') and s[i + 1] == c) {
          formatted += c;
          // Move by 1 as the loop is moving by 1 too!
          i += 1;
          continue;
        }

        // {} (automatic fields)
        if (c == '{' and s[i + 1] == '}') {
          if (mode == mode_e::NoMode) {
            mode = mode_e::AutomaticFields;
          }
          if (mode != mode_e::AutomaticFields) {
            throw ValueError(
                "cannot switch from automatic field numbering to manual field specification");
          }
          // Get next automatic field
          formatted += get_arg(automatic_field_index++).c_str();
          // Move by 1 as the loop is moving by 1 too!
          i += 1;
          continue;
        }
      }

      // Track matching brackets
      if (c == '{') {
        counter += 1;
        continue;
      }
      if (c == '}') {
        counter -= 1;
        // Check for format tokens
        if (counter == 0) {
          // {...} (manual fields) (only when counter == 0 because it means we've found a closing
          // bracket
          if (len(parsed)) {
            if (mode == mode_e::NoMode) {
              mode = mode_e::ManualFields;
            }
            if (mode != mode_e::ManualFields) {
              throw ValueError(
                  "cannot switch from automatic field numbering to manual field specification");
            }
            // Get named field (TODO)
            std::cout << parsed << std::endl;
            formatted += get_arg(std::stoi(parsed)).c_str();
            // Reset parsed key
            parsed = "";
            continue;
          }
        }
      }

      // Error handling
      if (counter < 0) {
        throw ValueError("Single '}' encountered in format string");
      }

      // Concat
      if (counter > 0) {
        parsed += c;
      } else {
        formatted += c;
      }
    }

    // If counter is not 0, then it means we have an unmatched bracket
    if (counter) {
      throw ValueError("unmatched '{' in format");
    }
    return formatted;
  }

  // Python operators
  // -----------------------------------------------------------------------------------------------
  public:
  static const char* __name__;

  str const& __str__() const {
    return *this;
  }

  template <typename Value>
  bool __contains__(Value const& v) const {
    static_assert(
        std::is_same<Value, std::string>::value
        || std::is_same<Value, char*>::value
        || std::is_same<Value, const char*>::value
        || std::is_same<Value, cyp::str>::value
        , "TypeError: 'in <string>' requires string as left operand");
    return _str.find(v) != std::string::npos;
  }

  str __repr__() const {
    return {};
  }

  // C++ operators
  // -----------------------------------------------------------------------------------------------
  public:

  template <typename T>
  str operator=(str const& x) {
    _str = x._str;
    return *this;
  }

  template <typename T>
  cyp::enable_if_t<is_stringable<T>::value, str>
  operator=(T const& x) {
    _str = std::to_string(x);
    return *this;
  }

  template <typename T>
  cyp::enable_if_t<hasattr__str__<T>::value, str>
  operator=(T const& x) {
    _str = x.__str__();
    return *this;
  }

  str& operator+=(str const& s) {
    _str += s._str;
    return *this;
  }

  str operator*(int n) {
    str s("");
    for (int i = 0; i < n; ++i) {
      s += _str;
    }
    return s;
  }

  operator std::string() {
    return _str;
  }
};

const char* str::__name__ = "str";

/*
std::ostream& operator<<(std::ostream& os, str const& s) {
  os << s.c_str();
  return os;
}
*/

}

#endif
