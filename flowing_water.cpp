/*
In a N*N matrix, values represent heights. Water flows from high to low, find all points that water can flow to Pacific and Atlantic.

Pacific: ~
Atlantic: *

~  ~   ~   ~   ~   ~  ~
~  1   2   2   3  (5) *
~  3   2   3  (4) (4) *
~  2   4  (5)  3   1  *
~ (6) (7)  1   4   5  *
~ (5)  1   1   2   4  *
*  *   *   *   *   *  *

Output: [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
 */
#include <iostream>
#include <vector>
#include <functional>
#include <map>

using namespace std;

#if 0
typedef pair<uint32_t,uint32_t> Point;

vector<Point> flowingWater(const vector<vector<uint32_t>>& mat) {
  const uint32_t n = mat.size();
  if (!n)
    return {};

  function<bool(const Point&)> isValid = [&](const Point& p) {
    return (p.first >= 0 && p.first < n && p.second >= 0 && p.second < n);
  };

  static const vector<Point> dirs = {{0,1},{0,-1},{1,0},{-1,0}};

  function<void(const Point,map<Point,bool>&)> solve =
    [&](const Point pt, map<Point,bool>& visited) {
    for (auto dir : dirs) {
      Point newp = {dir.first+pt.first, dir.second+pt.second};
      if (!isValid(newp) ||
          mat[newp.first][newp.second] > mat[pt.first][pt.second] ||
          visited.count(newp))
        continue;

      visited[newp] = true;
      solve(newp, visited);
    }
  };

  map<Point,bool> visited_pac;
  for (uint32_t i = 0; i < n; ++i) {
    visited_pac[{0,i}] = true;
    solve({0,i}, visited_pac);
  }
  for (uint32_t i = 0; i < n; ++i) {
    visited_pac[{i,0}] = true;
    solve({i,0}, visited_pac);
  }

  map<Point,bool> visited_alt;
  for (uint32_t i = 0; i < n; ++i) {
    visited_alt[{n-1,i}] = true;
    solve({n-1,i}, visited_alt);
  }
  for (uint32_t i = 0; i < n; ++i) {
    visited_alt[{i,n-1}] = true;
    solve({i,n-1}, visited_alt);
  }

  vector<Point> ret;
  for (auto& p : visited_alt) {
    if (visited_pac.count(p.first))
      ret.push_back(p.first);
  }

  return ret;
}
#endif
struct Square {
  bool pacific;
  bool atlantic;
  bool visited;

  Square()
      : pacific(false),
        atlantic(false),
        visited(false) {
  }
};

struct Position {
  int32_t row, col;

  Position(const int32_t row_, const int32_t col_)
      : row(row_), col(col_) {
  }
};

vector<Position> flowingWater(const vector<vector<uint32_t>>& height) {
  const uint32_t m = height.size();
  const uint32_t n = height[0].size();

  vector<vector<Square>> grid(m, vector<Square>(n, Square()));

  // mark .pacific and .atlantic as true for edges
  for (uint32_t row = 0; row < m; ++row) {
    grid[row][0].pacific = true;
    grid[row][n-1].atlantic = true;
  }
  for (uint32_t col = 0; col < n; ++col) {
    grid[0][col].pacific = true;
    grid[m-1][col].atlantic = true;
  }

  // drop water on a square, let it flow to surrounding squares if possible, and then update the current square's .pacific and .atlantic instance variables
  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t row, const uint32_t col) {
    grid[row][col].visited = true;

    // up
    if (row != 0 && height[row][col] >= height[row-1][col]) {
      if (!grid[row-1][col].visited)
        solve(row-1, col);
      grid[row][col].pacific |= grid[row-1][col].pacific;
      grid[row][col].atlantic |= grid[row-1][col].atlantic;
    }

    // down
    if (row != m-1 && height[row][col] >= height[row+1][col]) {
      if (!grid[row+1][col].visited)
        solve(row+1, col);
      grid[row][col].pacific |= grid[row+1][col].pacific;
      grid[row][col].atlantic |= grid[row+1][col].atlantic;
    }

    // left
    if (col != 0 && height[row][col] >= height[row][col-1]) {
      if (!grid[row][col-1].visited)
        solve(row, col-1);
      grid[row][col].pacific |= grid[row][col-1].pacific;
      grid[row][col].atlantic |= grid[row][col-1].atlantic;
    }

    // right
    if (col != n-1 && height[row][col] >= height[row][col+1]) {
      if (!grid[row][col+1].visited)
        solve(row, col+1);
      grid[row][col].pacific |= grid[row][col+1].pacific;
      grid[row][col].atlantic |= grid[row][col+1].atlantic;
    }
  };

  // visit every square and drop water on it
  for (uint32_t row = 0; row < m; ++row) {
    for (uint32_t col = 0; col < n; ++col) {
      if (!grid[row][col].visited)
        solve(row, col);
    }
  }

  vector<Position> ret;
  for (uint32_t row = 0; row < m; ++row) {
    for (uint32_t col = 0; col < n; ++col) {
      if (grid[row][col].pacific && grid[row][col].atlantic)
        ret.push_back({row, col});
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<vector<uint32_t>> mat =
    {{'1', '2', '2', '3', '5'},
     {'3', '2', '3', '4', '4'},
     {'2', '4', '5', '3', '1'},
     {'6', '7', '1', '4', '5'},
     {'5', '1', '1', '2', '4'}};

  vector<Position> res = flowingWater(mat);
  for (auto& i : res)
    cout << "[" << i.row << "," << i.col << "]" << " ";
  cout << endl;

  return 0;
}
