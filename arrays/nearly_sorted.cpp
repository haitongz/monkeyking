/*
Given an array of n elements, where each element is at most k away from its target position,
devise an algorithm that sorts in O(nlogk) time.
 */
void sortK(const int32_t a[], const uint32_t n, const uint32_t k) {
  // Create a Min Heap of first (k+1) elements from input array
  int32_t harr[k+1];

  for (uint32_t i = 0; i < k+1 && i < n; ++i) // i < n condition is needed when k > n
    harr[i] = a[i];

  MinHeap hp(harr, k+1);

  // i is index for remaining elements in arr[] and ti is target index of for cuurent minimum element in Min Heapm 'hp'.
  for (uint32_t i = k+1, ti = 0; ti < n; ++i, ++ti) {
    // If there are remaining elements, then place root of heap at target index and add arr[i] to Min Heap
    if (i < n)
      a[ti] = hp.replaceMin(a[i]);
    else // Otherwise place root at its target index and reduce heap size
      a[ti] = hp.extractMin();
  }
}
