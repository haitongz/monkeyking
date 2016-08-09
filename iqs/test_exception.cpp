#include <iostream>
#include <exception>

struct my_exp1 : /*virtual*/ std::exception
{
};

struct my_exp2 : /*virtual*/ std::exception
{
};

struct my_exp : my_exp1, my_exp2
{
};

int main()
{
   try
   {
      throw my_exp1();
   }
   catch( std::exception const& e ) {
      std::cout << "Caught std::exception: " << e.what() << std::endl;
   }
   catch( ... ) {
      std::cout << "confused!" << std::endl;
   }
}
