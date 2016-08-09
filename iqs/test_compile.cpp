#include <iostream>

template <class T>
void foo(T op1, T op2)
{
}

template <class T>
struct sum
{
   static void foo(T op1, T op2) {
      std::cout << "sum= " << op2 << std::endl;
   }
};

int main()
{
   foo(1, 3);
   foo<int>(1, '3');
   sum::foo(1, 2);
   return 0;
}
