#include <iostream>

int abs(int n)
{
   std::cout << "int gets called" << std::endl;
   return n;
}

long abs(long n)
{
   std::cout << "long gets called" << std::endl;
   return n;
}

double abs(double n)
{
   std::cout << "double gets called" << std::endl;
   return n;
}

float abs(float n)
{
   std::cout << "float gets called" << std::endl;
   return n;
}

int main()
{
   std::cout << abs(-10) << std::endl;
   return 0;
}
