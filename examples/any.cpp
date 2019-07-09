#include <cyp/print.hpp>
#include <cyp/any.hpp>

struct foobar {
  foobar() {
    std::cout << "foobar: " << (void*)this << std::endl;
  }
  ~foobar() {
    std::cout << "~foobar: " << (void*)this << std::endl;
  }
};

struct big {
  int a, b, c, d, e;
};

int main() {
  using cyp::print;

  cyp::any x;
  //x = 10;
  //x = 3.14;
  //print(x.get<double>());
  x = foobar();
  //print(sizeof(big));
  //x = big();
  //x = true;
  //print(x.get<bool>());

  return 0;
}
