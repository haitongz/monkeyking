#include <iostream>
#include <boost/type_traits/is_same.hpp>

#define GETTER( a ) Intruder::get( *this, a )
#define SETTER( a, i ) Intruder::set( *this, a, i )

class A
{
   private:
      friend struct Intruder;
      int _i;
      double _d;
};

struct Intruder
{
   template<typename T>
      static int get( const T& ref, const A& a );

   template<typename T>
      static void set( const T& ref, A& a, int i );
};

template<typename T>
int Intruder::get( const T& ref, const A& a )
{
   if( boost::is_same<T, B>::value ) {
      std::cout << "Getting " << a._i << std::endl;
      return a._i;
   }
   else
      std::cerr << "Wrong type!" << std::endl;
}

template<typename T>
void Intruder::set( const T& ref, A& a, int i )
{
   if( boost::is_same<T, B>::value ) {
      std::cout << "Setting to " << i << std::endl;
      a._i = i;
      return;
   }
   else
      std::cerr << "Wrong type!" << std::endl;
}

class B
{
   public:
      void do_it( A& a );
};

void B::do_it( A& a )
{
   SETTER( a, 250 );
   GETTER( a );
}

class C
{
   public:
      void do_it( A& a );
};

void C::do_it( A& a )
{
   SETTER( a, 250 );
   GETTER( a );
}

int main()
{
   A a;
   B b;
   b.do_it( a );
   C c;
   c.do_it( a );
}
