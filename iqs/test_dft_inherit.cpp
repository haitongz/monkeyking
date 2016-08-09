#include <iostream>

class B
{
};

class D1
{
   public:
      int d1;
};

class D2 : public B, D1
{
};

int main()
{
   D2 d2;
   std::cout << d2.d1 << std::endl;
}
