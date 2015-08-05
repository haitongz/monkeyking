/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 */
#include <iostream>

using namespace std;

uint32_t climbStairs_iter(const uint32_t n) {
  if (!n)
    throw exception();

  uint8_t f1 = 1, f2 = 2;

  if (n == 1)
    return f1;
  if (n == 2)
    return f2;

  for (uint32_t i = 3; i <= n; ++i) {
    uint8_t f3 = f1+f2;
    f1 = f2;
    f2 = f3;
  }

  return f2;
}

uint32_t climbStairs_recur(const uint32_t n) {
  function<uint32_t(const uint32_t)> solve =
    [](const uint32_t num) {
    if (num <= 0)
      return 0;
    if (num == 1)
      return 1;
    if (num == 2)
      return 2;

    return solve(num-1)+solve(num-2);
  };

  return solve(n);
}
