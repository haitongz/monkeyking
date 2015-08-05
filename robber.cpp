#include <iostream>
#include <vector>

using namespace std;

/*
A professional robber plans to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping him from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
 */
uint32_t rob(const vector<uint32_t>& money) {
  const uint32_t n = money.size();
  if (!n)
    return 0;

  vector<uint32_t> dp(n+1, 0);
  dp[0] = 0;
  dp[1] = money[0];

  for (uint32_t i = 2; i < n+1; ++i) {
    dp[i] = max(dp[i-2]+money[i-1], dp[i-1]);
  }

  return dp[n];
}

int main(int argc, char** argv) {
  const vector<uint32_t> money = {1,2,3,4,5,6,7,8,9};
  cout << rob(money) << endl;
  return 0;
}
