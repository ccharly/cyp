#include <cyp/str.hpp>
#include <cyp/print.hpp>

int main() {
  using cyp::print;

  {
    auto s = cyp::str("lol");
    print(s);
  }
  {
    auto s = cyp::str(1);
    print(s);
  }
  {
    auto s = cyp::str(3.14);
    print(s);
  }
  {
    try {
      auto s = cyp::str("{{test {{{0}}} {2} omg}}{0}").format();
      print(s);
    } catch (cyp::Exception const& e) {
      print(e);
    }
  }

  return 0;
}
