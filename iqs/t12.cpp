#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  char* s = "123456";
  *s = s[5];
  cout << s << endl;

  *s = ++s;
  cout << s << endl;

  return 0;
}
