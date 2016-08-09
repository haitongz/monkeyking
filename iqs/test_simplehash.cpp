#include <iostream>

int main()
{
   size_t hashSize = 200000;
   size_t hashVal = 1;

   for( ; hashVal < hashSize; hashVal *= 2 );

   size_t mask = hashVal-1;
   std::cout << "mask=" << mask << std::endl;

   for( size_t i = 0; i < hashSize; ++i ) {
      std::cout << "orderId=" << i << ",index=" << (i&mask) << std::endl;
   }
}
