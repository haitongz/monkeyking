#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
   std::vector<std::string> store;

   store.push_back("Bar");
   store.push_back("Baz");
   store.push_back("Foo");
   store.push_back("Bee");

   std::cout << std::count_if(store.begin(), store.end(),
      std::bind2nd(std::greater<std::string>(), "Baz"))
      << std::endl;
}
