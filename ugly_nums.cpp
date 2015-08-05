/*
Ugly numbers are numbers whose only prime factors are 2, 3 or 5. The sequence
1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15...shows the first 11 ugly numbers. By convention, 1 is included.
Write a program to find and print the 150th ugly number.

Algorithm:

Because every number can only be divided by 2, 3, 5, one way to look at the sequence is to split the sequence to three groups as below:
     (1) 1×2, 2×2, 3×2, 4×2, 5×2, ...
     (2) 1×3, 2×3, 3×3, 4×3, 5×3, ...
     (3) 1×5, 2×5, 3×5, 4×5, 5×5, ...

We can find that every subsequence is the ugly-sequence itself (1, 2, 3, 4, 5, ...) multiply 2, 3, 5. Then we use similar merge method as merge sort, to get every ugly number from the three subsequence. Every step we choose the smallest one, and move one step after.
Loop for all positive integers until ugly number count is smaller than n, if an integer is ugly than increment ugly number count.
 */
#include <iostream>

using namespace std;

uint32_t nthUglyNumber(const uint32_t n) {
  if (n < 1)
    return n;

  uint32_t n2 = 2, n3 = 3, n5 = 5;
  uint32_t i2 = 0, i3 = 0, i5 = 0;
  uint32_t ugly_nums[n];

  for (uint32_t i = 1; i < n; ++i) {
    uint32_t t = min(n2, min(n3, n5));
    if (t == n2) {
      ugly_nums[i] = n2;
      n2 = ugly_nums[++i2]*2;
    }
    if (t == n3) { // don't "else" to avoid duplicates
      ugly_nums[i] = n3;
      n3 = ugly_nums[++i3]*3;
    }
    if (t == n5) { // don't "else" to avoid duplicates
      ugly_nums[i] = n5;
      n5 = ugly_nums[++i5]*5;
    }
  }

  return ugly_nums[n-1];
}

int main(int argc, char** argv) {
  const uint32_t n = 150;
  uint32_t res = nthUglyNumber(n);
  cout << n << "th ugly number is " << res << endl;
  return 0;
}
