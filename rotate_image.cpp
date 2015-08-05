/*
You are given an nxn 2D matrix representing an image. Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?
 */
#include <iostream>
#include <vector>

using namespace std;

/*
void rotate(uint32_t* pS, uint32_t* pD, uint32_t row, uint32_t col) { // not in-place
  for (uint32_t r = 0; r < row; ++r) {
    for (uint32_t c = 0; c < col; ++c) {
      *(pD+c*row+(row-r-1)) = *(pS+r*col+c);
    }
  }
}
 */
void inplaceRotate(vector<vector<int32_t>>& mat) {
  const uint32_t n = mat.size();
  if (n <= 1)
    return;

  for (uint32_t r = 0; r < n/2; ++r) {
    int32_t nums = n-1-2*r;

    for (uint32_t i = 0; i < nums; ++i) {
      const int32_t t = mat[r][r+i];
      mat[r][r+i] = mat[n-r-1-i][r];
      mat[n-r-1-i][r] = mat[n-r-1][n-r-1-i];
      mat[n-r-1][n-r-1-i] = mat[r+i][n-r-1];
      mat[r+i][n-r-1] = t;
    }
  }
}

void inplaceRotate2(vector<vector<int32_t>>& mat) {
  const uint32_t n = mat.size();
  if (n <= 1)
    return;

  for (int32_t i = 0, j = n-1; i < j; ++i, --j) {
    for (int32_t k = i, l = j; k < j; ++k, --l) {
      const int32_t t = mat[i][k];
      mat[i][k] = mat[l][i];
      mat[l][i] = mat[j][l];
      mat[j][l] = mat[k][j];
      mat[k][j] = t;
    }
  }
}

int main(int argc, char** argv) {
  vector<vector<int32_t>> mat = {{1,2,3},
                                 {4,5,6},
                                 {7,8,9}};
  rotateInplace2(mat);
  for (auto i : mat) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
