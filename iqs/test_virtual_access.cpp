#include <iostream>

using namespace std;

class A {
 public:
  virtual void f(int& x) {
    cout << "A::f()" << endl;
  }
};

class B : public A {
 public:
  void f(int& x) {
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

class C : public B {
 public:
  virtual void f(const int& x) {
    // Tricky: C++ allows functions to be overloaded on the basis of constness
    // of parameters only if the const parameter is a reference or a pointer.
    // So this shadows B::f()??
    cout << "C::f()" << endl;
  }
};

class D : public B {
 private:
  int f() {
    cout << "D::f()" << endl;
  }
};

void fun(const int &i) {
  cout << "fun(const int&) called" << endl;
}

void fun(int& i) {
  cout << "fun(int&) called" << endl;
}

int main(int argc, char** argv) {
  D d;
  B* pb = &d;
  D* pd = &d;

  // pb->f();                       // OK: B::f() is public
  //   pd->f(); // error: D::f() is private
  cout << pb->c() << endl;

  int j = 1;
  A* pA = new B;
  pA->f(j);
  A a;
  a.f(j);
  B b;
  b.f(j);
  A a2 = b;
  a2.f(j);

  B* pB = new C;
  pB->f(j);

  C c;
  c.f(j);

  const int i = 10;
  fun(i);

  return 0;
}
