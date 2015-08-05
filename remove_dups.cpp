/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array A = [1,1,2],
Your function should return length = 2, and A is now [1,2].
*/
#include <iostream>

using namespace std;

uint32_t removeDupsInSorted(int32_t A[], const uint32_t n) {
  uint32_t i = 1;

  for (uint32_t j = 1; j < n; ++j) {
    if (A[j] != A[j-1])
      A[i++] = A[j];
  }

  return n ? i : 0;
}

int main(int argc, char** argv) {
  int32_t a[3] = {1, 1, 2};
  uint32_t len = removeDupsInSorted(a, 3);

  for (uint32_t i = 0; i < len; ++i)
    cout << a[i] << ",";
  cout << endl;
}
