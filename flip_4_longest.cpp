/*
Given an array of 0s and 1s, find the position of 0 to be replaced with 1 to get longest continuous sequence of 1s. Expected time complexity is O(n) and auxiliary space is O(1).
 */
#include <iostream>

using namespace std;

int32_t flip4Longest(const uint8_t a[], const uint32_t n) {
  if (!n)
    return -1;

  uint32_t curr_len = a[0] ? 1 : 0;
  uint32_t max_len = curr_len;
  int32_t ret = -1;

  for (uint32_t i = 1; i < n; ++i) {
    if (a[i]) {
      ++curr_len;
      max_len = max(max_len, curr_len);
    } else { // a[i] == 0
      if (a[i-1] && a[i+1]) {
        ++curr_len;
        ret = i;
        max_len = max(max_len, curr_len);
      } else {
        curr_len = 0;
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  uint8_t a[] = {1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1};
  const uint32_t n = sizeof(a)/sizeof(a[0]);

  cout << "Index of 0 to be replaced is " << flip4Longest(a, n) << endl;
  return 0;
}
