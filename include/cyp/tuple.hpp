#ifndef CYP_TUPLE_HPP
#define CYP_TUPLE_HPP

#include <cyp/any.hpp>
#include <cyp/static_operators.hpp>
#include <utility>
#include <vector>

namespace cyp {

template <typename... Types>
class tuple : public std::tuple<Types...> {
  public:
  using std::tuple<Types...>::tuple;

  static constexpr int static_size = sizeof...(Types);

  public:

  cyp::any_ref operator[](std::size_t index) {
    std::vector<any_ref> refs;
    for_constexpr(*this, [&](auto x) {
        std::cout << "for: " << typeid(x).name() << std::endl;
        refs.emplace_back(x);
        });
    return refs.at(index);
  }

  cyp::str __str__() const {
    auto comma = "";
    cyp::str str;
    str += "(";
    for_constexpr(*this, [&](auto x) {
        str += comma;
        str += cyp::str(x);
        comma = ", ";
        });
    str += ")";
    return str;
  }

  template <typename Value>
  bool __contains__(Value const& v) const {
    return any_constexpr(*this, [&](auto x) {
        return cyp::__eq__(x, v);
        });
  }

  template <typename... Types2>
  bool __eq__case(true_t, std::tuple<Types2...> const& other) const {
    return all_constexpr_i(*this, [&](auto, auto i) {
        return std::get<decltype(i)::value>(*this) == std::get<decltype(i)::value>(other);
        });
  }

  template <typename... Types2>
  bool __eq__case(false_t, std::tuple<Types2...> const& other) const {
    (void)other;
    return false;
  }

  template <typename... Types2>
  bool __eq__(std::tuple<Types2...> const& other) const {
    return __eq__case(static_bool_t<sizeof...(Types) == sizeof...(Types2)>{}, other);
  }
};

template <typename... Types>
tuple<Types...> make_tuple(Types&&... args) {
  return tuple<Types...>(std::forward<Types>(args)...);
}

}

#endif
