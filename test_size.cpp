#include <iostream>

class A {
public:
  A(uint64_t i)
    : m_i(i),
      m_str(new char[m_i]) {
  }

  uint64_t m_i;
  char* m_str;
};

class B : public A
{
public:
  B( uint64_t i )
    : A(i),
      m_j(2*i) {
  }
  uint64_t m_j;
};

class C : public A
{
public:
  C(uint64_t i )
    : A(i),
      a(m_i) {
  }
  uint64_t& a;
};

int main()
{
  A a(100);
  B b(100);
  C c(100);

  std::cout << "Size of A is: " << sizeof(A) << std::endl;
  std::cout << "Size of a is: " << sizeof(a) << std::endl;
  std::cout << "Size of B is: " << sizeof(B) << std::endl;
  std::cout << "Size of b is: " << sizeof(b) << std::endl;
  std::cout << "Size of C is: " << sizeof(C) << std::endl;
  std::cout << "Size of c is: " << sizeof(c) << std::endl;

  return 0;
}
