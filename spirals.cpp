#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
Given a matrix of m X n elements (m rows, n columns), return all elements of the matrix in spiral order.

Given the following matrix:
[
 [1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]
]

You should return [1,2,3,6,9,8,7,4,5].
 */
#if 0
enum DIRECTIONS {
  RIGHT = 0,
  DOWN,
  LEFT,
  UP,
  INVALID
};

vector<int32_t> spiralOrder(vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return {};

  vector<int32_t> result;
  DIRECTIONS direction = RIGHT;
  // steps for 4 directions
  int8_t x_steps[4] = {1,0,-1,0};
  int8_t y_steps[4] = {0,1, 0,-1};
  uint32_t x_pos = 0, y_pos = 0;
  uint32_t visited_rows = 0;
  uint32_t visited_cols = 0;
  uint32_t check_point = 0, runner = 0;

  while (true) {
    if (!x_steps[direction]) // visit y axis
      check_point = m-visited_rows;
    else // visit x axis
      check_point = n-visited_cols;
    if (check_point <= 0)
      break;

    result.push_back(mat[y_pos][x_pos]);
    ++runner;
    if (check_point == runner) { // change direction
      visited_rows += abs(x_steps[direction]);
      visited_cols += abs(y_steps[direction]);
      direction = (DIRECTIONS)((int)(direction+1)%(int)INVALID);
      runner = 0;
    }

    x_pos += x_steps[direction];
    y_pos += y_steps[direction];
  }

  return result;
}
#endif
vector<int32_t> spiralOrder(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return {};

  vector<int32_t> ret;

  function<void(const uint32_t,const uint32_t,const uint32_t)> solve =
    [&](const uint32_t row, const uint32_t col, const uint32_t idx) {
    if (row <= 0 || col <= 0)
      return;
    if (row == 1) {
      for (uint32_t i = 0; i < col; ++i)
        ret.push_back(mat[idx][idx+i]);
      return;
    }
    if (col == 1) {
      for (uint32_t i = 0; i < row; ++i)
        ret.push_back(mat[idx+i][idx]);
      return;
    }

    for (uint32_t i = 0; i < col-1; ++i)
      ret.push_back(mat[idx][idx+i]);
    for (uint32_t i = 0; i < row-1; ++i)
      ret.push_back(mat[idx+i][idx+col-1]);
    for (uint32_t i = 0; i < col-1; ++i)
      ret.push_back(mat[idx+row-1][idx+col-1-i]);
    for (uint32_t i = 0; i < row-1; ++i)
      ret.push_back(mat[idx+row-1-i][idx]);

    solve(row-2, col-2, idx+1);
  };

  solve(m, n, 0);
  return ret;
}
#if 0
vector<int32_t> spiralOrder(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return {};

  vector<int32_t> res;

  uint32_t layer = min(m, n)/2;
  for (uint32_t k = 0; k < layer; ++k) {
    for (uint32_t j = 0+k; j < n-k; ++j)
      res.push_back(mat[k][j]);
    for (uint32_t i = k+1; i < m-k; ++i)
      res.push_back(mat[i][n-1-k]);
    for (uint32_t j = n-2-k; j >= k; --j)
      res.push_back(mat[n-1-k][j]);
    for (uint32_t i = m-2-k; i > k; --i)
      res.push_back(mat[i][k]);
  }

  for (uint32_t i = layer; i < m-layer; ++i) {
    for (uint32_t j = layer; j < n-layer; ++j) {
      res.push_back(mat[i][j]);
    }
  }

  return res;
}
#endif
/*
Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.
 */
vector<vector<uint32_t>> spiralMatrix(const uint32_t n) {
  if (!n)
    return {};

  vector<vector<uint32_t>> ret(n, vector<uint32_t>(n, n*n));
  uint32_t value = 1;

  for (uint32_t row = 0; row < n/2; ++row) {
    uint32_t nums = n-1-2*row;
    for (uint32_t i = 0; i < nums; ++i)
      ret[row][row+i] = value++;
    for (uint32_t i = 0; i < nums; ++i)
      ret[row+i][n-row-1] = value++;
    for (uint32_t i = 0; i < nums; ++i)
      ret[n-row-1][n-row-1-i] = value++;
    for (uint32_t i = 0; i < nums; ++i)
      ret[n-row-1-i][row] = value++;
  }

  return ret;
}

/*
Write a code which inputs two numbers m and n and creates a matrix of size m x n (m rows and n columns) in which every elements is either X or 0. The Xs and 0s must be filled alternatively, the matrix should have outermost rectangle of Xs, then a rectangle of 0s, then a rectangle of Xs, and so on.

Input:  m = 6, n = 7
Output: Following matrix
X X X X X X X
X 0 0 0 0 0 X
X 0 X X X 0 X
X 0 X X X 0 X
X 0 0 0 0 0 X
X X X X X X X
 */
vector<vector<char>> alternateRec(uint32_t m, uint32_t n) {
    // Store given number of rows and columns for later use
    int r = m, c = n;

  vector<vector<char>> ret;
  char x = 'X'; // Iniitialize the character to be stoed in a[][]
  /*  k - starting row index
      l - starting column index
   */
  uint32_t k = 0, l = 0;

  // Every iteration fills one rectangle of either Xs or Os
  while (k < m && l < n) {
    /* Fill the first row from the remaining rows */
    for (uint32_t i = l; i < n; ++i)
      ret[k][i] = x;
    ++k;

    /* Fill the last column from the remaining columns */
    for (uint32_t i = k; i < m; ++i)
      ret[i][n-1] = x;
    --n;

    /* Fill the last row from the remaining rows */
    if (k < m) {
      for (uint32_t i = n-1; i >= l; --i)
        ret[m-1][i] = x;
      --m;
    }

    /* Print the first column from the remaining columns */
    if (l < n) {
      for (uint32_t i = m-1; i >= k; --i)
        ret[i][l] = x;
      ++l;
    }

    // Flip character for next iteration
    x = (x == 'O') ? 'X' : 'O';
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<vector<int32_t>> mat = {{1,2,3}, {4,5,6}, {7,8,9}};
  cout << "Spiral order of matrix: ";
  vector<int32_t> res = spiralOrder(mat);
  for (auto i : res)
    cout << i << " ";
  cout << endl;
  /*res = SpiralOrder2(mat);
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << res[i] << ",";
  }
  cout << endl;
  res = SpiralOrder3(mat);
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << res[i] << ",";
  }
  cout << endl;
*/

  cout << "Matrix in spiral order: " << endl;
  vector<vector<uint32_t>> res2 = spiralMatrix(9);
  for (auto& i : res2) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  vector<vector<char>> res3 = alternateRec(6, 7);
  for (const auto& i : res3) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
