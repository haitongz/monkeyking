#include <iostream>

using namespace std;

class A {
 public:
  A() {
    tab = new char[20];
  }
  ~A() {
    delete tab;
  }

 private:
  char* tab;
};

int main(int argc, char** argv) {
  try {
    A a1;
    A a2 = a1;
    printf("%x\n%x\n", &a1, &a2);
  } catch(...) {
    cout << "exception" << endl;
  }

  return 0;
}
