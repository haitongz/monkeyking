/*
Given an array of size n, the array contains numbers in range from 0 to k-1 where k is a positive integer and k <= n. Find the maximum repeating number in this array.

For example, let k be 10 the given array be a[] = {1, 2, 2, 2, 0, 2, 0, 2, 3, 8, 0, 9, 2, 3}, the maximum repeating number would be 2.

Expected time complexity is O(n) and extra space allowed is O(1). Modifications to array are allowed.
 */
#include <iostream>

/*
A better approach is to create a count array of size k and initialize all elements of count[] as 0. Iterate through all elements of input array, and for every element a[i], increment count[a[i]]. Finally, iterate through count[] and return the index with maximum value. This approach takes O(n) time, but requires O(k) space.
 */
uint32_t maxRepeating(uint32_t a[], const uint32_t n, const uint32_t k) {
  if (!n || !k || k > n)
    throw exception();

  // Iterate though input array, for every element a[i], increment a[a[i]%k] by k
  for (const auto& i : a) //int i = 0; i< n; i++)
    a[i%k] += k;

  // Find index of the maximum repeating element
  uint32_t max = a[0], ret = 0;
  for (uint32_t i = 1; i < n; ++i) {
    if (a[i] > max) {
      max = a[i];
      ret = i;
    }
  }

  /* Uncomment this code to get the original array back
       for (int i = 0; i< n; i++)
          arr[i] = arr[i]%k; */

  return ret;
}
