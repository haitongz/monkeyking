#include <iostream>

class A
{
   public:
      void show() {
         std::cout << "show" << std::endl;
      }
};

int main( )
{
   ((A*)(NULL))->show();
   return 0;
}
