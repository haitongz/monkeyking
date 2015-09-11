#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();

/*
Given a value N, if we want to make change for N cents,
and we have infinite supply of each of S = {S1,S2,...,Sm} valued coins,
how many ways can we make the change? The order of coins doesn't matter.

For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}.
So output should be 4. For N = 10 and S = {2,5,3,6}, there are five solutions:
{2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.
 */
uint32_t makeChange_recur(const uint8_t coins[], const uint32_t n, const uint32_t V) {
  if (!n || !V)
    return 0;

  function<uint32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t remain, const uint32_t coin_num) -> uint32_t {
    if (!remain) {
      return 1;
    }
    if (!coin_num) // && remaining >= 1)
      return 0;

    // count is sum of solutions (i) including S[m-1] (ii) excluding S[m-1]
    return solve(remain, coin_num-1) +
           solve(remain-coins[coin_num-1], coin_num);
  };

  return solve(V, n);
}

uint32_t makeChange_dp2(const uint8_t coins[], const uint32_t n, const uint32_t V) {
  if (!V || !n)
    return 0;

  uint32_t dp[V+1];
  for (auto& i : dp)
    i = 0;
  dp[0] = 1;

  // Pick all coins one by one and update dp values after index >= the value of the picked coin
  for (uint32_t i = 0; i < V; ++i) {
    const uint8_t i_value = coins[i];
    for (uint32_t j = i_value; j < n+1; ++j)
      dp[j] += dp[j-i_value];
  }

  return dp[n];
}

uint32_t makeChange_dp(const uint8_t coins[], const uint32_t n, const uint32_t V) {
  if (!V || !n)
    return 0;

  // We need V+1 rows as the table is consturcted in bottom up manner using the
  // base case 0 value case (V = 0)
  uint32_t dp[V+1][n];
  for (uint32_t i = 0; i < n; ++i)
    dp[0][i] = 1;

  for (uint32_t i = 1; i < V+1; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      // Count of solutions excluding coin S[j]
      const uint32_t s1 = (j >= 1) ? dp[i][j-1] : 0;
      // Count of solutions including S[j]
      const int32_t left = i-coins[j];
      const uint32_t s2 = (left >= 0) ? dp[left][j] : 0;
      dp[i][j] = s1+s2;
    }
  }

  return dp[V][n-1];
}

/*
Given a value V, if we want to make change for V cents, and we have infinite
supply of each of S = {S1,S2,...,Sm} valued coins, what is the minimum number
of coins to make the change?

Input: coins[] = {25, 10, 5}, V = 30
Output: Minimum 2 coins required
We can use one coin of 25 cents and one of 5 cents
 */
uint32_t minCoinNum(const uint8_t coins[], const uint32_t n, const uint32_t V) { // O(nV)
  if (!V || !n)
    return 0;

  uint32_t dp[V+1];
  dp[0] = 0;

  for (uint32_t i = 1; i < V+1; ++i) {
    uint32_t v = MAX_LMT; // cannot use -1 here, why?

    for (uint32_t j = 0; j < n; ++j) {
      const int32_t left = i-coins[j];
      if (left >= 0) { // coin value should not exceed the amount itself
        v = min(v, dp[left]);
      }
    }

    if (v != MAX_LMT)
      dp[i] = v+1;
    else
      dp[i] = MAX_LMT;
  }

  return dp[V];
}

/*
Given a list of numbers, you and another player pick a number in turn. Both of players
can only pick left most or right most number and you get to pick first, how should you max your sum?

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

/*
Consider a game where a player can score 3 or 5 or 10 points in a move.
Given a total score n, find number of ways to reach the given score.

Input: n = 20
Output: 4
There are following 4 ways to reach 20
(10, 10)
(5, 5, 10)
(5, 5, 5, 5)
(3, 3, 3, 3, 3, 5)
 */
uint32_t count(const uint32_t n) {
  uint32_t dp[n+1];
  for (auto& i : dp)
    i = 0;
  dp[0] = 1; // if n is 0

  // One by one consider given 3 moves and update the table[]
  // values after the index greater than or equal to the value of the picked move
  for (uint32_t i = 3; i < n+1; ++i)
    dp[i] += dp[i-3];
  for (uint32_t i = 5; i < n+1; ++i)
    dp[i] += dp[i-5];
  for (uint32_t i = 10; i< n+1; ++i)
    dp[i] += dp[i-10];

  return dp[n];
}

int main(int argc, char** argv) {
  const uint8_t coins[] = {2, 3, 5, 6};
  uint32_t n = sizeof(coins)/sizeof(coins[0]);
  uint32_t V = 25;

  //cout << "There are " << makeChange_recur(N, S) << " ways to represent " << N << " cents!" << endl;
  cout << "There are " << makeChange_dp(coins, n, V) << " ways for changes!" << endl;

  const uint8_t coins2[] = {1, 5, 10, 25};
  n = sizeof(coins2)/sizeof(coins2[0]);
  cout << "There are " << makeChange_dp(coins2, n, V) << " ways to represent " << V << " cents!" << endl;

  const uint8_t coins3[] =  {9, 6, 5, 1};
  n = sizeof(coins3)/sizeof(coins3[0]);
  V = 11;
  cout << "Minimum coins required is " << minCoinNum(coins3, n, V) << endl;

  vector<uint32_t> nums = {5, 3, 7, 10};
  cout << "Max sum: " << coinsInALine(nums) << endl;
  nums = {8, 15, 3, 7};
  cout << "Max sum: " << coinsInALine(nums) << endl;

  n = 20;
  cout << "There are " << count(n) << " ways to reach " << n << endl;
  
  return 0;
}
