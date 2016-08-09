#include <iostream>
#include <exception>
#include "ITOA.H"

#define numSize( x ) (\
   (x < 10) ? 1 : (\
      (x < 100) ? 2 : (\
         (x < 1000) ? 3 : (\
	    (x < 10000) ? 4 : (\
	       (x < 100000) ? 5 : -1)))))

template< unsigned N >
struct CharN
{
  char Buf[N];
};

template< unsigned M, unsigned TagValue >
struct FIXTag
{
  char Tag[numSize( TagValue )];
  CharN<M> Value;

  FIXTag() {
    hfe::ITOA<numSize( TagValue )>( Tag ).update( TagValue );
  }
};

int main()
{
  FIXTag<7,8> x;
  std::cout << "Buffer size is: " << sizeof(x.Tag) << std::endl;
}
