/*
N cows (1 <= N <= 20) each has some height of Hi (1 <= Hi <= 1,000,000 - there are very tall cows). The bookshelf has a
height of B (1 <= B <= S, where S is the sum of the heights of all cows).
To reach the top of the bookshelf, one or more of the cows can stand on top of each other in a stack, so that their total
height is the sum of each of their individual heights. This total height must be no less than the height of the bookshelf
in order for the cows to reach the top.
Since a taller stack of cows than necessary can be dangerous, your job is to find the set of cows that produces a stack of
the smallest height possible such that the stack can reach the bookshelf. Your program should print the minimal 'excess'
height between the optimal stack of cows and the bookshelf.
Input
* Line 1: Two space-separated integers: N and B
* Lines 2..N+1: Line i+1 contains a single integer: Hi
Output
* Line 1: A single integer representing the (non-negative) difference between the total height of the optimal set of cows
and the height of the shelf.
Sample Input
5 16
3
1
3
5
6
Sample Output
1
 */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

static const uint8_t MAX_COW = 21;
static const uint32_t MAX_HEIGHT = 1000000;
static const uint32_t max_lmt = numeric_limits<uint32_t>::max();
uint32_t heights[MAX_COW];
bool flags[MAX_COW*MAX_HEIGHT];

uint32_t dfs(const uint32_t N, const uint32_t B, const uint32_t S) {
  fill(flags, flags+S+1, false);
  flags[0] = true;

  for (uint32_t i = 0; i < N; ++i) {
    for (uint32_t j = S; j >= heights[i]; --j) {
      if (flags[j-heights[i]])
        flags[j] = true;
    }
  }

  uint32_t res = B;
  for (; res <= S && !flags[res]; ++res) {
  }

  return res;
}

uint32_t bfs(const uint32_t N, const uint32_t B) { // needs more memory but runs faster
  vector<uint32_t> stk = {0}; // add 0 to include every single height
  uint32_t res = max_lmt;

  for (uint8_t i = 0; i < N; ++i) {
    for (int32_t j = stk.size()-1; j >= 0; --j) { // stk.size() changes
      uint32_t new_h = stk[j]+heights[i];
      if (new_h == B)
        return 0;

      stk.push_back(new_h); // records all sum combinations, 0, 0+heights[0], heights[0]+heights[1], 0+heights[1]...
      if (new_h > B)
        res = min(res, new_h-B);
    }
  }

  return res;
}

int main(int argc, char** argv) {
  uint32_t N, B, S;

  while (~scanf("%d %d", &N, &B) != EOF) {
    S = 0;
    for (uint32_t i = 0; i < N; ++i) {
      scanf("%d", heights+i);
      S += heights[i];
    }
    cout << "DFS: " << (dfs(N, B, S)-B) << endl;
    cout << "BFS: " << bfs(N, B) << endl;
  }

  return 0;
}
