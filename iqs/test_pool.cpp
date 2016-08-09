#include <boost/pool/singleton_pool.hpp>
#include <boost/shared_ptr.hpp>

#include "S_TimeIntv.H"
#include <vector>

template <typename T>
class MemoryPooled : public T
{
   public:
      MemoryPooled() { }
      ~MemoryPooled() { }

      static const int32_t countObjectsInitiallyAllocated = 1000;
      typedef boost::singleton_pool<T, countObjectsInitiallyAllocated> Pool;

      void * operator new(size_t aMemSize) {
         return Pool::malloc();
      }

      void operator delete(void * p_memBlock) {
         Pool::free(p_memBlock);
      }
};

struct Test2
{
   private:
      std::vector<u_int32_t> m_Vector;
   public:
      Test2() : m_Vector(8)
         {}
};

template <bool isPooled>
void test()
{
   u_int64_t loops = 1000000;
   register u_int64_t i = 0;

   if (true == isPooled) {
      cout << "testing memory pool..." << endl;
      S_TimeIntv watcher(loops);
      {
         for (i = 0; i < loops; ++i) {
            boost::shared_ptr<Test2> item(new MemoryPooled<Test2>());
         }
      }
   }
   else {
      cout << "testing standard malloc..." << endl;
      S_TimeIntv watcher(loops);
      {
         for(i = 0; i < loops; ++i) {
            boost::shared_ptr<Test2> item(new Test2());
         }
      }
   }
}

int main()
{
   test<true>();
   test<false>();
}
