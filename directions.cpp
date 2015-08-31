#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is
formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are
all surrounded by water.

Example 1:
11110
11010
11000
00000
Answer: 1

Example 2:
11000
11000
00100
00011
Answer: 3

For example:
0011010
0010010
1000110
0000001

From first 1 element, find connected area and mark it with 2:
0022010
0020010
1000110
0000001

From next 1 element, find connected area and mark it with 3:
0022030
0020030
1000330
0000001

...
Final grid:
0022030
0020030
4000330
0000005

Number of islands is 4
 */
uint32_t islandNum(vector<vector<uint32_t>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return 0;

  static const vector<pair<int8_t,int8_t>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

  function<void(const uint32_t,const uint32_t)> solve = // color filling
    [&](const uint32_t row, const uint32_t col) {
    for (auto d : dirs) {
      const int32_t new_row = row+d.first;
      const int32_t new_col = col+d.second;
      if (new_row < 0 || new_col < 0 || new_row >= m || new_col >= n)
        continue;

      if (mat[new_row][new_col] != 1)
        continue;

      mat[new_row][new_col] = mat[row][col];
      solve(new_row, new_col);
    }
  };

  uint32_t count = 2;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (mat[i][j] == 1) {
        mat[i][j] = ++count;
        solve(i, j);
      }
    }
  }

  return count-2;
}

/*
Given a rectangular matrix which has only two possible values 'X' and 'O'. The values 'X' always appear in form of
rectangular islands and these islands are always row-wise and column-wise separated by at least one line of 'O's.
Note that islands can only be diagonally adjacent. Count the number of islands in the given matrix.

mat[M][N] =  {{'X', 'O', 'O', 'O', 'O', 'O'},
              {'X', 'O', 'X', 'X', 'X', 'X'},
              {'O', 'O', 'O', 'O', 'O', 'O'},
              {'X', 'X', 'X', 'O', 'X', 'X'},
              {'X', 'X', 'X', 'O', 'X', 'X'},
              {'O', 'O', 'O', 'O', 'X', 'X'},
             };
Output: Number of islands is 4
 */
uint32_t islandNum2(const vector<vector<char>>& mat) {
  const uint32_t M = mat.size(), N = mat[0].size();
  if (!M || !N)
    return 0;

  uint32_t ret = 0;

  for (uint32_t i = 0; i < M; ++i) {
    for (uint32_t j = 0; j < N; ++j) {
      // If current cell is 'X', then check whether this is top-leftmost of a rectangle. If yes, then increment count
      if (mat[i][j] == 'X') {
        if ((!i || mat[i-1][j] == 'O') &&
            (!j || mat[i][j-1] == 'O'))
          ++ret;
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<vector<uint32_t>> grid = {{1,1,1,1,0},
                                   {1,1,0,1,0},
                                   {1,1,0,0,0},
                                   {0,0,0,0,0}};
  cout << islandNum(grid) << endl;

  grid = {{1,1,0,0,0},
          {1,1,0,0,0},
          {0,0,1,0,0},
          {0,0,0,1,1}};
  cout << islandNum(grid) << endl;

  vector<vector<char>> grid2 =
    {{'X', 'O', 'O', 'O', 'O', 'O'},
     {'X', 'O', 'X', 'X', 'X', 'X'},
     {'O', 'O', 'O', 'O', 'O', 'O'},
     {'X', 'X', 'X', 'O', 'X', 'X'},
     {'X', 'X', 'X', 'O', 'X', 'X'},
     {'O', 'O', 'O', 'O', 'X', 'X'}};
  cout << islandNum2(grid2) << endl;

  return 0;
}
