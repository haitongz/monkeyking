#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <unordered_set>

int main()
{
   // Given a variable str of type std::string,
   // which one of the following statements outputs the string backwards?
   //   std::string test = "peng xu is so handsome...";

   //   std::copy(test.reverse(), std::unary_function(std::cout));
   //   std::reverse(test); std::cout << test;

   //   for (unsigned int i = test.size(); i > 0; i--)
   //    std::cout << test[test.length() - i];

   std::unordered_set<std::string> test;
   std::ifstream ifs("filter.txt");
   std::string str;

   while (getline(ifs, str)) {
      std::replace(str.begin(), str.end(), ',', ' ');
      if (!str.empty()) {
         std::istringstream iss(str);
         std::istream_iterator<std::string> iter(iss);
         test.insert(*iter);
      }
   }

   std::cout << "total items: " << test.size() << std::cout;
   std::copy(test.begin(),
      test.end(),
      std::ostream_iterator<std::string>(std::cout, "\n"));

   //   std::cout << test.reverse();
}
