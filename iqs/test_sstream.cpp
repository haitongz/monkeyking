#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
   std::ostringstream strout;
   int x = 42;
   strout << "The answer to the question is " << 42 << std::endl;
   cout << strout.str() << endl;
   strout.str("");
   strout << 53.2;
   cout << strout.str() << endl;
   return 0;
}
