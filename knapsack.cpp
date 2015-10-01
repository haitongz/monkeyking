/*
Given weights and values of n items, put these items in a knapsack of capacity W to
get the maximum total value in the knapsack. In other words, given two integer arrays
v[0...n-1] and wt[0...n-1] which represent values and weights associated with n items respectively.
Also given an integer W which represents knapsack capacity, find out the maximum value subset of
v[] such that sum of the weights of this subset is smaller than or equal to W.

You cannot break an item, either pick the complete item, or don't pick it (0-1 property).
 */
#include <iostream>

using namespace std;

/*
Time Complexity: O(nW) where n is the number of items and W is the capacity of knapsack.
 */
uint32_t knapSack(const uint32_t v[], const uint32_t wt[], const uint32_t n, const uint32_t W) {
  uint32_t dp[n+1][W+1];

  for (uint32_t i = 0; i < n+1; ++i) {
    for (uint32_t j = 0; j < W+1; ++j) {
      if (!i || !j)
        dp[i][j] = 0;
      else if (wt[i-1] <= j)
        dp[i][j] = max(v[i-1]+dp[i-1][j-wt[i-1]], dp[i-1][j]);
      else
        dp[i][j] = dp[i-1][j];
    }
  }

  return dp[n][W];
}

int main(int argc, char** argv) {
  uint32_t v[] = {60, 100, 120};
  uint32_t wt[] = {10, 20, 30};
  uint32_t W = 50;
  uint32_t n = sizeof(v)/sizeof(v[0]);

  cout << "Max value of subsets: " << knapSack(v, wt, n, W) << endl;
  return 0;
}
