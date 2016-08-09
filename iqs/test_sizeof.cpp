#include <iostream>
// #include <conio.h>
#include <stdio.h>

using namespace std;

#define sizeof_op1(val) ((char*)(&val+1)-(char*)(&val))

class A
{
   public:
      A(const int a) : a_(a) {}
      virtual ~A() {}

   private:
      int a_;
};

struct triplet
{
   int    i_;
   double d_;
   char   c_;
};

int main()
{
   //  char a[] = ”hello”;
   //  cout << getsize(a); //output is 6 because backslash 0 has to be considered.

   A a(100);
   cout << "sizeof A is " << sizeof(a) << endl;

   int x = sizeof_op1(a);
   cout << "my sizeof A is " << x << endl;

   cout << "size of double is " << sizeof(double) << endl;
   cout << "padding is " << sizeof(triplet) << endl;

   return 0;
}
