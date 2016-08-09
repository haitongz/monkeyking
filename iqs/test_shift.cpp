#include <iostream>

int main()
{
  std::cout << "Hugepage size: " << (1<<21) << std::endl;
   int n = 2;
   std::cout << ": " << (n<<3) << std::endl;

   std::cout << ": " << (n<<1 + n<<3) << std::endl;
   std::cout << "n: " << n << std::endl;
   n = 1;
   n = n<<1 + n<<3;
   std::cout << "result: " << n << std::endl;
}
