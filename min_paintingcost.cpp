/*
There are N houses in a row. Each house can be painted in either Red, Green or Blue color. The cost of coloring each house in each of the colors is different.
Find the color of each house such that no two adjacent house have the same color and the total cost of coloring all the houses is minimum.
*/
#include <iostream>

using namespace std;

uint32_t minPaintingCost(const uint32_t costs[][3], const uint32_t N) {
  uint32_t dp[N+1][3];

  for (uint8_t i = 0; i < 3; ++i) {
    dp[0][i] = 0;
  }

  for (uint32_t i = 1; i < N+1; ++i) {
    dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i-1][0]; // use costs[i-1] because costs has one row less
    dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i-1][1];
    dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i-1][2];
  }

  return min(min(dp[N][0], dp[N][1]), dp[N][2]);
}

int main(int argc, char** argv) {
  uint32_t N = 6;
  uint32_t costs[6][3] = {{7, 5, 10},
                          {3, 6, 1},
                          {8, 7, 4},
                          {6, 2, 9},
                          {1, 4, 7},
                          {2, 3, 6}};

  cout << "Min painting cost: " << minPaintingCost(costs, N) << endl;
  return 0;
}
