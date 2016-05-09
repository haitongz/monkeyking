#include <iostream>
#include <limits>
#include <functional>

using namespace std;

static const uint MAX_LMT = numeric_limits<uint>::has_infinity ?
                            numeric_limits<uint>::infinity() : numeric_limits<uint>::max();

/*
Given a value N, if we want to make change for N cents,
and we have infinite supply of each of S = {S1,S2,...,Sm} valued coins,
how many ways can we make the change? The order of coins doesn't matter.

For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}.
So output should be 4. For N = 10 and S = {2,5,3,6}, there are five solutions:
{2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.
 */
/*
   these 2 don't work
uint makeChange_recur(const uint coins[], const uint n, const uint V) {
  if (!n || !V)
    return 0;

  function<uint(const uint,const uint)> solve =
    [&](const uint remain, const uint coin_num) -> uint {
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

uint makeChange_dp(const uint coins[], const uint n, const uint V) {
  if (!V || !n)
    return 0;

  uint dp[V+1];
  for (auto& i : dp)
    i = 0;
  dp[0] = 1;

  // Pick all coins one by one and update dp values after index >= the value of the picked coin
  for (uint i = 0; i < V; ++i) {
    const uint i_value = coins[i];
    for (uint j = i_value; j < n+1; ++j)
      dp[j] += dp[j-i_value];
  }

  return dp[n];
}
 */
uint makeChange_dp(const uint coins[], const uint n, const uint V) {
  if (!V || !n)
    return 0;

  // We need V+1 rows as the table is consturcted in bottom up manner using the
  // base case 0 value case (V = 0)
  uint dp[V+1][n];
  for (uint i = 0; i < n; ++i)
    dp[0][i] = 1;

  for (uint i = 1; i < V+1; ++i) {
    for (uint j = 0; j < n; ++j) {
      // Count of solutions excluding coin S[j]
      const uint s1 = (j >= 1) ? dp[i][j-1] : 0;
      // Count of solutions including S[j]
      const int left = i-coins[j];
      const uint s2 = (left >= 0) ? dp[left][j] : 0;
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
uint minCoinNum(const uint coins[], const uint n, const uint V) { // O(nV)
  if (!V || !n)
    return 0;

  uint dp[V+1];
  dp[0] = 0;

  for (uint i = 1; i < V+1; ++i) {
    uint v = MAX_LMT; // cannot use -1 here, why?

    for (uint j = 0; j < n; ++j) {
      const int left = i-coins[j];
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
uint coinsInALine(const uint nums[], const uint n) {
  if (!n)
    return 0;

  uint dp[n][n];

  for (uint k = 0; k < n; ++k) {
    for (uint i = 0, j = k; j < n; ++i, ++j) {
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
uint count(const uint n) {
  uint dp[n+1];
  for (auto& i : dp)
    i = 0;
  dp[0] = 1; // if n is 0

  // One by one consider given 3 moves and update the table[]
  // values after the index greater than or equal to the value of the picked move
  for (uint i = 3; i < n+1; ++i)
    dp[i] += dp[i-3];
  for (uint i = 5; i < n+1; ++i)
    dp[i] += dp[i-5];
  for (uint i = 10; i< n+1; ++i)
    dp[i] += dp[i-10];

  return dp[n];
}

int main(int argc, char** argv) {
  const uint coins[] = {2, 3, 5, 6};
  uint n = sizeof(coins)/sizeof(coins[0]);
  uint V = 25;

  cout << "There are " << makeChange_dp(coins, n, V) << " ways for changes!" << endl;

  const uint coins2[] = {1, 5, 10, 25};
  n = sizeof(coins2)/sizeof(coins2[0]);
  cout << "There are " << makeChange_dp(coins2, n, V) << " ways to represent " << V << " cents!" << endl;

  const uint coins3[] = {9, 6, 5, 1};
  n = sizeof(coins3)/sizeof(coins3[0]);
  V = 11;
  cout << "Minimum coins required is " << minCoinNum(coins3, n, V) << endl;

  const uint coins4[] = {5, 3, 7, 10};
  cout << "Max sum: " << coinsInALine(coins4, 4) << endl;
  const uint coins5[] = {8, 15, 3, 7};
  cout << "Max sum: " << coinsInALine(coins5, 4) << endl;

  n = 20;
  cout << "There are " << count(n) << " ways to reach " << n << endl;

  return 0;
}
