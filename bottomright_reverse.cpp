#include <iostream>
#include <vector>
#include <limits>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();

/*
Harry Porter starts from up left corner, can only move right or down.
If he steps in a cell with positive number his strength increases by that amount, otherwise decreases.
Game will be over once his strength becomes zero.
Find minimum initial strength Harry needs to reach right bottom corner?
 */
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
        int32_t right = (j == n-1) ? MAX_LMT : dp[i][j+1]-mat[i][j];
        int32_t down  = (i == m-1) ? MAX_LMT : dp[i+1][j]-mat[i][j];
        dp[i][j] = max(1, min(right, down));
      }
    }
  }

  return dp[0][0];
}

/*
Given a grid with each cell consisting of positive, negative or no points i.e, zero points.
We can move across a cell only if we have positive points. Whenever we pass through a cell,
points in that cell are added to our overall points. We need to find minimum initial points to
reach cell (m-1, n-1) from (0, 0).

Constraints :
From a cell (i, j) we can move to (i+1, j) or (i, j+1).
We cannot move from (i, j) if your overall points at (i, j) is <= 0.
We have to reach at (n-1, m-1) with minimum positive points i.e., > 0.

Input: points[m][n] = {{-2,  -3,  3},
                       {-5, -10,  1},
                       {10,  30, -5}};
Output: 7

Explanation:
7 is the minimum value to reach destination with positive throughout the path. Below is the path.

(0,0) -> (0,1) -> (0,2) -> (1, 2) -> (2, 2)

We start from (0, 0) with 7, we reach(0, 1) with 5, (0, 2) with 2, (1, 2) with 5, (2, 2)
with 6 and finally we have 1 point (we needed greater than 0 points at the end).
 */
#define R 3
#define C 3

// formula: dp[i][j] = max(minpts_on_exit–points[i][j], 1)
uint32_t minInitialPoints(const int32_t points[][C]) {
  // dp[i][j] represents the minimum initial points player should have
  // so that when starts with cell(i, j) successfully reaches the destination cell(m-1, n-1)
  uint32_t dp[R][C];
  uint32_t m = R, n = C;
  dp[m-1][n-1] = points[m-1][n-1] > 0 ? 1 : (abs(points[m-1][n-1])+1);

  // Fill last row and last column as base to fill entire table
  for (int32_t i = m-2; i >= 0; --i)
    dp[i][n-1] = max(dp[i+1][n-1]-points[i][n-1], (uint32_t)1);
  for (int32_t j = n-2; j >= 0; --j)
    dp[m-1][j] = max(dp[m-1][j+1]-points[m-1][j], (uint32_t)1);

  for (int32_t i = m-2; i >= 0; --i) {
    for (int32_t j = n-2; j >= 0; --j) {
      uint32_t minpts_on_exit = min(dp[i+1][j], dp[i][j+1]);
      dp[i][j] = max(minpts_on_exit-points[i][j], (uint32_t)1);
    }
  }

  return dp[0][0];
}

int main(int argc, char** argv) {
  int32_t points[R][C] =
    {{-2,  -3,  3},
     {-5, -10,  1},
     {10,  30, -5}};

  cout << "Min initial points required: "
    << minInitialPoints(points) << endl;

  return 0;
}
