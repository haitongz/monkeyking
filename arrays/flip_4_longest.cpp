/*
Given an array of 0s and 1s, find the position of 0 to be replaced with 1 to get longest continuous sequence of 1s.
Expected time complexity is O(n) and auxiliary space is O(1).
 */
#include <iostream>

using namespace std;

int flip4Longest(const uint a[], const uint n) {
  if (!n) {
    return -1;
  }

  uint currLen = a[0] ? 1 : 0;
  uint maxLen = currLen;
  int ret = -1;

  for (uint i = 1; i < n; ++i) {
    if (a[i]) {
      ++currLen;
      maxLen = max(maxLen, currLen);
    } else { // a[i] == 0
      if (a[i-1] && a[i+1]) {
        ++currLen;
        ret = i;
        maxLen = max(maxLen, currLen);
      } else {
        currLen = 0;
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  uint a[] = {1,1,0,0,1,0,1,1,1,0,1,1,1};
  const uint n = sizeof(a)/sizeof(a[0]);

  cout << "Index of 0 to be replaced is " << flip4Longest(a, n) << endl;
  return 0;
}
