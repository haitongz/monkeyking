#include <iostream>

class A {
public:
  class Inner {
  public:
    Inner(A& parent)
      : ref(parent.a) {
    }

  private:
    friend class B;
    int& ref;
  };

  A() : a(0), i(*this) {
  }

  Inner& getInner() {
    return i;
  }

  int getNum() const {
    return a;
  }

private:
  int a;
  Inner i;
};

class B {
public:
  void changeNum(A& a, int x) {
    A::Inner& i = a.getInner();
    i.ref = x;
  }
};

int main() {
  A a;
  std::cout << "Original value: " << a.getNum() << std::endl;

  B b;
  b.changeNum(a, 10);
  std::cout << "New value: " << a.getNum() << std::endl;

  return 0;
}
