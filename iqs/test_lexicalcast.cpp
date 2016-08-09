#include <iostream>
#include <boost/lexical_cast.hpp>

int main( int argc, char** argv )
{
   const char* m = "0\0b";
   //   std::string t = m;
   //   t += '\0';
   std::cout << "String is " << m << std::endl;

   int i = boost::lexical_cast<int>( m );
   std::cout << "Got number " << i << std::endl;
}
