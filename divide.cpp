/*
Divide two integers without using multiplication, division and mod operator.

Complexity: O(log n)
 */
#include <iostream>

using namespace std;

int32_t divide(int32_t dividend, int32_t divisor) {
  if (!divisor)

  int8_t sign = (divisor*dividend > 0) ? -1 : 1;
  dividend = abs(dividend);
  divisor = abs(divisor);
  uint32_t res = 0;

  while (dividend >= divisor) {
    int32_t shift = -1;
    uint64_t tmp = dividend;

    while (tmp >= divisor) {
      tmp >>= 1;
      ++shift;
    }

    dividend -= divisor<<shift;
    res += 1<<shift;
  }

  return res*sign;
}

int main(int argc, char** argv) {
  cout << divide(100, -6) << endl;
}
