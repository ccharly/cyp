#include <cyp/print.hpp>
#include <cyp/tuple.hpp>
#include <cyp/static_operators.hpp>
#include <cyp/cxx.hpp>

struct foo {
  const char* __str__() const {
    return "foo";
  }

  bool __eq__(foo const&) const {
    return false;
  }
};

int main() {
  using cyp::print;

  auto t = cyp::make_tuple(foo(), "lol", 3.3f);

  if (cyp::in(3.3f, t)) {
    std::cout << "in" << std::endl;
  }

  if (cyp::eq(foo(), 10)) {
  }

  std::cout << t[1] << std::endl;

  std::cout << t << std::endl;
  //cyp::print(t);

  //auto x = t[0].as<float>();

  //print(t.get<std::string>(1));

  return 0;
}
