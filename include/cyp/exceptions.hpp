#ifndef CYP_EXCEPTIONS_HPP
#define CYP_EXCEPTIONS_HPP

#include <string>
#include <exception>

namespace cyp {

class str;

class Exception : public std::exception {
  std::string _more;
  std::string _what;

  public:
  Exception() {
    _what = __name__();
  }

  Exception(const char* s) : _more(s) {
    _what = __name__();
    _what += ": " + _more;
  }

  Exception(std::string const& s) : Exception(s.c_str()) {
  }

  virtual ~Exception() {
  }

  public:
  const char* __str__() const {
    return what();
  }

  public:
  virtual const char* __name__() const {
    return "Exception";
  }

  virtual const char* what() const noexcept {
    return _what.c_str();
  }
};

template <typename T>
class TypedException : public Exception {
  using Exception::Exception;

  public:
  virtual const char* __name__() const {
    return typeid(T).name();
  }
};

class KeyError : public TypedException<KeyError> {
  using TypedException<KeyError>::TypedException;
};

class ValueError : public TypedException<ValueError> {
  using TypedException<ValueError>::TypedException;
};

class IndexError : public TypedException<IndexError> {
  using TypedException<IndexError>::TypedException;
};

class TypeError : public TypedException<TypeError> {
  using TypedException<TypeError>::TypedException;
};

class NotImplementedError : public TypedException<NotImplementedError> {
  using TypedException<NotImplementedError>::TypedException;
};

class UndefinedError : public TypedException<UndefinedError> {
  using TypedException<UndefinedError>::TypedException;
};

}

#endif
