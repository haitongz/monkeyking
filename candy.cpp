/*
There are N children standing in a line. Each child is assigned a rating value. You are giving candies to these children subjected to the following requirements:
Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
 */
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

uint32_t minCandies(const double ratings[], const uint32_t N) {
  vector<uint32_t> dp(N, 0);
  dp[0] = 1;

  for (uint32_t i = 1; i < N; ++i) {
    dp[i] = (ratings[i] > ratings[i-1]) ? (dp[i-1]+1) : 1;
  }

  uint32_t res = dp[N-1];
  for (int32_t i = N-2; i >= 0; --i) {
    if (ratings[i] > ratings[i+1]) {
      if (dp[i] > dp[i+1]+1) {
        cout << "Turning, dp[" << i << "]: " << dp[i] << ", dp[" << (i+1) << "]: " << dp[i+1] << endl;
      }

      dp[i] = max(dp[i], dp[i+1]+1);
    }
    res += dp[i];
  }

  return res;
}

int main(int argc, char** argv) {
  srand(time(NULL));

  uint32_t N = 10;
  double ratings[N];
  for (uint32_t i = 0; i < N; ++i) {
     ratings[i] = (rand()%100+1)/(i+1);
     cout << "Rating[" << i << "]: " << ratings[i] << endl;
  }

  cout << "Minimum candies: " << minCandies(ratings, N) << endl;
}
