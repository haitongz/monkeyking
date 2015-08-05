/*
Harry Porter starts from up left corner, can only move right or down. If he steps in a cell with positive number his strength increases by that amount, otherwise decreases. Game will be over once his strength becomes zero. Find minimum initial strength Harry needs to reach right bottom corner?
 */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

static const uint32_t max_lmt = numerica_limits<int32_t>::max();

// formula: dp[i][j] = max(1, min(dp[i][j+1]-mat[i][j], dp[i+1][j]-mat[i][j]))
uint32_t minStrength(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return 0;

  vector<vector<int32_t>> dp(m, vector<int32_t>(n));
  // scanning start from bottom right
  for (int32_t i = m-1; i >= 0; --i) {
    for (int32_t j = n-1; j >= 0; --j) {
      if (i == m-1 && j == n-1) {
        dp[i][j] = max(1, 1-mat[i][j]);
      } else {
        int32_t right = (j == n-1) ? max_lmt : dp[i][j+1]-mat[i][j];
        int32_t down  = (i == m-1) ? max_lmt : dp[i+1][j]-mat[i][j];
        dp[i][j] = max(1, min(right, down));
      }
    }
  }

  return dp[0][0];
}

int main(int argc, char** argv) {
}
