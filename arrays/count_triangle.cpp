/*
Given an unsorted array of positive integers. Find the number of triangles that can be formed with three different array
elements as three sides of triangles.
 */
/*
1. Sort the array in non-decreasing order.
2. Initialize two pointers 'i' and 'j' to first and second elements respectively, and initialize count of triangles as 0.
3. Fix 'i' and 'j' and find the rightmost index 'k' (or largest 'a[k]') such that 'a[i]+a[j] > a[k]'. The number of triangles
that can be formed with 'a[i]' and 'a[j]' as two sides is 'k ' j'. Add 'k ' j' to count of triangles.
Let us consider 'a[i]' as 'a', 'a[j]' as b and all elements between 'a[j+1]' and 'a[k]' as 'c'.
The above mentioned conditions (ii) and (iii) are satisfied because 'a[i] < a[j] < a[k]'.
And we check for condition (i) when we pick 'k'.
4. Increment 'j' to fix the second element again.
Note that in step 3, we can use the previous value of 'k'. The reason is simple, if we know that the value
of 'a[i]+a[j-1]' is greater than 'a[k]', then we can say 'a[i]+a[j]' will also be greater than 'a[k]',
because the array is sorted in increasing order.
5. If 'j' has reached end, then increment 'i'. Initialize 'j' as 'i + 1', 'k' as 'i+2' and repeat the steps 3 and 4.
 */
uint32_t numOfTriangles(const uint32_t a[], const uint32_t n) {
    // Sort the array elements in non-decreasing order
  sort(a.begin(), a.end(), less);

  // Initialize count of triangles
  uint32_t ret = 0;
  // Fix the first element.  We need to run till n-3 as the other two elements are selected from arr[i+1...n-1]
  for (uint32_t i = 0; i < n-2; ++i) {
    // Initialize index of the rightmost third element
    uint32_t k = i+2;

    // Fix the second element
    for (uint32_t j = i+1; j < n; ++j) {
      // Find the rightmost element which is smaller than the sum of two fixed
      // elements. The important thing to note here is, we use the previous value of k.
      // If value of arr[i] + arr[j-1] was greater than arr[k], then arr[i] + arr[j] must be greater than k,
      // because thearray is sorted.
      while (k < n && (a[i]+a[j] > a[k]))
        ++k;

      // Total number of possible triangles that can be formed with the two fixed elements is k-j-1.
      // The two fixed elements are a[i] and a[j].  All elements between a[j+1] to a[k-1] can form
      // a triangle with a[i] and a[j]. One is subtracted from k because k is incremented one extra in above while loop.
      // k will always be greater than j. If j becomes equal to k, then above loop will increment k,
      // because arr[k] + arr[i] is always greater than a[k]
      ret += k-j-1;
    }
  }

  return ret;
}
