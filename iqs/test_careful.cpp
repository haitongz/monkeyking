#include <iostream>

struct B
{
   void Go() { std::cout << "B::Go()" << std::endl; }
   void Back() { std::cout << "B::Back()" << std::endl; }
};

struct C : public B
{
   void Go() { std::cout << "C::Go()" << std::endl; }
};

struct D : public B
{
   void Back() { std::cout << "D::Back()" << std::endl; }
};

void f()
{
   B * bd = new D;
   B * bc = new C;
   D d;

   bd->Go();
   bd->Back();
   bc->Go();
   bc->Back();
   d.Go();

   delete bd;
   delete bc;
}

int main()
{
   f();
   return 0;
}
