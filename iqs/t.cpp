#include <iostream>

template <typename T>
class Foo{
        T tVar;
        public:
                Foo(T t) : tVar(t) { }
};

class FooDerived : public Foo<std::string> {};

int main(){
        FooDerived d;
    return 0;
}
