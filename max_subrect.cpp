/*
Given a 2D array, find the maximum sum subarray in it.

Given a matrix:
 1, 2,-1,-4,-20
-8,-3, 4, 2, 1
 3, 8,10, 1, 3
-4,-1, 1, 7,-6

The result is 29.
 */
#include <iostream>
#include <vector>

using namespace std;

int32_t maxSubrect(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return 0;

  vector<vector<int32_t>> col_sums(mat);

  for (uint32_t i = 1; i < m; ++i)
    for (uint32_t j = 0; j < n; ++j)
      col_sums[i][j] += col_sums[i-1][j];

  int32_t ret = 0;

  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < i+1; ++j) {
      int32_t min_left = 0;
      int32_t row_sums[n];

      for (uint32_t k = 0; k < n; ++k) {
        int32_t col_sum = !j ? col_sums[i][k] : (col_sums[i][k]-col_sums[j-1][k]);
        row_sums[k] = !k ? col_sum : (col_sum+row_sums[k-1]);
        ret = max(ret, row_sums[k]-min_left);
        min_left = min(min_left, row_sums[k]);
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<vector<int32_t>> mat =
    {{1,2,-1,-4,-20},
     {-8,-3,4,2,1},
     {3,8,10,1,3},
     {-4,-1,1,7,-6}};
  cout << maxSubrect(mat) << endl;

  return 0;
}
