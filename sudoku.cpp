/*
Write a program to solve a Sudoku puzzle by filling the empty cells. Empty cells are indicated by the character '.'.
You may assume that there will be only one unique solution.
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// N is used for size of Sudoku grid. Size will be NxN
#define N 9
#define S_N 3

bool solveSudoku(vector<vector<char>>& board) {
  function<bool(const uint8_t,const uint8_t)> isValid =
    [&](const uint8_t row, const uint8_t col) {
    const uint8_t s_row = row/S_N;
    const uint8_t s_col = col/S_N;
    for (uint8_t i = 0; i < N; ++i) {
      if (i != col && board[row][col] == board[row][i])
        return false;
      if (i != row && board[row][col] == board[i][col])
        return false;

      const uint8_t r = s_row*S_N+i/S_N;
      const uint8_t c = s_col*S_N+i%S_N;
      if (!(r == row && c == col) && board[row][col] == board[r][c])
        return false;
    }

    return true;
  };

  function<bool(const uint8_t,const uint8_t)> backtrack =
    [&](const uint8_t row, const uint8_t col) {
    if (row == N)
      return true;

    const uint8_t nr = (col == N-1) ? row+1 : row;
    const uint8_t nc = (col == N-1) ? 0 : col+1;

    if (board[row][col] != '.') {
      if (backtrack(nr, nc))
        return true;
    } else {
      for (char i = '1'; i <= '9'; ++i) {
        board[row][col] = i;
        if (isValid(row, col) && backtrack(nr, nc))
          return true;
      }

      board[row][col] = '.';
    }

    return false;
  };

  return backtrack(0, 0);
}

int main(int argc, char** argv) {
  vector<vector<char>> board =
    {{'3', '.', '6', '5', '.', '8', '4', '.', '.'},
     {'5', '2', '.', '.', '.', '.', '.', '.', '.'},
     {'.', '8', '7', '.', '.', '.', '.', '3', '1'},
     {'.', '.', '3', '.', '1', '.', '.', '8', '.'},
     {'9', '.', '.', '8', '6', '3', '.', '.', '5'},
     {'.', '5', '.', '.', '9', '.', '6', '.', '.'},
     {'1', '3', '.', '.', '.', '.', '2', '5', '.'},
     {'.', '.', '.', '.', '.', '.', '.', '7', '4'},
     {'.', '.', '5', '2', '.', '6', '3', '.', '.'}};

  if (solveSudoku(board)) {
    for (auto& i : board) {
      for (auto j : i)
        cout << j << " ";
      cout << endl;
    }
  } else
    cerr << "No solution exists" << endl;

  return 0;
}
