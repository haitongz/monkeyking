#include <iostream>

using namespace std;

class A {
        public:
                int data;
                virtual void fun(){}
                virtual void fun1() {}
                virtual void fun2() {}
};

int main(){

        A a;
        cout << sizeof(a) << endl;

return 0;
}
