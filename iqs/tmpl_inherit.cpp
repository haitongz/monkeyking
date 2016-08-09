#include <iostream>

class Base
{
   public:
      void init() { std::cout << "Base::init() get called..." << std::endl; }
};

template< typename DDerived >
class Derived : public Base
{
   public:
      template< typename Insert1, typename Insert2 >
      void init() {
         std::cout << "Derived::init() plus something: " << Insert1::out() << " and something: " << Insert2::out() << std::endl;
      }

      virtual void start() {
         return static_cast<DDerived *>(this)->start();
      }
};

class Insert1
{
   public:
      static std::string out() {
         return std::string("this is Insert1...");
      }
};

class Insert2
{
   public:
      static std::string out() {
         return std::string("this is Insert2...");
      }
};

class Insert3
{
   public:
      static std::string out() {
         return std::string("this is Insert3...");
      }
};

class DDerived : public Derived<DDerived>
{
   public:
      virtual void start() {
         std::cout << "Derived class starting..." << std::endl;
      }
};

int main()
{
   DDerived lD;
   lD.init<Insert1, Insert2>();
   lD.Base::init();
   lD.init<Insert2, Insert3>();
   lD.start();
   return 0;
}
