#include <iostream>
#include <memory>

class B {
public:
  virtual void f(int i = 0) {
    std::cout << i << std::endl;
  }
};

class D : public B {
public:
  void f(int i = 10) {
    std::cout << i << std::endl;
  }
};

class B1 {
};

class D1 {
public:
  int d1;
};

class D2 : public B1, D1 {
};

int main(int argc, char** argv) {
  std::auto_ptr<B> b(new D);
  b->f();
  std::auto_ptr<D> d(new D);
  d->f();
  
  D2 d2;
  std::cout << d2.d1 << std::endl;
}
