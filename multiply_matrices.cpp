/**
Given a sequence of matrices, find the most efficient way to multiply these matrices together. The problem is not actually to perform the multiplications, but merely to decide in which order to perform the multiplications.

We have many options to multiply a chain of matrices because matrix multiplication is associative. In other words, no matter how we parenthesize the product, the result will be the same. For example, if we had four matrices A, B, C, and D, we would have:

    (ABC)D = (AB)(CD) = A(BCD) = ....
However, the order in which we parenthesize the product affects the number of simple arithmetic operations needed to compute the product, or the efficiency. For example, suppose A is a 10 × 30 matrix, B is a 30 × 5 matrix, and C is a 5 × 60 matrix. Then,

    (AB)C = (10×30×5) + (10×5×60) = 1500 + 3000 = 4500 operations
    A(BC) = (30×5×60) + (10×30×60) = 9000 + 18000 = 27000 operations.
Clearly the first parenthesization requires less number of operations.
 */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

static const uint32_t max_lmt = numeric_limits<int32_t>::max();

// Matrix Ai has dimension p[i-1] x p[i] for i = 1...n
uint32_t matrixChainOrder(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  // One extra row and one extra column, 0th row and 0th column of dp[][] are not used...
  vector<vector<int32_t>> dp(n, vector<int32_t>(n, 0));

  // dp[i,j] = Minimum number of scalar multiplications needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where dimention of A[i] is p[i-1] x p[i]

  // L is chain length.
  for (uint32_t L = 2; L < n; ++L) {
    for (uint32_t i = 1; i <= n-L+1; ++i) {
      uint32_t j = i+L-1;
      dp[i][j] = max_lmt;
      for (uint32_t k = i; k <= j-1; ++k) {
        // q = cost/scalar multiplications
        const int32_t q = dp[i][k] + dp[k+1][j] + nums[i-1]*nums[k]*nums[j];
        if (q < dp[i][j])
          dp[i][j] = q;
      }
    }
  }

  return dp[1][n-1];
}

int main(int argc, char** argv) {
  vector<int32_t> nums = {1, 2, 3, 4};
  cout << "Minimum number of multiplications is " << matrixChainOrder(nums) << endl;
  return 0;
}
