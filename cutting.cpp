#include <iostream>
#include <vector>

using namespace std;

/*
Given a rope of length n meters, cut the rope in different parts of integer lengths in a way that maximizes product of lengths of all parts. You must make at least one cut. Assume that the length of rope is more than 2 meters.

Examples:
Input: 2, return 1 because 1x1 = 1
Input: 5, return 6 because 2x3 = 6
 */
uint32_t cutRope(const uint32_t n) {
  if (n <= 2)
    return 0;

  uint32_t dp[n+1]; // global results
  dp[0] = dp[1] = 1;

  for (uint32_t i = 2; i <= n; ++i) {
    dp[i] = 0;

    for (uint32_t j = 1; j < i; ++j) {
      const uint32_t tmp = max(j, dp[j])*(i-j);
      dp[i] = max(dp[i], tmp);
    }
  }

  return dp[n];
}

uint32_t cutRope2(uint32_t n) {
  if (n == 2 || n == 3)
    return n-1;

  uint32_t res = 1;

  while (n > 4) {
    n -= 3;
    res *= 3;
  }

  return n*res;
}

/*
Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. Determine the maximum value obtainable by cutting up the rod and selling the pieces. For example, if length of the rod is 8 and the values of different pieces are given as following, then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)

Example:
Pricing list: {1, 5, 8, 9, 10, 17, 17, 20}
Result = 22 (cut into two pieces of length 2 and 6)
 */
uint32_t cutRod(const vector<uint32_t>& px) {
  const uint32_t n = px.size();
  if (!n)
    return 0;

  uint32_t dp[n+1];
  dp[0] = 1;

  for (uint32_t i = 1; i < n+1; ++i) {
    dp[i] = px[i-1];

    for (uint32_t j = 1; j < i; ++j) {
      const uint32_t tmp = px[j-1] + dp[i-j]; // Note: dp[i-j] only has to do with length i-j, not sequence before i
      dp[i] = max(dp[i], tmp);
    }
  }

  return dp[n];
}

int main(int argc, char** argv) {
  cout << "Cutting rope: " << cutRope(5) << endl;
  cout << "Cutting rope 2: " << cutRope2(5) << endl;
  vector<uint32_t> px = {1, 5, 8, 9, 10, 17, 17, 20};
  cout << "Cutting rod: " << cutRod(px) << endl;
  return 0;
}
