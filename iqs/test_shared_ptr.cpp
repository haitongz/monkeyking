#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace boost;
// using namespace std;

class Y: public enable_shared_from_this<Y>
{
   public:
      shared_ptr<Y> f() {
         return shared_from_this();
      }
};

struct null_deleter
{
   void operator()(const void *) { }
};

int main()
{
   shared_ptr<Y> p(new Y);
   shared_ptr<Y> q = p->f();
   assert(p == q);
   assert(!(p < q || q < p));
   std::cout << "use_count() is " << p.use_count() << ": they must share ownership." << std::endl;

   int k = 128;
   std::vector<boost::shared_ptr<int> > v(k);
   for(unsigned int i = 0; i < k; ++i) {
      v[i].reset(&k, null_deleter());             // null_deleter to get around when reset() is not receiving a new()
      // v[i].reset(new int(0));
   }

   int t = rand() % k;
   std::cout << "v[" << t << "].use_count() is " << v[t].use_count() << ", it points to value " << *v[t] << std::endl;
   return 0;
}
