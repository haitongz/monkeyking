#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

int main()
{
   // Given a variable str of type std::string,
   // which one of the following statements outputs the string backwards?
   std::string test = "peng xu is so handsome...";

   //   std::copy(test.reverse(), std::unary_function(std::cout));
   //   std::reverse(test); std::cout << test;

   //   for (unsigned int i = test.size(); i > 0; i--)
   //    std::cout << test[test.length() - i];

   std::reverse_copy( test.begin(),
                      test.end(),
		      std::ostream_iterator<char>( std::cout ) );

   //   std::cout << test.reverse();
}
