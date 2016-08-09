#include <vector>
#include <iostream>

struct P {
   P() {
      std::cout << "default constructor gets called!" << std::endl;
   }
   P(const P & lhs) {
      std::cout << "copy constructor gets called!" << std::endl;
   }
   const P& operator=(const P& lhs) {
      return lhs;
   }
   virtual ~P() {
      std::cout << "destructor gets called!" << std::endl;
   }
};

int main()
{
  P const* lP = new P();
  std::vector<P> v(0);
  v.push_back(*lP);
  std::cout << "push_back finished, and u think it's the last function call? think again..." << std::endl;

  return 0;
}
