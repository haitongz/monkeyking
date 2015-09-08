/*
A number can always be represented as a sum of squares of other numbers. Note that 1 is a square and we can always
break a number as (1*1+1*1+1*1+...). Given a number n, find the minimum number of squares that sum to X.

Examples:

Input:  n = 100
Output: 1

100 can be written as 102. Note that 100 can also be written as 52+52+52+52,
but this representation requires 4 squares.
 */
#include <iostream>
#include <functional>

using namespace std;

uint32_t minSquares(const uint32_t n) {
  function<uint32_t(const uint32_t)> solve =
    [&](const uint32_t m) {
    if (m <= 3)
      return m;

    uint32_t ret = m; // maximum squares required is n (1*1 + 1*1 + ..)

    // go through all smaller numbers to recursively find minimum
    for (uint32_t i = 1; i < m+1; ++i) {
      uint32_t tmp = i*i;
      if (tmp > m)
        break;
      else
        ret = min(ret, 1+solve(m-tmp));
    }
    return ret;
  };

  return solve(n);
}

int main(int argc, char** argv) {
  cout << minSquares(6) << endl;

  return 0;
}
