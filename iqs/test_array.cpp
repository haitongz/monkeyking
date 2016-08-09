#include <string>
#include <iostream>

class Ab
{
   public:
      virtual int crap() = 0;
};

template< typename U >
bool isAbstract( U (*array)[1] )
{
}

int main( int argc, char** argv )
{
   int array[1];
   array[0] = -1;
   Ab array2[1];

   bool ret = isAbstract<int>( NULL );
   ret = isAbstract<Ab>( NULL );
   ret = isAbstract<int>( &array );
   ret = isAbstract<Ab>( &array2 );
}
