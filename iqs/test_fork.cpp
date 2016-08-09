#include <iostream>
#include <unistd.h>

int main()
{
   fork();
   //  std::cout << "my id=" << getpid() << " and my parent id=" << getppid() << std::endl;

   fork();
   // std::cout << "my id=" << getpid() << " and my parent id=" << getppid() << std::endl;

   fork();
   // std::cout << "my id=" << getpid() << " and my parent id=" << getppid() << std::endl;

   std::cout << "abc..." << std::endl;
}
