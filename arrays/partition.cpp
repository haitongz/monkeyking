/*
Given an array nums of integers and an int k, partition the array (i.e move the elements in "nums") such that:

    All elements < k are moved to the left
    All elements >= k are moved to the right

Return the partitioning index, i.e the first index i nums[i] >= k.
 */
#include <iostream>

using namespace std;

uint partitionIndex(int nums[], const uint n, const int k) {
  if (!n) {
    return 0;
  }

  uint ret = 0;

  return ret;
}

int main(int argc, char** argv) {
  int a[] = {0,4,4,0,0,2,4,4};
  cout << "New length: " << newLenAfterRm(a, 8, 4) << endl;

  return 0;
}
