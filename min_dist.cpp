/*
Given an unsorted array a[] and two numbers x and y, find the minimum distance between x and y in a[]. The array might also contain duplicates. You may assume that both x and y are different and present in a[].

1) Traverse array from left side and stop if either x or y is found. Store index of this first occurrence in a variable say prev
2) Now traverse a[] after the index prev. If the element at current index i matches with either x or y then check if it is different from a[prev]. If it is different then update the minimum distance if needed. If it is same then update prev i.e., make prev = i.
 */
uint32_t minDist(const int32_t a[], const uint32_t n, const int32_t x, const int32_t y) {
  uint32_t ret = MAX_LIMIT;
  uint32_t prev;

  // Find the first occurence of any of the two numbers (x or y) and store the
  // index of this occurence in prev
  for (uint32_t i = 0; i < n; ++i) {
    if (a[i] == x || a[i] == y) {
      prev = i;
      break;
    }
  }

  // Traverse after the first occurence
  for (; i < n; ++i) {
    if (a[i] == x || a[i] == y) {
      // If the current element matches with any of the two then check if
      // current element and prev element are different. Also check if this value is smaller than minimm distance so far
      if (a[prev] != a[i] && (i-prev) < ret) {
        ret = i-prev;
        prev = i;
      }
      else
        prev = i;
    }
  }

  return min_ret;
}
