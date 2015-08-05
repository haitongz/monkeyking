/*
Reverse digits of an integer.
Example1: x = 123, return 321
Example2: x = -123, return -321
*/
#include <iostream>
#include <limits>

using namespace std;

int32_t reverseInteger(int32_t x) {
  int32_t res = 0;
  while (x) {
    res = res*10 + x%10;
    x /= 10;
  }
  if (res > numeric_limits<int32_t>::max())
    return numeric_limits<int32_t>::max();
  if (res < numeric_limits<int32_t>::min())
    return numeric_limits<int32_t>::min();
  return res;
}

int main(int argc, char** argv) {
  int32_t x = 123;
  cout << "Reversed integer of " << x << " is " << reverseInteger(x) << endl;
  x = -321;
  cout << "Reversed integer of " << x << " is " << reverseInteger(x) << endl;
}
