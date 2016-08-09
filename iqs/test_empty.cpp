#include <iostream>
#include <string>
#include <list>
#include <iterator>

#define X(y, z) ((int) &(((y *) 0)->z))

using namespace std;

template <typename T>
void printTemplate(const T & coll)
{
   copy(coll.begin(), coll.end(),                 // source
                                                  // destination
      ostream_iterator<typename T::value_type>(cout, " + "));
   cout << endl;
}

int main()
{
   #if 0
   typedef size_t vT;
   typedef list<vT> collT;
   collT coll;
   // insert elements from 6 to 1 and 1 to 6
   for (size_t i = 1; i <= 6; ++i) {
      coll.push_front(i);
      coll.push_back(i);
   }

   printTemplate<collT>(coll);
   #endif
   int y = 1;
   int z = 10;
   std::cout << (X(y, z)) << std::endl;
}
