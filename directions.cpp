#include <iostream>
#include <vector>
#include <functional>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();

/*
Given a sequence of moves for a robot, check if the sequence is circular or not. A sequence of moves is circular
if first and last positions of robot are same. A move can be on of the following:
  G - Go one unit
  L - Turn left
  R - Turn right
 */
bool isCircularMoves(const char seq[], const uint32_t N) {
  // Initialize starting point for robot as (0, 0) and starting direction as N North
  uint32_t x = 0, y = 0;
  uint32_t dir = N;

  for (uint32_t i = 0; seq[i]; ++i) {
    char move = seq[i];
    if (move == 'R') // If move is left or right, then change direction
      dir = (dir+1)%4;
    else if (move == 'L')
      dir = (4+dir-1)%4;
    else { // if (move == 'G')
      // If move is Go, then change x or y according to current direction
      if (dir == N)
        ++y;
      else if (dir == E)
        ++x;
      else if (dir == S)
        --y;
      else // dir == W
        --x;
    }
  }

  // If robot comes back to (0, 0), then path is cyclic
  return (x == 0 && y == 0);
}

/*
Given a two dimensional array, obstacles are marked as '1', points are marked as 'P', empty cells are marked as '0'.
Given k points, find the cell with smallest distance sum to all points.
 */
typedef pair<uint32_t,uint32_t> Point;

Point closest2AllPts(const vector<vector<char>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return {};

  vector<Point> pts;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (mat[i][j] == 'P')
        pts.push_back({i,j});
    }
  }

  struct Node {
    uint32_t dist_sum {0};
    bool visited {false};
  };

  static const vector<pair<const int8_t,const int8_t>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
  vector<vector<Node>> nodes(m, vector<Node>(n));
  const uint32_t k = pts.size();

  for (uint32_t i = 0; i < k; ++i) {
    for (auto& j : nodes)
      for (auto& l : j)
        l.visited = false;

    deque<Point> q {pts[i]};
    deque<uint32_t> dists {0};
    nodes[pts[i].first][pts[i].second].visited = true;

    while (!q.empty()) {
      auto curr = q.front();
      q.pop_front();
      auto dist = dists.front();
      dists.pop_front();

      for (const auto& d : dirs) {
        Point newp = {d.first+curr.first, d.second+curr.second};
        if (newp.first < 0 || newp.second < 0 || newp.first >= m || newp.second >= n)
          continue;
        if (mat[newp.first][newp.second] == '1')
          continue;
        if (nodes[newp.first][newp.second].visited)
          continue;

        nodes[newp.first][newp.second].visited = true;
        nodes[newp.first][newp.second].dist_sum += dist+1;
        q.push_back(newp);
        dists.push_back(dist+1);
      }
    }
  }

  uint32_t min_sum = MAX_LMT;
  Point ret;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (mat[i][j] == '0') {
        if (nodes[i][j].dist_sum < min_sum) {
          min_sum = nodes[i][j].dist_sum;
          ret = {i,j};
        }
      }
    }
  }

  return ret;
}

/*
Given NxN matrix, -1 represent a closed room, MAX_LMT represents an open room, 0 represents a policeman.
Return a NxN matrix with each element representing shortest distance of nearest policeman.
 */
void policeRooms(vector<vector<int32_t>>& rooms) {
  const uint32_t n = rooms.size();
  if (!n)
    return;

  static const vector<pair<const int8_t,const int8_t>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
  set<Point> visited;
  deque<Point> q;
  deque<uint32_t> dists;

  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (!rooms[i][j]) {
        q.push({i,j});
        visited.insert({i,j});
        dists.push(0);
      }
    }
  }

  while (!q.empty()) {
    auto pos = q.front();
    q.pop();

    auto dist = dists.front();
    dists.pop();

    for (const auto& dir : dirs) {
      Point curr = {dir.first+pos.first, dir.second+pos.second};
      if (curr.first < 0 || curr.second < 0 || curr.first >= n || curr.second >= n)
        continue;

      if (visited.count(curr))
        continue;

      if (rooms[curr.first][curr.second] == -1) {
        visited.insert(curr);
        continue;
      }

      visited.insert(curr);
      dists.push(dist+1);
      q.push(curr);

      rooms[curr.first][curr.second] = min(rooms[curr.first][curr.second], dist+1);
    }
  }
}

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
