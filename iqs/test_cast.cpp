class Foo
{
   public:
      virtual ~Foo() {}
};

class Bar : public Foo
{
};

class Bar2 : public Foo
{
};

class FooBar : public Bar
{
};

class FooBar2 : public Bar2
{
};

int main()
{
   // Foo & foo = static_cast<Foo &>(FooBar2 f);
   //Foo & foo2 = new FooBar;
   //FooBar2 & fb2 = dynamic_cast<Foo &>(new FooBar2);
   Foo & foo = dynamic_cast<Foo &>(*(new FooBar2));
   // FooBar2 * fb3 = new Foo;
   return 0;
}
