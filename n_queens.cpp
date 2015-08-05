#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
 */
vector<vector<string>> solveNQueens(const uint8_t n) {
  if (n <= 1)
    return {};

  vector<vector<string>> ret;
  vector<string> s(n, string(n, '.'));

  function<bool(const uint8_t,const uint8_t)> isValid =
    [&](const uint8_t row, const uint8_t col) {
    for (int8_t i = row-1, j = col-1, k = col+1; i >= 0; --i, --j, ++k) {
      if (s[i][col] == 'Q' ||
          (j >= 0 && s[i][j] == 'Q') ||
          (k < n && s[i][k] == 'Q'))
        return false;
    }

    return true;
  };

  function<void(uint8_t)> backtrack = [&](const uint8_t row) {
    if (row == n) {
      ret.push_back(s);
      return;
    }

    for (uint8_t col = 0; col < n; ++col) {
      if (isValid(row, col)) {
        s[row][col] = 'Q';
        backtrack(row+1);
        s[row][col] = '.';
      }
    }
  };

  backtrack(0);
  return ret;
}

/*
Return distinct solutions
 */
uint32_t totalNQueens(const uint8_t n) {
  if (n <= 1)
    return 1;

  vector<int32_t> q(n, -1);

  function<bool(const uint8_t,const uint8_t col)> isValid =
    [&](const uint8_t row, const uint8_t col) {
    for (uint8_t i = 0; i < row; ++i) {
      if (q[i] == col || q[i]-i == col-row || q[i]+i == col+row)
        return false;
    }

    return true;
  };

  function<uint32_t(const uint8_t)> backtrack =
    [&](const uint8_t row) -> uint32_t {
    if (row == n)
      return 1;

    uint32_t ret = 0;
    for (uint8_t i = 0; i < n; ++i) {
      if (isValid(row, i)) {
        q[row] = i;
        ret += backtrack(row+1);
        q[row] = -1;
      }
    }

    return ret;
  };

  return backtrack(0);
}

int main(int argc, char** argv) {
  uint8_t n = 4;
  vector<vector<string>> res = solveNQueens(n);
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << "Solution " << i+1 << endl;
    for (uint32_t j = 0; j < n; ++j) {
      cout << res[i][j] << endl;
    }
  }

  cout << "Total solution number: " << totalNQueens(n*2) << endl;
  return 0;
}
