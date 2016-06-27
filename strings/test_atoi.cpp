#include "atoi.h"
#include <iostream>

int main() {
  string s = "-2147483649";
  int n = myatoi(s.c_str());
  cout << n << endl;

  return 0;
}
