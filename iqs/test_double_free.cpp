#include <stdlib.h>
#include <string.h>

class Foo
{
   char * buf;
   public:
      Foo(const char * b = "default") {
         if (b) {
            buf = new char[strlen(b) + 1];
            strcpy(buf, b);
         }
         else
            buf = 0;
      }

      ~Foo() { delete buf; /*if (buf) delete[] buf;*/ }
};

Foo func(Foo f)
{
   return f;
}

int main()
{
   Foo f("lsajfadjflsdafjl;asdfj");
   func(f);
   return 0;
}
