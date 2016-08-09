#include <iostream>
#include <typeinfo>
using namespace std;

/*
int main()
{
   int myArray[10];
   cout << typeid(myArray).name() << endl;
}

*/
template <typename T>
struct Some : public T
{
   // U typeOntheFly() { return typeid(T); }
   void print() { std::cout << "type is " << typeof(T).name() << std::endl; }
};

int main()
{
   void * lptr = new Some<unsigned long long>;
   //	typedef typename typeof(Some<unsigned long long>) T;
   reinterpret_cast<Some<unsigned long long> *>(lptr)->print();
   return 0;
}
