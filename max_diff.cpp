/*
Given an array arr[] of integers, find out the difference between any two elements such that larger element appears after the smaller number in arr[].

take the difference with the minimum element found so far. So we need to keep track of 2 things:
1) Maximum difference found so far (max_diff).
2) Minimum number visited so far (min_element).
Time Complexity: O(n)
Auxiliary Space: O(1)
 */
#include <iostream>

using namespace std;

uint32_t maxDiff(const int32_t a[], const uint32_t n) {
  uint32_t max_diff = a[1]-a[0];
  uint32_t min_element = a[0];

  for (uint32_t i = 1; i < n; ++i) {
    if (a[i]-min_element > max_diff)
      max_diff = a[i]-min_element;
    if (a[i] < min_element)
      min_element = a[i];
  }

  return max_diff;
}
