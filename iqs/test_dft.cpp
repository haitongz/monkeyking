#include <iostream>
#include <memory>

class B
{
   public:
      virtual void f( int i = 0 ) {
         std::cout << i << std::endl;
      }
};

class D : public B
{
   public:
      void f( int i = 10 ) {
         std::cout << i << std::endl;
      }
};

int main( int argc, char** argv )
{
   std::auto_ptr<B> b( new D );
   b->f();
   std::auto_ptr<D> d( new D );
   d->f();
}
