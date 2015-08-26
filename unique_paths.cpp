/*
Imagine a robot sitting on the upper left corner of an X by Y grid. The robot can only move in two directions:
right and down. How many possible paths are there for the robot to go from (0, 0) to (X, Y)?

FOLLOW UP: Imagine certain spots are "off limits", such that the robot cannot step on them.
 */
#include <iostream>
#include <vector>

using namespace std;

uint32_t uniquePaths(const uint32_t m, const uint32_t n) {
  if (!m || !n)
    return 0;

  vector<uint32_t> dp(n, 1);

  for (uint32_t i = 1; i < m; ++i) {
    for (uint32_t j = 1; j < n; ++j) {
      dp[j] = dp[j-1] + dp[j];
    }
  }

  return dp[n-1];
}

/*
Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.
 */
uint32_t uniquePathsWithObstacles(const vector<vector<uint8_t>>& obstacleGrid) {
  const uint8_t m = obstacleGrid.size();
  const uint8_t n = obstacleGrid[0].size(); // at most 100

  uint32_t dp[m][n];
  for (uint32_t i = 0; i < n; ++i) {
    if (obstacleGrid[0][i] != 1) {
      dp[0][i] = 1;
    } else
      break;
  }

  for (uint32_t i = 0; i < m; ++i) {
    if (obstacleGrid[i][0] != 1) {
      dp[i][0] = 1;
    } else
      break;
  }

  for (uint32_t i = 1; i < m; ++i) {
    for (uint32_t j = 1; j < n; ++j) {
      if (obstacleGrid[i][j] == 1)
        continue;
      else {
        dp[i][j] = dp[i-1][j] + dp[i][j-1];
      }
    }
  }

  return dp[m-1][n-1];
}

int main(int argc, char** argv) {
  uint32_t x = 100, y = 100;
  cout << "There are " << uniquePaths(x, y) << " unique paths!" << endl;

  const vector<vector<uint8_t>> grid = {{0,0,0},
                                        {0,1,0},
                                        {0,0,0}};
  cout << uniquePathsWithObstacles(grid) << " step!" << endl;
}
