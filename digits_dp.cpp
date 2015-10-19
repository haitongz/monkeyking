#include <iostream>
#include <functional>

using namespace std;

/*
Given two integers 'n' and 'sum', find count of all n digit numbers with sum of digits as 'sum'.
Leading 0's are not counted as digits.
1 <= n <= 100 and 1 <= sum <= 50000

Example:

Input:  n = 2, sum = 2
Output: 2
Explanation: Numbers are 11 and 20

Input:  n = 2, sum = 5
Output: 5
Explanation: Numbers are 14, 23, 32, 41 and 50
 */
// A lookup table used for memoization
int32_t lookup[101][50001];

// A memoization based recursive program to count numbers with sum of n as given 'sum'
uint32_t digitSumCnt(const uint32_t n, const uint32_t sum) {
  if (n < 1 || n > 100 || sum < 1 || sum > 50000)
    return 0;

  for (auto& i : lookup)
    for (auto& j : i)
      j = -1;

  function<uint32_t(const uint32_t,const int32_t)> solve =
    [&](const uint32_t digits, const int32_t curr_sum) -> uint32_t {
    if (!digits)
      return (uint32_t)curr_sum == 0;

    // If this subproblem is already evaluated, return the evaluated value
    if (lookup[digits][curr_sum] != -1)
      return (uint32_t)lookup[digits][curr_sum];

    uint32_t ret = 0;
    for (uint8_t i = 0; i < 10; ++i)
      if (curr_sum-i >= 0)
        ret += solve(digits-1, curr_sum-i);

    lookup[digits][curr_sum] = ret;
    return ret;
  };

  uint32_t ret = 0;
  // Traverse through every digit from 1 to 9 and count numbers beginning with it
  for (uint8_t i = 1; i < 10; ++i)
    if (sum-i >= 0)
      ret += solve(n-1, sum-i);

  return ret;
}

/*
Given a number n, we need to count total number of n digit numbers such that the sum of even digits
is 1 more than the sum of odd digits. Here even and odd means positions of digits are like array indices,
for example, the leftmost (or leading) digit is considered as even digit,
next to leftmost is considered as odd and so on.

Input:  n = 2
Output: Required count of 2 digit numbers is 9
Explanation : 10, 21, 32, 43, 54, 65, 76, 87, 98.

Input:  n = 3
Output: Required count of 3 digit numbers is 54
Explanation: 100, 111, 122, ......, 980
 */
// A lookup table used for memoization.
int32_t lookup2[50][1000][1000][2];

uint32_t digitSumCnt2(const uint32_t n) {
  for (auto& i : lookup2)
    for (auto& j : i)
      for (auto& l : j)
        for (auto& m : l)
          m = -1;

  // Memnoization based recursive function to count numbers with even and odd digit sum difference as 1.
  // This function conisders leading zero as a digit
  function<uint32_t(const uint32_t,const uint32_t,const uint32_t,bool)> solve =
    [&](const uint32_t digits, const uint32_t esum, const uint32_t osum, bool isOdd) -> uint32_t {
    if (digits == n)
      return (uint32_t)esum-osum == 1;

    // If current subproblem is already computed
    if (lookup2[digits][esum][osum][isOdd] != -1)
      return (uint32_t)lookup2[digits][esum][osum][isOdd];

    uint32_t ret = 0;
    if (isOdd) // If current digit is odd, then add it to odd sum and recur
      for (uint8_t i = 0; i < 10; ++i)
        ret += solve(digits+1, esum, osum+i, false);
    else // Add to even sum and recur
      for (uint8_t i = 0; i < 10; ++i)
        ret += solve(digits+1, esum+i, osum, true);

    // Store current result in lookup table and return the same
    lookup2[digits][esum][osum][isOdd] = ret;
    return ret;
  };

  uint32_t ret = 0;
  // Initialize number digits considered so far
  uint32_t digits = 0;
  // Initialize even and odd sums
  uint32_t esum = 0, osum = 0;

  // Explicitly handle first digit and call recursive function for remaining digits.
  // Note that the first digit is considered as even digit.
  for (uint8_t i = 1; i < 10; ++i)
    ret += solve(digits+1, esum+i, osum, true);

  return ret;
}

/*
A number is non-decreasing if every digit (except the first one) is greater than or equal to previous digit.
For example, 223, 4455567, 899, are non-decreasing numbers.

So, given the number of digits n, you are required to find the count of total non-decreasing numbers with n digits.
 */
uint32_t nonDecreasingCnt(const uint32_t n) {
  // dp[i][j] contains total count of non decreasing numbers ending with digit i and of length j
  int32_t dp[10][n+1];
  for (auto& i : dp)
    for (auto& j : i)
      j = 0;

  // Fill table for non decreasing numbers of length 1
  // base cases 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  for (uint8_t i = 0; i < 10; ++i)
    dp[i][1] = 1;

  // Fill the table in bottom-up manner
  for (uint8_t i = 0; i < 10; ++i) {
    // Compute total numbers of non decreasing numbers of length 'len'
    for (uint32_t len = 2; len < n+1; ++len) {
      // sum of all numbers of length of len-1 in which last digit x is <= 'digit'
      for (uint32_t j = 0; j < i+1; ++j)
        dp[i][len] += dp[j][len-1];
    }
  }

  uint32_t ret = 0;
  // There total nondecreasing numbers of length n is dp[0][n]+dp[1][n]+...+dp[9][n]
  for (uint8_t i = 0; i < 10; ++i)
    ret += dp[i][n];

  return ret;
}

int main(int argc, char** argv) {
  uint32_t n = 3;
  uint32_t sum = 5;
  cout << digitSumCnt(n, sum) << endl;
  cout << digitSumCnt2(n) << endl;
  cout << nonDecreasingCnt(n) << endl;

  return 0;
}
