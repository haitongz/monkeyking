#include <iostream>

struct Base
{
   Base() { std::cout << "One Base created!" << std::endl; }
};

struct Sub1 : public virtual Base
{
   Sub1() : Base() { std::cout << "One Sub1 created!" << std::endl; }
};

struct Sub2 : public /*virtual */Base
{
   Sub2() : Base() { std::cout << "One Sub2 created!" << std::endl; }
};

class Multi : public Sub1, public Sub2
{
};

struct professor
{
   ~professor() {
      std::cout << "professor\n";
   }
};

struct researcher
{
   ~researcher() {
      std::cout << "researcher\n";
   }
};

struct teacher :  public professor
{
   ~teacher() {
      std::cout << "teacher\n";
   }
};

struct myprof : public teacher,
                public virtual researcher
{
   ~myprof() { std::cout << "myprof\n"; }
};

int main()
{
   //   Multi m;
   myprof m;
   return 0;
}
