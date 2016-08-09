#include <iostream>
#include <cstring>
#include <string>
#include <stddef.h>

//#include "object.hpp"

template <typename T>
inline T max(T const& a, T const& b)
{
   return a < b ? b : a;
}

inline const char* max(char const* a, const char* b)
{
   return (std::strcmp(a, b) < 0) ? b : a;
}

template <typename T>
inline T max(T const& a, T const& b, T const& c)
{
   return max(max(a, b), c);
}

// Using CRTP
// keep track of how many objects of a certain class type were created.
template <typename DerivedToCount>
class ObjectCounter
{
   private:
      static size_t count;                        // number of existing objects

   protected:
      // default constructor
      ObjectCounter() { ++ObjectCounter<DerivedToCount>::count; }

      // copy constructor
      ObjectCounter(ObjectCounter<DerivedToCount> const&) { ++ObjectCounter<DerivedToCount>::count; }

      // destructor
      ~ObjectCounter() { --ObjectCounter<DerivedToCount>::count; }

   public:
      void handle() { std::cout << "base class: handling..." << std::endl;}

   public:
      // return number of existing objects:
      static size_t live() { return ObjectCounter<DerivedToCount>::count; }

      // non-static virtual-like
      void interface() {
         static_cast<DerivedToCount *>(this)->impl();
      }

      // static virtual-like
      static void static_func() {
         DerivedToCount::static_sub();
      }
};

// Using PBCP
// -------------
template <typename T>
struct Derived : ObjectCounter<T>
{
   void handle() {
      // Since the handler derives from the supplied type, it can call the correct implementation directly.
      ObjectCounter<T>::handle();
   };

};

// initialize counter with zero
template <typename DerivedToCount>
size_t ObjectCounter<DerivedToCount>::count = 0;

template <typename charT>
class MyString : public ObjectCounter<MyString<charT> >
{
   public:
      void impl() { std::cout << "derived class: impl()" << std::endl; }
      static void static_sub() { std::cout << "derived class: static_sub()" << std::endl; }
};

/*#include <memory>
class AutoMemory
{
private:
   std::auto_ptr<Object> object_pointer;
public:
   AutoMemory(unsigned int number) : object_pointer(number != 0 ? new Object() : NULL) { }
        ~AutoMemory() { }
}

class Base
{
public:
Base() { std::cout << "base class ctor!" << std::endl; }
virtual ~Base() { std::cout << "base class dtor!" << std::endl; }
virtual void doSth() { std::cout << "base function gets called!" << std::endl; }
};

class Derived2 : public Base
{
public:
Derived2() { std::cout << "derived class ctor!" << std::endl; }
~Derived2() { std::cout << "derived class dtor!" << std::endl; }
virtual void doSth() { std::cout << "overwritten function gets called!" <<  std::endl; }
};

static void framework()
{
Base * lObj = new Derived2();
lObj->doSth();
delete lObj;
}
*/

int main() {
   /*
      std::cout << "biggest number is: " << ::max(7, 42, 68) << std::endl;
   const char* s1 = "frederic";
   const char* s2 = "anica";
   const char* s3 = "lucas";
   std::cout << "biggest string is: " << ::max(s1, s2, s3) << std::endl;*/

   MyString<char> lStr1;
   // ObjectCounter<int> * lDrvd = new Derived<int>();
   // Derived<int> lDrvd;
   // lDrvd.handle();
   ObjectCounter<MyString<char> > * lStr2 = new MyString<char>();
   MyString<wchar_t> ws;
   std::cout << "number of MyString with char: " << MyString<char>::live() << std::endl;
   std::cout << "number of MyString with wchar_t: " << ws.live() << std::endl;
   lStr2->interface();
   ObjectCounter<MyString<char> >::static_func();

   //	framework();
}
