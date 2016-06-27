#include <iostream>

using namespace std;

/*
Given an array a[] of integers, find out the difference between any two elements such that
larger element appears after the smaller number in a[].

take the difference with the minimum element found so far. So we need to keep track of 2 things:
1) Maximum difference found so far (maxDiff).
2) Minimum number visited so far (minElem).

Time Complexity: O(n)
Auxiliary Space: O(1)
 */
int maxDiffInSequence(const int a[], const uint n) {
  int maxDiff = a[1]-a[0];
  int minElem = a[0];

  for (uint i = 1; i < n; ++i) {
    if (a[i]-minElem > maxDiff) {
      maxDiff = a[i]-minElem;
    }
    if (a[i] < minElem) {
      minElem = a[i];
    }
  }

  return maxDiff;
}


