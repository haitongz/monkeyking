#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

static const uint32_t max_lmt = numeric_limits<uint32_t>::max();

/*
Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = {S1,S2,...,Sm} valued coins, how many ways can we make the change? The order of coins doesn't matter.

For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4. For N = 10 and S = {2,5,3,6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.
 */
uint32_t makeChange_recur(const uint32_t N, const vector<uint8_t>& S) {
  const uint32_t m = S.size();
  if (!N || !m)
    return 0;

  function<uint32_t(const uint32_t,const uint32_t)> dfs =
    [&](const uint32_t remaining, const uint32_t coin_num) -> uint32_t {
    if (!remaining) {
      return 1;
    }
    if (!coin_num) // && remaining >= 1)
      return 0;

    // count is sum of solutions (i) including S[m-1] (ii) excluding S[m-1]
    return dfs(remaining, coin_num-1) + dfs(remaining-S[coin_num-1], coin_num);
  };

  return dfs(N, m);
}

uint32_t makeChange_dp2(const uint32_t N, const vector<uint8_t>& S) {
  const uint32_t m = S.size();
  if (!N || !m)
    return 0;

  vector<uint32_t> dp(N+1, 0);
  dp[0] = 1;

  // Pick all coins one by one and update dp values after index >= the value of the picked coin
  for (uint32_t i = 0; i < m; ++i) {
    const uint8_t i_value = S[i];

    for (uint32_t j = i_value; j < N+1; ++j)
      dp[j] += dp[j-i_value];
  }

  return dp[N];
}

uint32_t makeChange_dp(const uint32_t N, const vector<uint8_t>& S) {
  const uint32_t m = S.size();
  if (!N || !m)
    return 0;

  // We need N+1 rows as the table is consturcted in bottom up manner using the
  // base case 0 value case (n = 0)
  uint32_t dp[N+1][m];
  for (uint32_t i = 0; i < m; ++i)
    dp[0][i] = 1;

  for (uint32_t i = 1; i < N+1; ++i) {
    for (uint32_t j = 0; j < m; ++j) {
      // Count of solutions excluding coin S[j]
      const uint32_t s1 = (j >= 1) ? dp[i][j-1] : 0;

      // Count of solutions including S[j]
      const int32_t left = i-S[j];
      const uint32_t s2 = (left >= 0) ? dp[diff][j] : 0;

      dp[i][j] = s1+s2;
    }
  }

  return dp[N][m-1];
}

/*
Given a set of denominations and an amount, how do we minimize the number of coins to make up the given amount?
 */
uint32_t minCoinsNum(const uint32_t N, const vector<uint8_t>& S) {
  const uint32_t m = S.size();
  if (!N || !m)
    return 0;

  uint32_t dp[N+1];
  dp[0] = 0;

  for (uint32_t i = 1; i < N+1; ++i) {
    uint32_t v = max_lmt;

    for (uint32_t j = 0; j < m; ++j) {
      const int32_t left = i-S[j];
      if (left >= 0) { // coin value should not exceed the amount itself
        v = min(v, dp[left]);
      }
    }

    if (v < max_lmt)
      dp[i] = v+1;
    else
      dp[i] = max_lmt;
  }

  return dp[N];
}

/*
Given a list of numbers, you and another player pick a number in turn. Both of players can only pick left most or right most number and you get to pick first, how should you max your sum?

Example:
{5, 3, 7, 10} return 15
{8, 15, 3, 7} return 22
 */
uint32_t coinsInALine(const vector<uint32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  uint32_t dp[n][n];

  for (uint32_t k = 0; k < n; ++k) {
    for (uint32_t i = 0, j = k; j < n; ++i, ++j) {
      if (i == j) {
        dp[i][j] = nums[i];
      } else if (i+1 == j) {
        dp[i][j] = max(nums[i], nums[j]);
      } else {
        dp[i][j] = max(nums[i]+min(dp[i+1][j-1], dp[j+2][j]),
                       nums[j]+min(dp[i][j-2], dp[i+1][j-1]));
      }
    }
  }

  return dp[0][n-1];
}

int main(int argc, char** argv) {
  vector<uint8_t> S = {2, 3, 5, 6};
  const uint32_t N = 25;

  //cout << "There are " << makeChange_recur(N, S) << " ways to represent " << N << " cents!" << endl;
  cout << "There are " << makeChange_dp(N, S) << " ways for changes!" << endl;

  S = {1, 5, 10, 25};
  cout << "There are " << makeChange_dp(N, S) << " ways to represent " << N << " cents!" << endl;

  vector<uint32_t> nums = {5, 3, 7, 10};
  cout << "Max sum: " << coinsInALine(nums) << endl;
  nums = {8, 15, 3, 7};
  cout << "Max sum: " << coinsInALine(nums) << endl;

  return 0;
}
