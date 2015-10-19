#include <iostream>
#include <vector>

using namespace std;

/*
Given a 2D matrix, print all elements of the given matrix in diagonal order.
Input:
    1     2     3     4
    5     6     7     8
    9    10    11    12
   13    14    15    16
   17    18    19    20

Output:
    1
    5     2
    9     6     3
   13    10     7     4
   17    14    11     8
   18    15    12
   19    16
   20
 */
vector<vector<int32_t>> diagonalOrder(const vector<vector<int32_t>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return {};

  vector<vector<int32_t>> ret;

  // There will be m+n-1 lines in the output
  for (uint32_t i = 1; i < (m+n); ++i) {
    /* Get column index of the first element in this line of output. The index is 0 for first ROW lines and line -
    ROW for remaining lines
     */
    uint32_t s_col = max(0, i-m);

    /* Get count of elements in this line. The count of elements is equal to minimum of line number, COL-start_col and ROW */
    uint32_t count = min(i, (n-s_col), m);

    /* Print elements of this line */
    for (uint32_t j = 0; j < count; ++j)
      ret.push_back(mat[min(m, i)-j-1][s_col+j]);
  }

  return ret;
}

/*
Given an M x N matrix, transpose the matrix without auxiliary memory. It is easy to transpose matrix using an auxiliary array.
If the matrix is symmetric in size, we can transpose the matrix inplace by mirroring the 2D array across its diagonal.
How to transpose an arbitrary size matrix inplace?
 */
void inplaceTranspose(vector<vector<int32_t>>& A) {
  const uint32_t r = A.size(), c = A[0].size();
  uint32_t size = r*c-1;
  int32_t t; // holds element to be replaced, eventually becomes next element to move
  int32_t next; // location of 't' to be moved
  int32_t cycleBegin; // holds start of cycle
  uint32_t i; // iterator
  bitset<128/*HASH_SIZE*/> b; // hash to mark moved elements
  b.reset();
  b[0] = b[size] = 1;

  i = 1; // Note that A[0] and A[size-1] won't move
  while (i < size) {
    cycleBegin = i;
    t = A[i];

    do {
            // Input matrix [r x c]
            // Output matrix 1
            // i_new = (i*r)%(N-1)

      next = (i*r)%size;
      swap(A[next], t);
      b[i] = 1;
      i = next;
    } while (i != cycleBegin);

    // Get Next Move (what about querying random location?)
    for (i = 1; i < size && b[i]; ++i)
      ;
 //   cout << endl;
  }
}
