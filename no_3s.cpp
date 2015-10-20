/*
Given a number n, write a function that returns count of numbers from 1 to n that don't contain digit 3
in their decimal representation.
 */
#include <iostream>

using namespace std;

uint32_t numsWO3Count(const uint32_t n) {
  if (n < 3)
    return {n};
  else if (n < 10)
    return n-1;

  function<uint32_t(const uint32_t)> solve = [&](const uint32_t num) {
    // Calculate 10^(d-1) (10 raise to the power d-1) where d is number of digits in n. po will be 100 for n = 578
    uint32_t po = 1;
    while (num/po > 9)
      po *= 10;

    // find the most significant digit (msd is 5 for 578)
    uint32_t msd = num/po;
    if (msd != 3)
      // For 578, total will be 4*count(10^2 - 1) + 4 + count(78)
      return solve(msd)*solve(po-1) + solve(msd) + solve(num%po);
    else
      // For 35, total will be equal to count(29)
      return solve(msd*po-1);
    }
  };

  return solve(n);
}
