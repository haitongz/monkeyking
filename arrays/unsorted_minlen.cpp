/*
Given an unsorted array a[] of size n, find the minimum length subarray a[s..e] such that sorting
this subarray makes the whole array sorted.
 */

/*
1.
a) Scan from left to right and find the first element which is greater than the next element. Let s be the index
of such an element.
b) Scan from right to left and find the first element (first in right to left order) which is smaller than the next
element (next in right to left order). Let e be the index of such an element.

2) Check whether sorting the candidate unsorted subarray makes the complete array sorted or not. If not, then include
more elements in the subarray.
a) Find the minimum and maximum values in a[s..e]. Let minimum and maximum values be min and max. min and max for
[30, 25, 40, 32, 31] are 25 and 40 respectively.
b) Find the first element (if there is any) in a[0..s-1] which is greater than min, change s to index of this element.
c) Find the last element (if there is any) in a[e+1..n-1] which is smaller than max, change e to index of this element.
 */
uint32_t minLen(int32_t a[], const uint32_t n) {
  if (!n)
    return 0;

  // step 1(a) of above algo
  uint32_t s = 0;
  for (; s < n-1; ++s)
    if (a[s] > a[s+1])
      break;
  if (s == n-1) {
    cout << "Complete array is sorted" << endl;
    return 0;
  }
  // step 1(b) of above algo
  uint32_t e = n-1;
  for (; e > 0; --e) {
    if (a[e] < a[e-1])
      break;
  }
  // step 2(a) of above algo
  int32_t max_v = a[s]; min_v = a[s];
  for (uint32_t i = s+1; i < e+1; ++i) {
    max_v = max(a[i], max_v);
    min_v = min(a[i], min_v);
  }
  // step 2(b) of above algo
  for (uint32_t i = 0; i < s; ++i) {
    if (a[i] > min_v) {
      s = i;
      break;
    }
  }
  // step 2(c) of above algo
  for (uint32_t i = n-1; i > e; --i) {
    if (a[i] < max_v) {
      e = i;
      break;
    }
  }
}
