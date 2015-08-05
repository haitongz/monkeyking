/*
Given a binary matrix, find out the maximum size square sub-matrix with all 1s.
For example, consider the below binary matrix.
   0  1  1  0  1
   1  1  0  1  0
   0  1  1  1  0
   1  1  1  1  0
   1  1  1  1  1
   0  0  0  0  0
The maximum square sub-matrix with all set bits is
    1  1  1
    1  1  1
    1  1  1
 */
#include <iostream>

using namespace std;

#define R 6
#define C 5

void maxAllSetSubsquare(bool M[R][C]) {
  uint32_t dp[R][C];

  for (uint32_t i = 0; i < R; ++i) // first column
    dp[i][0] = M[i][0];
  for (uint32_t i = 0; i < C; ++i) // first row
    dp[0][i] = M[0][i];

  uint32_t max_len = 0, max_i = 0, max_j = 0;
  for (uint32_t i = 1; i < R; ++i) {
    for (uint32_t j = 1; j < C; ++j) {
      if (M[i][j]) {
        dp[i][j] = min(dp[i][j-1], min(dp[i-1][j], dp[i-1][j-1])) + 1;
        if (max_len < dp[i][j]) {
          max_len = dp[i][j];
          max_i = i;
          max_j = j;
        }
      } else {
        dp[i][j] = 0; // need to start over
      }
    }
  }

  cout << "Max all-set subsquare ends at [" << max_i << "," << max_j << "], with length " << max_len << endl;
  for (uint32_t i = max_i; i > max_i-max_len; --i) {
    for (uint32_t j = max_j; j > max_j-max_len; --j) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char** argv) {
  bool M[R][C] = {{0, 1, 1, 0, 1},
                  {1, 1, 0, 1, 0},
                  {0, 1, 1, 1, 0},
                  {1, 1, 1, 1, 0},
                  {1, 1, 1, 1, 1},
                  {0, 0, 0, 0, 0}};

  maxAllSetSubsquare(M);
  return 0;
}
