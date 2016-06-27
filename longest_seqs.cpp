#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

/*
The Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of
a given sequence such that all elements of the subsequence are sorted in increasing order.
1. Elements don't need to be contiguous;
2. No need to keep spaces in between, just length of the subsequence.

For example, length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.
 */
uint LISLen(const int a[], const uint n) {
  if (!n)
    return 0;

  vector<uint> dp(n, 1); // initialize to 1, as each number is a sequence
  uint ret = 1;

  for (uint i = 1; i < n; ++i) {
    for (uint j = 0; j < i; ++j) {
      if (a[i] > a[j]) {
        dp[i] = max(dp[i], dp[j]+1);
      }

      ret = max(ret, dp[i]);
    }
  }

  return ret;
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
uint longestSnakeSeqLen(const vector<vector<int>>& mat) {
  const uint m = mat.size();
  const uint n = mat[0].size();
  if (m < 2 || n < 2)
    return 0;

  uint ret = 0;
  vector<vector<uint>> dp(m, vector<uint>(n, 1));

  for (int i = m-2; i >= 0; --i) { // right most column, can't move right
    if (abs(mat[i][n-1]-mat[i+1][n-1]) == 1) {
      dp[i][n-1] = dp[i+1][n-1]+1;
      ret = max(dp[i][n-1], ret);
    }
  }
  for (int j = n-2; j >= 0; --j) { // bottom row, can't move down
    if (abs(mat[m-1][j]-mat[m-1][j+1]) == 1) {
      dp[m-1][j] = dp[m-1][j+1]+1;
      ret = max(dp[m-1][j], ret);
    }
  }
  for (int i = m-2; i >= 0; --i) { // now move
    for (int j = n-2; j >= 0; --j) {
      if (abs(mat[i][j]-mat[i][j+1]) == 1) {
        dp[i][j] = dp[i][j+1]+1;
      }
      if (abs(mat[i][j]-mat[i+1][j]) == 1) {
        dp[i][j] = max(dp[i][j], dp[i+1][j]+1);
      }

      ret = max(dp[i][j], ret);
    }
  }

  return ret;
}

/*
Find the longest increasing (increasing means one step) sequence
in an integer matrix in 4 directions (up down left right), return the sequence

Given
[
 1 2 3 4
 8 7 6 5
]

The output should be [1, 2, 3, 4, 5, 6, 7, 8]

vector<int> matrixLIS(const vector<vector<int>>& mat) {
  const uint m = mat.size();
  const uint n = mat[0].size();
  if (!m || !n)
    return {};

  static const vector<pair<int,int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
  vector<vector<int>> dp(m, vector<int>(n, 0));

  function<int(const uint,const uint)> solve = // DFS
    [&](const uint i, const uint j) {
    if (dp[i][j] != 0)
      return dp[i][j];

    for (const auto& d : dirs) {
      int newi = i+d.first, newj = j+d.second;
      if (newi < 0 || newj < 0 || newi >= m || newj >= n)
        continue;

      if (mat[newi][newj] == mat[i][j]+1)
        dp[i][j] = max(dp[i][j], solve(newi, newj));
    }

    return ++dp[i][j];
  };

  int max_start = 0, max_path = 0;
  for (uint i = 0; i < m; ++i) {
    for (uint j = 0; j < n; ++j) {
      int path = solve(i, j);
      if (path > max_path) {
        max_start = mat[i][j];
        max_path = path;
      }
    }
  }

  vector<int> ret(max_path);
  iota(ret.begin(), ret.end(), max_start);
  return ret;
}
 */

/*
Given an array a[0 ... n-1] containing n positive integers,
a subsequence of a[] is called Bitonic if it is first increasing, then decreasing.
Write a function that takes an array as argument and returns the length of the longest bitonic subsequence.
A sequence, sorted in increasing order is considered Bitonic with the decreasing part as empty.
Similarly, decreasing order sequence is considered Bitonic with the increasing part as empty.

Input a[] = {1, 11, 2, 10, 4, 5, 2, 1};
Output: 6 (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)

Input a[] = {12, 11, 40, 5, 3, 1}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)

Input a[] = {80, 60, 30, 40, 20, 10}
Output: 5 (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)
 */
uint longestBitonicSubseqLen(const uint a[], const uint n) {
  if (n < 3)
    return 0;

  vector<uint> t1(n, 1), t2(n, 1);
  for (int i = 0, k = n-1; i < n && k >= 0; ++i, --k) {
    for (int j = i+1, l = k-1; j < n && l >= 0; ++j, --l) {
      if (a[j] > a[i])
        t1[j] = t1[i]+1;
      if (a[l] > a[k])
        t2[l] = t2[k]+1;
    }
    if (i > 1)
      t1[i] = max(t1[i], t1[i-1]);
    if (k < n-1)
      t2[k] = max(t2[k], t2[k+1]);
  }

  uint len = 0;
  for (uint i = 1; i < n; ++i) {
    len = max(t1[i-1]+t2[i], len);
  }

  return len;
}

int main(int argc, char** argv) {
  int a[9] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
  cout << "LIS length: " << LISLen(a, 9) << endl;

  vector<vector<int>> mat = {{1, 3, 2, 6, 8},
                                 {-9, 7, 1, -1, 2},
                                 {1, 5, 0, 1, 9}};
  cout << "Longest snake sequence length: " << longestSnakeSeqLen(mat) << endl;

 /* mat = {{1,8}, {2,7}, {3,6}, {4,5}};
    vector<int> res = matrixLIS(mat);

  cout << "Longest increasing sequence: ";
  for (const auto i : res)
    cout << i << " ";
  cout << endl;
 */
  uint b[8] = {1, 11, 2, 10, 4, 5, 2, 1};
  cout << "Longest bitonic subsequence length is: " << longestBitonicSubseqLen(b, 8) << endl;

  return 0;
}
