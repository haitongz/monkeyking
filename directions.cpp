#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();
static const int32_t MIN_LMT = numeric_limits<int32_t>::min();

/*
Given a sequence of moves for a robot, check if the sequence is circular or not. A sequence of moves is circular
if first and last positions of robot are same. A move can be on of the following:
  G - Go one unit
  L - Turn left
  R - Turn right
 */
bool areCircularMoves(const char seq[]) { // Initialize starting point for robot as (0, 0) and starting direction as N North
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

/*
Given a matrix of characters. Find length of the longest path from a given character,
such that all characters in the path are consecutive to each other, i.e., every character in path
is next to previous in alphabetical order. It is allowed to move in all 8 directions from a cell.

Input: matt[][] = {{a, c, d},
                   {h, b, e},
                   {i, g, f}}
      Starting Point = 'e'

Output: 5

If starting point is 'e', then longest path with consecutive characters is "e f g h i".

Input: matt[R][C] = {{b, e, f},
                     {h, d, a},
                     {i, c, a}};
      Starting Point = 'b'

Output: 1
'c' is not present in all adjacent cells of 'b'
 */
#define R 3
#define C 3

uint32_t minConsecPathLen(const char mat[R][C], char s) {
  // dp[i][j] stores length of longest consecutive path starting at arr[i][j].
  uint32_t dp[R][C];
  for (auto& i : dp)
    for (auto& j : i)
      j = -1;

  function<bool(const uint32_t,const uint32_t)> isvalid =
    [&](const uint32_t i, const uint32_t j) {
    return !(i < 0 || j < 0 || i >= R || j >= C);
  };

  function<bool(const char,const char)> isadjacent =
    [&](const char prev, const char curr) {
    return ((curr - prev) == 1);
  };

  static const pair<int8_t,int8_t> dirs[8] =
    {{0,1},{1,0},{1,1},{-1,1},{1,-1},{0,-1},{-1,0},{-1,-1}};

  function<uint32_t(const uint32_t,const uint32_t,const char)> solve =
    [&](const uint32_t i, const uint32_t j, const char prev) -> uint32_t {
    // If this cell is not valid or current character is not
    // adjacent to previous one (e.g. d is not adjacent to b )
    // or if this cell is already included in the path than return 0.
    if (!isvalid(i, j) || !isadjacent(prev, mat[i][j]))
      return 0;

    // If this subproblem is already solved, return the answer
    if (dp[i][j] != -1)
      return (uint32_t)dp[i][j];

    uint32_t ret = 0;
    // recur for paths with differnt adjacent cells and store the length of longest path.
    for (uint8_t k = 0; k < 8; ++k)
      ret = max(ret, 1+solve(i+dirs[k].first, j+dirs[k].second, mat[i][j]));

    dp[i][j] = ret;
    return ret;
  };

  uint32_t ret = 0;
  for (uint32_t i = 0; i < R; ++i) {
    for (uint32_t j = 0; j < C; ++j) {
      // check for each possible starting point
      if (mat[i][j] == s) {
        // recur for all eight adjacent cells
        for (uint8_t k = 0; k < 8; ++k)
          ret = max(ret, 1+solve(i+dirs[k].first, j+dirs[k].second, s));
      }
    }
  }

  return ret;
}

/*
Given a matrix where every cell represents points. How to collect maximum points using two traversals
under following conditions?

Let the dimensions of given grid be RxC.
1) The first traversal starts from top left corner, i.e., (0, 0) and should reach left bottom corner, i.e., (R-1, 0).
The second traversal starts from top right corner, i.e., (0, C-1) and should reach bottom right corner, i.e., (R-1, C-1)/
2) From a point (i, j), we can move to (i+1, j+1) or (i+1, j+1) or (i+1, j)
3) A traversal gets all points of a particular cell through which it passes. If one traversal has already collected
points of a cell, then the other traversal gets no points if goes through that cell again.
 */
#define R 5
#define C 4

struct Direction {
  int8_t x, y1, y2;
};

/*
The idea is to do both traversals concurrently. We start first from (0, 0) and second traversal from (0, C-1) simultaneously.
At any particular step both traversals will be in same row as in all possible three moves, row number is increased.
Let (x1, y1) and (x2, y2) denote current positions of first and second traversals respectively.
Thus at any time x1 will be equal to x2 as both of them move forward but variation is possible along y.
Since variation in y could occur in 3 ways no change (y), go left (y-1), go right (y+1).
So in total 9 combinations among y1,y2 are possible.
 */
uint32_t maxCollection(const uint32_t a[R][C]) {
  int32_t mem[R][C][C];
  for (auto& i : mem)
    for (auto& j : i)
      for (auto& k : j)
        k = -1;

  static const vector<Direction> dirs = {{1,0,-1},{1,0,1},{1,0,0},
                                         {1,-1,0},{1,-1,-1},{1,-1,1},
                                         {1,1,0},{1,1,-1},{1,1,1}};

  function<bool(const uint32_t,const uint32_t,const uint32_t)> isValid =
    [&](const uint32_t x, const uint32_t y1, const uint32_t y2) {
    return (x >= 0 && x < R && y1 >=0 && y1 < C && y2 >=0 && y2 < C);
  };

  function<int32_t(const uint32_t,const uint32_t,const uint32_t)> solve =
    [&](const uint32_t x, const uint32_t y1, const uint32_t y2) {
    // if P1 or P2 is at an invalid cell
    if (!isValid(x, y1, y2))
      return MIN_LMT;

    // if both traversals reach their destinations
    if (x == R-1 && y1 == 0 && y2 == C-1)
      return (int32_t)(a[x][y1]+a[x][y2]);
    // If both traversals are at last row but not at their destination
    if (x == R-1)
      return MIN_LMT;
    // If subproblem is already solved
    if (mem[x][y1][y2] != -1)
      return mem[x][y1][y2];

    // Initialize answer for this subproblem
    int32_t ret = MIN_LMT;
    // this variable is used to store gain of current cell(s)
    int32_t tmp = (y1 == y2) ? a[x][y1] : a[x][y1]+a[x][y2];
    /* Recur for all possible cases, then store and return the one with max value */
    for (uint8_t i = 0; i < dirs.size(); ++i)
      ret = max(ret, tmp+solve(x+dirs[i].x, y1+dirs[i].y1, y2+dirs[i].y2));

    mem[x][y1][y2] = ret;
    return ret;
  };

  return solve(0, 0, C-1);
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

  char path[] = "GLGLGLG";
  if (areCircularMoves(path))
    cout << "Given sequence of moves is circular!" << endl;
  else
    cout << "Given sequence of moves is NOT circular!" << endl;

  char matt[R][C] = {{'a','c','d'},
                     {'h','b','a'},
                     {'i','g','f'}};

  cout << minConsecPathLen(matt, 'a') << endl;
  cout << minConsecPathLen(matt, 'e') << endl;
  cout << minConsecPathLen(matt, 'b') << endl;
  cout << minConsecPathLen(matt, 'f') << endl;

  uint32_t a[R][C] = {{3, 6, 8, 2},
                      {5, 2, 4, 3},
                      {1, 1, 20, 10},
                      {1, 1, 20, 10},
                      {1, 1, 20, 10}};

  cout << "Maximum collection is " << maxCollection(a) << endl;
  return 0;
}
