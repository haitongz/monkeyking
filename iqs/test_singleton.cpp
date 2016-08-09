#include <iostream>

class X
{
   public:
      X* getInstance() { return &_x; }
      void setMember( int i ) { _i = i; }
      int getMember() const { return _i; }
      const int* getMemberAddr() const { return &_i; }

   private:
      X() {}
      ~X() {}
      X( const X& );
      X& operator=( const X& );

      static X _x;
      int _i;
};

X X::_x;

int main()
{
   X* p;
   std::cout << p->getInstance() << std::endl;

   p->getInstance()->setMember( 10 );

   std::cout << p->getInstance()->getMember() << std::endl;
   std::cout << p->getInstance()->getMemberAddr() << std::endl;

   X* q;
   std::cout << q->getInstance()->getMember() << std::endl;
   std::cout << q->getInstance()->getMemberAddr() << std::endl;
}
