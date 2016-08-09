#include <iostream>
#include <string.h>

class String
{
   char * s;
   int  length;

   public:
      String(const char * str) :
      s(const_cast<char *>(str)), length(strlen(str)) {}
      String();

      /* add code here */
      operator const char*() const { return s; }
      operator char* const() const { return s; }
      //   char* operator() { return s; }
      //   char* const operator() { return s; }
      //   char* const operator() const { return s; }
};

template <class T, class X>
class Object
{
   T my_t;
   X my_x;

   public:
      Object(T t, X x) : my_t(t), my_x(x) {}

      /* add code here */
      // operator(T) { return my_t; }
      // T operator T (const Obj &obj) { return obj.my_t; }
      operator T () const { return my_t; }
      // T operator T () { return my_t; }
      // T operator(T) const { return my_t; }
};

int main()
{
   String s1 = "abc";
   String s2 = "def";
   std::cout << strcmp(s1, s2) << std::endl;

   int i;
   Object<int, float> O(10, 13.567);
   i = O;
   std::cout << i << std::endl;

   int x=5, y=-10, a=2, b=4;
   std::cout << (x++ - --y*a/b) << std::endl;
   return 0;
}
