/*
An array contains both positive and negative numbers in random order. Rearrange the array elements so that positive and negative numbers are placed alternatively. Number of positive and negative numbers need not be equal. If there are more positive numbers they appear at the end of the array. If there are more negative numbers, they too appear in the end of the array.
 */
void rearrange(int32_t a[], const uint32_t n) {
  // The following few lines are similar to partition process of QuickSort. The idea is to consider 0 as pivot and divide the array around it.
  int32_t i = -1;
  for (uint32_t j = 0; j < n; j++) {
    if (a[j] < 0) {
      ++i;
      swap(a[i], a[j]);
    }
  }

  // Now all positive numbers are at end and negative numbers at the beginning of array. Initialize indexes for starting point of positive and negative numbers to be swapped
  uint32_t pos = i+1, neg = 0;

  // Increment the negative index by 2 and positive index by 1, i.e., swap every alternate negative number with next positive number
  while (pos < n && neg < pos && a[neg] < 0) {
    swap(a[neg], a[pos]);
    ++pos;
    neg += 2;
  }
}
