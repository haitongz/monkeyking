#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

double pow(double x, int32_t n) {
  if (!n || x == 1)
    return 1.0;
  if (!x)
    return 0.0;
  if (n < 0)
    x = 1/x;

  n = abs(n);
  if (n == 1)
    return x;

  function<double(const int32_t)> solve =
    [&](const int32_t m) {
    double sub_res = solve(m/2);
    return sub_res*sub_res*((m%2) ? x : 1);
  };

  return solve(n);
}

/*
Consider the binary representation of n. For example, if it is "10001011", then x^n = x^(1+2+8+128) = x^1 * x^2 * x^8 * x^128. Thus, we don't want to loop n times to calculate x^n. To speed up, we loop through each bit, if the i-th bit is 1, then we add x^(1 << i) to the result. Since (1 << i) is a power of 2, x^(1<<(i+1)) = square(x^(1<<i)). The loop executes for a maximum of log(n) times.
 */
double pow_iter(double x, const int32_t n) {
  uint32_t m = abs((double)n); // int might overflow
  double res = 1.0;

  for (; m; x *= x, m >>= 1) {
    if (m & 1) { // is last bit set? if yes plus x. x will be square while shifting
      res *= x;
    }
  }

  return (n < 0) ? 1.0/res : res;
}

int main(int argc, char** argv) {
}
