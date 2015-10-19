/*
Given a matrix where every row is sorted in increasing order. Write a function that finds and returns a common element
in all rows. If there is no common element, then returns -1.
 */
#include <iostream>
#include <vector>

using namespace std;

/*
O(m*n) approach: start from the last column of every row. If elements at all last columns are same, then we found
the common element. Otherwise we find the minimum of all last columns. Once we find a minimum element, we know that
all other elements in last columns cannot be a common element, so we reduce last column index for all rows except for
the row which has minimum value. We keep repeating these steps till either all elements at current last column don't
become same, or a last column index reaches 0.
 */
int32_t commonElement(const vector<vector<uint32_t>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return -1;

  vecotr<uint32_t> column(m, n-1); // store indexes of current last column
  uint32_t min_row = 0; // store index of row whose current last element is minimum

  // Keep finding min_row in current last column, till either all elements of last column become same or we hit first column.
  while (column[min_row] >= 0) {
    for (uint32_t i = 0; i < m; ++i)
      if (mat[i][column[i]] < mat[min_row][column[min_row]])
        min_row = i;

    // eq_count is count of elements equal to minimum in current last column.
    uint32_t eq_count = 0;

    // Traverse current last column elements again to update it
    for (uint32_t i = 0; i < m; ++i) {
      // Decrease last column index of a row whose value is more than minimum.
      if (mat[i][column[i]] > mat[min_row][column[min_row]]) {
        if (!column[i])
          return -1;
        --column[i];
      } else
        ++eq_count;
    }

    // If equal count becomes m, return the value
    if (eq_count == m)
      return mat[min_row][column[min_row]];
  }

  return -1;
}

int main(int argc, char** argv) {
  vector<vector<uint32_t>> mat =
  {{1, 2, 3, 4, 5},
   {2, 4, 5, 8, 10},
   {3, 5, 7, 9, 11},
   {1, 3, 5, 7, 9}};

  int32_t res = commonElement(mat);
  if (res == -1)
    cout << "No common element!" << endl;
  else
    cout << "Common element is " << res << endl;

  return 0;
}
