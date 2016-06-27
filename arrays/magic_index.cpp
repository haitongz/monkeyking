/**
A magic index in an array A[0...n-1] is defined to be an index such that A[i] = i.
Given a sorted array, write a method to find a magic index, if one exists, in array A.

FOLLOW UP: What if the values are not distinct?
 */

// O(1) space, O(lgn) time
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int32_t magicIndex(const vector<uint32_t>& A) {
  const uint32_t n = A.size();
  if (!n)
    return -1;

  function<int32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t start, const uint32_t end) -> int32_t {
    if (start > end || end > n-1) {
      return -1;
    }

    const uint32_t mid = start + (end-start)/2;
    const uint32_t t_idx = A[mid];
    if (t_idx == mid)
      return mid;

    const uint32_t new_end = min(mid-1, t_idx); // optimization: array is sorted so when array[mid] < mid-1,
                                                // magic index can only appear before index array[mid]
    int32_t test_left = solve(start, new_end);
    if (test_left != -1)
      return test_left;

    const int32_t new_start = max(mid+1, t_idx); // same optimization
    return solve(new_start, end);
  };

  return solve(0, n-1);
}

int main(int argc, char** argv) {
  vector<uint32_t> A = {1,2,3,3,4,5,6,9};
  int32_t index = magicIndex(A);
  if (index == -1) {
    cout << "No magic index!" << endl;
  } else {
    cout << "First magic index: " << index << endl;
  }

  return 0;
}
