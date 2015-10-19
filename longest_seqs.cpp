#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

/*
The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of
a given sequence such that all elements of the subsequence are sorted in increasing order.
1. Elements don't need to be contiguous;
2. No need to keep spaces in between, just length of the subsequence.

For example, length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.
 */
uint32_t LISLen(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  vector<uint32_t> dp(n, 1); // initialize to 1, as each number is a sequence
  uint32_t res = 1;

  for (uint32_t i = 1; i < n; ++i) {
    for (uint32_t j = 0; j < i; ++j) {
      if (nums[i] > nums[j]) {
        dp[i] = max(dp[i], dp[j]+1);
      }

      res = max(res, dp[i]);
    }
  }

  return res;
}

/*
A snake sequence is made up of adjacent numbers such that for each number,
the number on the right or the number below it is +1 or -1 its value.

Given
1 3 2 6 8
-9 7 1 -1 2
1 5 0 1 9

In this grid, (3, 2, 1, 0, 1) is a snake sequence.

Given a grid, find the longest snake sequences and their lengths
(so there can be multiple snake sequences with the maximum length).
 */
uint32_t longestSnakeSeqLen(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (m < 2 || n < 2)
    return 0;

  uint32_t res = 0;
  vector<vector<uint32_t>> dp(m, vector<uint32_t>(n, 1));

  for (int32_t i = m-2; i >= 0; --i) { // right most column, can't move right
    if (abs(mat[i][n-1]-mat[i+1][n-1]) == 1) {
      dp[i][n-1] = dp[i+1][n-1]+1;
      res = max(dp[i][n-1], res);
    }
  }
  for (int32_t j = n-2; j >= 0; --j) { // bottom row, can't move down
    if (abs(mat[m-1][j]-mat[m-1][j+1]) == 1) {
      dp[m-1][j] = dp[m-1][j+1]+1;
      res = max(dp[m-1][j], res);
    }
  }
  for (int32_t i = m-2; i >= 0; --i) { // now move
    for (int32_t j = n-2; j >= 0; --j) {
      if (abs(mat[i][j]-mat[i][j+1]) == 1) {
        dp[i][j] = dp[i][j+1]+1;
      }
      if (abs(mat[i][j]-mat[i+1][j]) == 1) {
        dp[i][j] = max(dp[i][j], dp[i+1][j]+1);
      }

      res = max(dp[i][j], res);
    }
  }

  return res;
}

/*
Find the longest increasing(increasing means one step) sequence in an integer matrix in 4 directions (up down left right),
return the sequence

Given
[
 1 2 3 4
 8 7 6 5
]

The output should be [1, 2, 3, 4, 5, 6, 7, 8]
 */
vector<int32_t> matrixLIS(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return {};

  static const vector<pair<int8_t,int8_t>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
  vector<vector<int32_t>> dp(m, vector<int32_t>(n, 0));

  function<int32_t(const int32_t,const int32_t)> dfs =
    [&](const int32_t i, const int32_t j) {
    if (dp[i][j] != 0)
      return dp[i][j];

    for (auto& d : dirs) {
      int32_t newi = i+d.first, newj = j+d.second;
      if (newi < 0 || newj < 0 || newi >= m || newj >= n)
        continue;

      if (mat[newi][newj] == mat[i][j]+1)
        dp[i][j] = max(dp[i][j], dfs(newi, newj));
    }

    return ++dp[i][j];
  };

  int32_t max_start = 0, max_path = 0;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      int32_t path = dfs(i, j);
      if (path > max_path) {
        max_start = mat[i][j];
        max_path = path;
      }
    }
  }

  vector<int32_t> res(max_path);
  //iota(res.begin(), res.end(), max_start);
  return res;
}

/*
Given an array arr[0 ... n-1] containing n positive integers, a subsequence of arr[] is called Bitonic if it is first increasing, then decreasing. Write a function that takes an array as argument and returns the length of the longest bitonic subsequence.
A sequence, sorted in increasing order is considered Bitonic with the decreasing part as empty. Similarly, decreasing order sequence is considered Bitonic with the increasing part as empty.

Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)

Input arr[] = {12, 11, 40, 5, 3, 1}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)

Input arr[] = {80, 60, 30, 40, 20, 10}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)
 */
uint32_t longestBitonicSubseqLen(const vector<uint32_t>& nums) {
  const uint32_t n = nums.size();
  if (n < 3)
    return 0;

  vector<uint32_t> t1(n, 1), t2(n, 1);
  for (int32_t i = 0, k = n-1; i < n && k >= 0; ++i, --k) {
    for (int32_t j = i+1, l = k-1; j < n && l >= 0; ++j, --l) {
      if (nums[j] > nums[i])
        t1[j] = t1[i]+1;
      if (nums[l] > nums[k])
        t2[l] = t2[k]+1;
    }
    if (i > 1)
      t1[i] = max(t1[i], t1[i-1]);
    if (k < n-1)
      t2[k] = max(t2[k], t2[k+1]);
  }

  uint32_t len = 0;
  for (uint32_t i = 1; i < n; ++i) {
    len = max(t1[i-1]+t2[i], len);
  }

  return len;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {10, 22, 9, 33, 21, 50, 41, 60, 80};
  cout << "LIS length: " << LISLen(a) << endl;

  vector<vector<int32_t>> mat = {{1, 3, 2, 6, 8},
                                 {-9, 7, 1, -1, 2},
                                 {1, 5, 0, 1, 9}};
  cout << "Longest snake sequence length: " << longestSnakeSeqLen(mat) << endl;

  mat = {{1,8}, {2,7}, {3,6}, {4,5}};
  vector<int32_t> res = matrixLIS(mat);

  cout << "Longest increasing sequence: ";
  for (auto i : res)
    cout << i << " ";
  cout << endl;

  vector<uint32_t> b = {1, 11, 2, 10, 4, 5, 2, 1};
  cout << "Longest bitonic subsequence length is: " << longestBitonicSubseqLen(b) << endl;
  b = {12, 11, 40, 5, 3, 1};
  cout << "Longest bitonic subsequence length is: " << longestBitonicSubseqLen(b) << endl;
  b = {80, 60, 30, 40, 20, 10};
  cout << "Longest bitonic subsequence length is: " << longestBitonicSubseqLen(b) << endl;

  return 0;
}
