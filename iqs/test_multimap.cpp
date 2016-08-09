#include <iostream>
#include <map>

int main ()
{
   std::multimap<char,int> mymultimap;
   std::multimap<char,int>::iterator it, itlow, itup;

   mymultimap.insert(std::make_pair('a', 10));
   mymultimap.insert(std::make_pair('b', 121));
   mymultimap.insert(std::make_pair('c', 3003));
   mymultimap.insert(std::make_pair('c', 1001));
   mymultimap.insert(std::make_pair('c', 2002));
   mymultimap.insert(std::make_pair('d', 11011));
   mymultimap.insert(std::make_pair('e', 77));

   itlow = mymultimap.lower_bound('c');           // itlow points to b
   itup  = mymultimap.upper_bound('d');           // itup points to e (not d)

   std::cout << itlow->first << " => " << itlow->second << std::endl;
   /*
      // print range [itlow,itup):
      for (it = itlow; it != itup; ++it)
         std::cout << (*it).first << " => " << (*it).second << std::endl;
   */
   return 0;
}
