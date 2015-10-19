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

int searchInsert(int32_t A[], const uint32_t n, int32_t target) {
  uint32_t low = 0, up = n-1;

  while (low <= up) {
    uint32_t mid = low + ((up-low)>>1);
    if (A[mid] >= target)
      up = mid-1;
    else
      low = mid+1;
  }

  return low;
}

int main(int argc, char** argv) {
}
