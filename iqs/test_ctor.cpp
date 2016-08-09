#include <iostream>

/*
class I
{
   public:
      I() { std::cout << "default ctor of I" << std::endl; }
      virtual void f() = 0;
      virtual ~I() {}
};

class A : public I
{
public:
A() {}
A( const A& a ) {}
A& operator =( const A& a ) { return *this; }
void f() { std::cout << "implementing f()..." << std::endl; }
};*/

class BaseClass
{
   public:
      BaseClass() : _i( 0 ) {
         std::cout << "dft ctor..." << std::endl;
      }

      BaseClass( int i )
      : _i( i ) {
         std::cout << "integer ctor..." << _i << std::endl;
      }

      BaseClass( const BaseClass& rhs )
      : _i( rhs._i ) {
         std::cout << "copy ctor..." << _i << std::endl;
      }

      const BaseClass& operator=( const BaseClass& rhs ) {
         this->_i = rhs._i;
         std::cout << "assign operator..." << _i << std::endl;
         return *this;
      }

      // wont compile
      /*
      BaseClass( MyClass rhs )
      {
         this->_i = rhs._i;
         std::cout << "copy ctor..." << std::endl;
      }*/

      int increment() { return ++_i; }
      int getValue() const { return _i; }

      virtual void f() {
         std::cout << "BaseClass::f()..." << std::endl;
      }

      virtual ~BaseClass() {}

   private:
      int _i;
};

class Derived : public BaseClass
{
   public:
                                                  // won't work as BaseClass will always be initialized before _j, so we are using a garbage _j for MyClass...
      Derived( int i ) : _j( i ), BaseClass( _j ) {
      }

      // wont compile
      /*
      void manipulate()
      {
         std::cout << "new value=" << ++_i << std::endl;
      }*/

   private:
      virtual void f() {
         std::cout << "Derived::f()..." << std::endl;
      }

      int _j;
};

//some code block
int main()
{
   BaseClass* p = new BaseClass( BaseClass( BaseClass( BaseClass( BaseClass( 1 ) ) ) ) );
   std::cout << "value=" << p->getValue() << std::endl;

   // BaseClass a; //, b, c;

   // wont compile
   /*
   if( (a = *p).increment())
      ;*/

   Derived d( 10 );
   std::cout << "value=" << d.getValue() << std::endl;
   *p = d;
   std::cout << "value=" << p->getValue() << std::endl;

   std::cout << "testing virtual function access..." << std::endl;
   p->f();                                        // OK, calls BaseClass::f()

   BaseClass* q = &d;
   q->f();                                        // OK because BaseClass::f() is public, and vptr goes to Derived::f()

   // wont compile
   /*
   Derived* t = &d;
   t->f(); Derived::f() is private */

   delete p;

   return 0;
   /*
      const A a1;
      A a2( a1 );
      return 0;*/
}
