#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"

struct A {};
struct B {};

template<typename X>
struct S
{
   template<typename T, typename Enable = void>
      struct foo
   {
      enum { value = 0 };
   };

   template<typename T>
      struct foo<T, typename boost::enable_if<boost::is_same<X,A> >::type>
   {
      enum { value = 1 };
   };
};

int
main()
{
   int i = S<A>::foo<B>::value;
   int j = S<B>::foo<B>::value;                   // OK for g++ 4.2.0, NOK for Intel C++ 10.0.23
}
