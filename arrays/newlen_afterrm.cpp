/*
Given an array and a value, remove all occurrences of that value in place and return the new length.
The order of elements can be changed, and the elements after the new length don't matter.
 */
#include <iostream>

using namespace std;

uint newLenAfterRm(int a[], const uint n, const int target) {
  if (!n) {
    return 0;
  }

  uint ret = 0;
  uint i = 0;
  while (i < n) {
    if (a[i] == target) {
      while (++i < n && a[i] == target) {
      }
    } else {
      a[ret++] = a[i++];
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  int a[] = {0,4,4,0,0,2,4,4};
  cout << "New length: " << newLenAfterRm(a, 8, 4) << endl;

  return 0;
}
