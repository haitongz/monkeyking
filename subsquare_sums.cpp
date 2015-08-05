/*
Given an nxn square matrix, find sum of all sub-squares of size k x k where k is smaller than or equal to n

Simple solution is to calculate all subsquares, O(k^2n^2).
O(n2) solution: preprocess the given square matrix, calculate sum of all vertical strips of size kx1 in a temporary square matrix stripSum[][]. Once we have sum of all vertical strips, we can calculate sum of first sub-square in a row as sum of first k strips in that row, and for remaining sub-squares, we can calculate sum in O(1) time by removing the leftmost strip of previous subsquare and adding the rightmost strip of new square.
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int32_t> subsquareSums(const vector<vector<int32_t>>& mat, const uint32_t k) {
  const uint32_t n = mat.size();
  if (!n || k > n)
    return {};

  int32_t stripsum[n][n];
  for (uint32_t j = 0; j < n; ++j) {
    int32_t sum = 0;
    for (uint32_t i = 0; i < k; ++i)
      sum += mat[i][j];

    stripsum[0][j] = sum;

    // Calculate sum of remaining rectangles
    for (uint32_t i = 1; i < n-k+1; ++i) {
      sum += (mat[i+k-1][j] - mat[i-1][j]);
      stripsum[i][j] = sum;
    }
  }

  vector<int32_t> ret;
  for (uint32_t i = 0; i < n-k+1; ++i) {
    // Calculate and print sum of first subsquare in this row
    int32_t sum = 0;
    for (uint32_t j = 0; j < k; ++j)
      sum += stripsum[i][j];

    ret.push_back(sum);

    // Calculate sum of remaining squares in current row by removing the leftmost strip of previous sub-square and adding a new strip
    for (uint32_t j = 1; j < n-k+1; ++j) {
      sum += (stripsum[i][j+k-1] - stripsum[i][j-1]);
      ret.push_back(sum);
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<vector<int32_t>> mat =
    {{1, 1, 1, 1, 1},
     {2, 2, 2, 2, 2},
     {3, 3, 3, 3, 3},
     {4, 4, 4, 4, 4},
     {5, 5, 5, 5, 5}};

  uint32_t k = 3;

  vector<int32_t> res = subsquareSums(mat, k);
  for (const auto i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
