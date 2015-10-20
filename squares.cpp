/*
Given a set of N points in the plane, how many squares are there such that all their corners belong to this set?

Input
The first line contains t, the number of test cases (about 10). Then t test cases follow.
Each test case has the following form:
The first line contains an integer N, the number of points in the given set (4 <= N <= 500).
Then N lines follow, each line contains two integers X, Y describing coordinates of a point (-50 <= X, Y <= 50).
Output

For each test case, print in a single line the number of squares that have vertices belong to the given set.

Input:
1
7
0 0
0 1
1 0
1 1
1 2
2 1
2 2

Output:
3

Output details:
The three squares are:
(0 0), (0 1), (1 1), (1 0)
(1 1), (1 2), (2 2), (2 1)
(0 1), (1 0), (2 1), (1 2)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(int argc, char** argv) {
  uint32_t N = 0;
  scanf("%d",&N);

  uint32_t x[501],y[501];
  uint32_t grid[101][101];


  uint32_t top = 0;

  for (uint8_t i = 0; i < 101; ++i) {
    for(uint8_t j = 0; j < 101; ++j)
      grid[i][j]=0;
  }

  for (uint32_t i = 0; i < N; ++i) {
    scanf("%d %d", &x[top], &y[top]);
    grid[50+x[top]][50+y[top]] = 1;
    ++top;
  }

  for (uint8_t i = 0; i < top; ++i) {
    for (uint8_t j = 0; j < top-i-1; ++j) {
      if (x[j] > x[j+1] || (x[j] == x[j+1] && y[j] > y[j+1])) {
        uint32_t temp = x[j];
        x[j] = x[j+1];
        x[j+1] = temp;
        temp = y[j];
        y[j] = y[j+1];
        y[j+1]=temp;
      }
    }
  }

  for (uint8_t i = 0; i < top; ++i) {
    for (uint8_t j = i+1; j < top; ++j) {
      if (!grid[50+x[i]][50+y[i]])
        continue;

      int32_t perp = y[j]-y[i];
      int32_t base = x[j]-x[i];
      int32_t newx = x[i] + perp;
      int32_t newy = y[i]-base;

      if (newx < -50 || newy < -50 || newx > 50 || newy > 50)
        continue;

      if (grid[50+newx][50+newy]) {
        newx = x[i]+base+perp;
        newy = y[i]+perp-base;
        if (newx < -50 || newy < -50 || newx > 50 || newy > 50)
          continue;

        if (grid[50+newx][50+newy]) {
          ++res;
        }
      }
    }

    grid[50+x[i]][50+y[i]] = 0;
  }

  return 0;
}
/*
int main(int argc, char** argv) {
  uint32_t N = 0;
  scanf("%d", &N);

  vector<vector<uint32_t>> points(101, vector<uint32_t>(101, 0));
  vector<pair<uint32_t,uint32_t>> square;

  for (uint32_t i = 0; i < N; ++i) {
    int32_t x, y;
    scanf("%d %d", &x, &y);
    ++points[y+50][x+50];
    square.push_back(make_pair(y+50, x+50));
  }

  const uint32_t n = square.size();

  function<uint32_t()> numOfSquares = [&]() {
    sort(square.begin(), square.end());

    uint32_t res = 0;

    for (uint32_t i = 0; i < n; ++i) {
      for (uint32_t j = i+1; j < n; ++j) {
        if (square[j].second > square[i].second) {
          uint32_t x  = square[i].second;
          uint32_t y  = square[i].first;
          uint32_t dx = square[j].second-x;
          int32_t dy  = square[j].first-y;

          if (x-dy >= 0 && y+dx+dy < 101 && points[y+dx][x-dy] && points[y+dx+dy][x-dy+dx])
            ++res;
        }
      }
    }

    return res;
  };

  cout << "Number of squares: " << numOfSquares() << endl;

  return 0;
} */
