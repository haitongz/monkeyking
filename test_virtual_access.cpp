#include <iostream>

class B {
public:
  virtual int f() {
    std::cout << "B::f()" << std::endl;
  }

  int c() const {
    std::cout << "Const method" << std::endl;
    return 0;
  }

  int c() {
    std::cout << "Const method overloaded" << std::endl;
    return 1;
  }
};

class D : public B {
private:
  int f() {
    std::cout << "D::f()" << std::endl;
  }
};

int main() {
  D d;
  B* pb = &d;
  D* pd = &d;

  pb->f(); // OK: B::f() is public
  //   pd->f(); // error: D::f() is private
  std::cout << pb->c() << std::endl;
}
