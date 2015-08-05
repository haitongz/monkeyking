/*
Given an array of integers, replace every element with the next greatest element (greatest element on the right side) in the array. Since there is no element next to the last element, replace it with -1. For example, if the array is {16, 17, 4, 3, 5, 2}, then it should be modified to {17, 5, 5, 5, 2, -1}.
 */
vector<int32_t> nextGreatest(const int32_t a[], const uint32_t n) { // O(n)
  if (!n)
    return {};
  if (n < 2)
    return {-1};

  vector<int32_t> ret;

  // Initialize the next greatest element
  int32_t max_from_right = a[n-1];

  // The next greatest element for the rightmost element is always -1
  a[n-1] = -1;

  // Replace all other elements with the next greatest
  for (int32_t i = size-2; i >= 0; --i) {
    // Store the current element (needed later for updating the next greatest element)
    int32_t tmp = a[i];
    // Replace current element with the next greatest
    a[i] = max_from_right;

    // Update the greatest element, if needed
    max_from_right = max(max_from_right, tmp);
  }
}
