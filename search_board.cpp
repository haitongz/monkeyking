/*
Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or
vertically neighboring. The same letter cell may not be used more than once.

Given board =
[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
 */
#include <iostream>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

bool found_recur(vector<vector<char>>& board, const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return false;

  const uint32_t m = board.size();
  const uint32_t n = board[0].size();
  if (!m || !n)
    return false;

  function<bool(const uint32_t,const uint32_t,const uint32_t)> isValid =
    [&](const uint32_t row, const uint32_t col, const uint32_t idx) {
    return (row < 0 || row >= m ||
            col < 0 || col >= n ||
            board[row][col] != s[idx]) ? false : true;
  };

  function<bool(const uint32_t,const uint32_t,const uint32_t)> solve =
    [&](const uint32_t row, const uint32_t col, const uint32_t idx) {
    if (idx == len)
      return true;

    if (!isValid(row, col, idx))
      return false;

    char cp = board[row][col];
    board[row][col] = '*';
    if (solve(row+1, col, idx+1) ||
        solve(row, col+1, idx+1) ||
        solve(row-1, col, idx+1) ||
        solve(row, col-1, idx+1))
      return true;

    board[row][col] = cp;
    return false;
  };

  for (uint32_t i = 0; i < m; ++i)
    for (uint32_t j = 0; j < n; ++j)
      if (solve(i, j, 0))
        return true;

  return false;
}

bool found_iter(vector<vector<char>>& board, const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return false;

  const uint32_t m = board.size();
  const uint32_t n = board[0].size();
  if (!m || !n)
    return false;

  stack<uint32_t> to_visit;
  bool visited[m][n];

  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      visited[i][j] = false;

      if (board[i][j] == s[0]) {
        to_visit.push(i*n+j);
      }
    }
  }

  uint32_t idx = 0;

  while (!to_visit.empty()) {
    const uint32_t root = to_visit.top();
    to_visit.pop();
    const uint32_t x = root/n;
    const uint32_t y = root%n;
    visited[x][y] = true;
    if (idx == len-1)
      return true;

    if (y > 0 && visited[x][y-1] == false && board[x][y-1] == s[idx+1]) { //left
      to_visit.push(x*n+y-1);
      ++idx;
    }
    if (y < n-1 && visited[x][y+1] == false && board[x][y+1] == s[idx+1]) { //right
      to_visit.push(x*n+y+1);
      ++idx;
    }
    if (x > 0 && visited[x-1][y] == false && board[x-1][y] == s[idx+1]) { //up
      to_visit.push((x-1)*n+y);
      ++idx;
    }
    if (x < m-1 && visited[x+1][y] == false && board[x+1][y] == s[idx+1]) { //down
      to_visit.push((x+1)*n+y);
      ++idx;
    }
  }

  return false;
}

int main(int argc, char** argv) {
  vector<vector<char>> board = {{'A','B','C','E'},
                                {'S','F','C','S'},
                                {'A','D','E','E'}};
  cout << (found_recur(board, "ABCCED") ? "exists" : "not exist") << endl;

  board = {{'A','B','C','E'},
           {'S','F','C','S'},
           {'A','D','E','E'}};
  cout << (found_iter(board, "ABCCED") ? "exists" : "not exist") << endl;
 // cout << (found_recur(board, "SEE") ? "exists" : "not exist") << endl;
 // cout << (exists(board, "ABCB") ? "exists" : "not exist") << endl;

  return 0;
}
