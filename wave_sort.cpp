/*
Given an unsorted array of integers, sort the array into a wave like array. An array a[0..n-1] is sorted in wave form if arr[0] >= arr[1] <= arr[2] >= arr[3] <= arr[4] >= ...
 */
#include <iostream>

using namespace std;

/*
This can be done in O(n) time by doing a single traversal of given array. The idea is based on the fact that if we make sure that all even positioned (at index 0, 2, 4, ..) elements are greater than their adjacent odd elements, we don't need to worry about odd positioned element. Following are simple steps.
1) Traverse all even positioned elements of input array, and do following.
...a) If current element is smaller than previous odd element, swap previous and current.
...b) If current element is smaller than next odd element, swap next and current.
 */
void waveSort(vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (n < 2)
    return;

  for (uint32_t i = 0; i < n; i += 2) {
    // If current even element is smaller than previous
    if (i > 0 && a[i-1] > a[i])
      swap(a[i], a[i-1]);
    // If current even element is smaller than next
    if (i < n-1 && a[i] < a[i+1])
      swap(a[i], a[i+1]);
  }
}
