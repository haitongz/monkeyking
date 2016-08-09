#include <iostream>

class B
{
   public: int a;
   protected: int b;
   private: int c;
};

class D : public B
{
   friend class F;
   int d;
};

class F
{
   D derived;
   public:
      void test() {
         derived.a = 1;
         derived.b = 2;
         derived.c = 3;
         derived.d = 4;

         std::cout << "a is" << derived.a << std::endl;
         std::cout << "b is" << derived.b << std::endl;
         std::cout << "c is" << derived.c << std::endl;
         std::cout << "d is" << derived.d << std::endl;
      }
};

int main()
{
   F f;

   f.test();
   return 0;
}
