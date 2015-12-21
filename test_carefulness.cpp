#include <iostream>

struct B {
   void go() { std::cout << "B::go()" << std::endl; }
   void back() { std::cout << "B::back()" << std::endl; }
};

struct C : public B {
   void go() { std::cout << "C::go()" << std::endl; }
};

struct D : public B {
   void back() { std::cout << "D::back()" << std::endl; }
};

void f() {
   B* bd = new D;
   B* bc = new C;
   D d;

   bd->go();
   bd->back();
   bc->go();
   bc->back();
   d.go();

   delete bd;
   delete bc;
}

int main() {
   f();
   return 0;
}
