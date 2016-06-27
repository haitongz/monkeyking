/*
Given a sorted array and a target value, return the index if the target is found.
If not, return the index where it would be if it were inserted in order.
You may assume no duplicates in the array.

Examples:
[1,3,5,6], 5 -> 2
[1,3,5,6], 2 -> 1
[1,3,5,6], 7 -> 4
[1,3,5,6], 0 -> 0
 */
#include <iostream>

using namespace std;

int insertPosition(int a[], const uint n, int target) {
  if (!n) {
    return 0;
  }

  uint low = 0, up = n-1;

  while (low <= up) {
    uint mid = low + ((up-low)>>1);
    if (a[mid] >= target) {
      if (!mid) {
        return 0;
      } else {
        up = mid-1;
      }
    } else {
      low = mid+1;
    }
  }

  return low;
}

int main(int argc, char** argv) {
  int a[] = {1,3,5,6};
  cout << insertPosition(a, 4, 5) << endl;
  cout << insertPosition(a, 4, 2) << endl;
  cout << insertPosition(a, 4, 7) << endl;
  cout << insertPosition(a, 4, 0) << endl;

  return 0;
}
