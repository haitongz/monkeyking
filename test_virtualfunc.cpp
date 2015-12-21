#include <iostream>

using namespace std;

class A {
public:
  A() {
    cout << "ctor of A calls virtual function f()." << endl;
    f();
  }

  virtual void n() {
    cout << "function n() of class A." << endl;
    f();
  }

  void m() {
    cout << "function m() of class A." << endl;
  }

  virtual void f() {
    cout << "virtual function f() of class A." << endl;
        // m();
  }

  virtual ~A() {
//         cout << "virtual dtor of class A." << endl;
  }
};

class B : public A {
public:
  void n() {
    cout << "function n() of class B" << endl;
  }

  int n(int a) {
    cout << "function n(int) of class B sees " << a << endl;
    return a;
  }

  virtual void f() {
    cout << "virtual function f() of class B." << endl;
  }

      /*int */
  void m() {
    cout << "function m() of class B." << endl;
  }
#if 0
      void m(int a = 9) {
         cout << "function m(int) of class B sees " << a << endl;
      }
#endif

  virtual ~B() {
  //       cout << "virtual dtor of class B." << endl;
  }
};

class C : public B {
public:
      /* if overiding virtual method, return type must be identical to or covariant with parent one */
  int n(int a = 8) {
    cout << "virtual function n() of class C sees " << a << endl;
    return a;
  }

      // function overiding
  int m(int a) {
    cout << "function m() of class C sees " << a << endl;
    return a;
  }

      // overiding virtual function
  virtual void f() {
    cout << "virtual function f() of class C." << endl;
        //	A::m(); // co-exist with int m(int)
    m(8);
  }

      void f(int a) {
    //     cout << "overloaded function f() of class C." << endl;
      }

#if 0
      C() {
         cout << "test point: ctor of C." << endl;
      }
#endif
};

int main() {
   /*
   A * lPtr = new C;
   lPtr->n();*/
  B* lB = new B;
  lB->f();
  lB->m();

  A* lA = new B;
  lA->f();
  lA->m();

  A a;
  B b;
  a = b;
  a.f();

  delete lA;
  delete lB;

#if 0
   A * lPtr2 = new B;
   lPtr2->n();
   B * lPtr3 = new C;
   lPtr3->n();
#endif
}
