#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
Given a 2D screen, location of a pixel in the screen and a color, replace color of the given pixel and all adjacent same colored pixels with the given color.
Input:
       screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 1, 1, 1, 1, 1, 0, 0},
                       {1, 0, 0, 1, 1, 0, 1, 1},
                       {1, 2, 2, 2, 2, 0, 1, 0},
                       {1, 1, 1, 2, 2, 0, 1, 0},
                       {1, 1, 1, 2, 2, 2, 2, 0},
                       {1, 1, 1, 1, 1, 2, 1, 1},
                       {1, 1, 1, 1, 1, 2, 2, 1}};
    x = 4, y = 4, newColor = 3
The values in the given 2D screen indicate colors of the pixels. x and y are coordinates of the brush, newColor is the color that should replace the previous color on screen[x][y] and all surrounding pixels with same color.

Output:
Screen should be changed to following.
       screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
                       {1, 1, 1, 1, 1, 1, 0, 0},
                       {1, 0, 0, 1, 1, 0, 1, 1},
                       {1, 3, 3, 3, 3, 0, 1, 0},
                       {1, 1, 1, 3, 3, 0, 1, 0},
                       {1, 1, 1, 3, 3, 3, 3, 0},
                       {1, 1, 1, 1, 1, 3, 1, 1},
                       {1, 1, 1, 1, 1, 3, 3, 1}};
 */
// It mainly finds the previous color on (x, y) and // calls floodFillUtil()
void floodFill(vector<vector<uint32_t>>& screen,
               const uint32_t x, const uint32_t y, const uint32_t new_color) {
  const uint32_t M = screen.size(), N = screen[0].size();
  if (!M || !N)
    return;

  const uint8_t prev_color = screen[x][y];

  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t x, const uint32_t y) {
    if (x < 0 || x >= M || y < 0 || y >= N)
      return;
    if (screen[x][y] != prev_color)
      return;

    screen[x][y] = new_color;

    solve(x+1, y);
    solve(x-1, y);
    solve(x, y+1);
    solve(x, y-1);
  };

  solve(x, y);
}

/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Input: mat[M][N] =  {{'X', 'O', 'X', 'X', 'X', 'X'},
                     {'X', 'O', 'X', 'X', 'O', 'X'},
                     {'X', 'X', 'X', 'O', 'O', 'X'},
                     {'O', 'X', 'X', 'X', 'X', 'X'},
                     {'X', 'X', 'X', 'O', 'X', 'O'},
                     {'O', 'O', 'X', 'O', 'O', 'O'}};

Output: mat[M][N] =  {{'X', 'O', 'X', 'X', 'X', 'X'},
                      {'X', 'O', 'X', 'X', 'X', 'X'},
                      {'X', 'X', 'X', 'X', 'X', 'X'},
                      {'O', 'X', 'X', 'X', 'X', 'X'},
                      {'X', 'X', 'X', 'O', 'X', 'O'},
                      {'O', 'O', 'X', 'O', 'O', 'O'}};
 */
const static char NOT_SURROUNDED = '*';

void capture(vector<vector<char>>& board) {
  const uint32_t m = board.size();
  const uint32_t n = board[0].size();
  if (!m || !n)
    return;

  function<bool(const int32_t,const int32_t)> isValid =
    [&](const int32_t row, const int32_t col) {
    return !(row < 0 || row >= m || col < 0 || col >= n || board[row][col] != 'O');
  };

  function<void(const int32_t,const int32_t)> solve =
    [&](const int32_t row, const int32_t col) {
    if (!isValid(row, col))
      return;

    board[row][col] = NOT_SURROUNDED;

    solve(row+1, col);
    solve(row-1, col);
    solve(row, col+1);
    solve(row, col-1);
  };

  for (uint32_t i = 0; i < m; ++i) {
    solve(i, 0);
    solve(i, n-1);
  }
/*
  cout << "Checking first and last column..." << endl;
  for (auto& i : board) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }
*/
  for (uint32_t i = 1; i < n; ++i) {
    solve(0, i);
    solve(m-1, i);
  }
/*
  cout << "Checking first and last row..." << endl;
  for (auto& i : board) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }
*/
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (board[i][j] == NOT_SURROUNDED)
        board[i][j] = 'O';
      else
        board[i][j] = 'X';
    }
  }
}

int main(int argc, char** argv) {
  vector<vector<uint32_t>> screen =
    {{1, 1, 1, 1, 1, 1, 1, 1},
     {1, 1, 1, 1, 1, 1, 0, 0},
     {1, 0, 0, 1, 1, 0, 1, 1},
     {1, 2, 2, 2, 2, 0, 1, 0},
     {1, 1, 1, 2, 2, 0, 1, 0},
     {1, 1, 1, 2, 2, 2, 2, 0},
     {1, 1, 1, 1, 1, 2, 1, 1},
     {1, 1, 1, 1, 1, 2, 2, 1}};

  uint32_t x = 4, y = 4, newC = 3;
  floodFill(screen, x, y, newC);

  cout << "Updated screen after call to floodFill: \n";
  for (const auto& i : screen) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

/*  vector<vector<char>> board = {{'X','X','X','X'},
                                {'X','O','O','X'},
                                {'X','X','O','X'},
                                {'X','O','X','X'}};*/
  vector<vector<char>> board =
    {{'X', 'O', 'X', 'X', 'X', 'X'},
     {'X', 'O', 'X', 'X', 'O', 'X'},
     {'X', 'X', 'X', 'O', 'O', 'X'},
     {'O', 'X', 'X', 'X', 'X', 'X'},
     {'X', 'X', 'X', 'O', 'X', 'O'},
     {'O', 'O', 'X', 'O', 'O', 'O'}};

  capture(board);

  for (const auto& i : board) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
