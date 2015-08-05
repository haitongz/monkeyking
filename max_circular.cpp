/*
Given n numbers (both +ve and -ve), arranged in a circle, fnd the maximum sum of consecutive number.
 */
// Standard Kadane's algorithm to find maximum subarray sum
// See http://www.geeksforgeeks.org/archives/576 for details
int32_t kadane(const int32_t a[], const uint32_t n) {
  int32_t max_so_far = 0, max_ending_here = 0;

  for (uint32_t i = 0; i < n; ++i) {
    max_ending_here += a[i];
    if (max_ending_here < 0)
      max_ending_here = 0;
    max_so_far = max(max_so_far, max_ending_here);
  }

  return max_so_far;
}

int32_t maxCircularSum(const int32_t a[], const uint32_t n) {
  // Case 1: get the maximum sum using standard kadane's algorithm
  int32_t max_kadane = kadane(a, n);

  // Case 2: Now find the maximum sum that includes corner elements.
  int32_t max_wrap = 0;
  for (uint32_t i = 0; i < n; ++i) {
    max_wrap += a[i]; // Calculate array-sum
    a[i] = -a[i];  // invert the array (change sign)
  }

  // max sum with corner elements will be: array-sum - (-max subarray sum of inverted array)
  max_wrap += kadane(a, n);

  // The maximum circular sum will be maximum of two sums
  return (max_wrap > max_kadane) ? max_wrap : max_kadane;
}
