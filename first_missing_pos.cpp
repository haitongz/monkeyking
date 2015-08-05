#include <iostream>
#include <vector>

using namespace std;

/*
Given an unsorted integer array, find the first missing positive integer.
Given [1,2,0] return 3, and [3,4,-1,1] return 2.
Your algorithm should run in O(n) time and uses constant space.

if nums[i] is positive, say we have nums[i] = x, we know it should be in slot nums[x-1]. We can swap nums[x-1] with nums[i] so as to place x into the right place; if nums[i] is non-positive, 0, or nums[i] > nums.size(), ignore it; if nums[i] == nums[x-1], we do not swap, two cases: 1. Maybe nums[i] = i+1, nums[i] is correct; 2. though nums[i] is not correct like [1,1] index 1, but nums[0] == nums[1], swap nums[1] with nums[0] will only give rise to infinite loop.
 */
uint32_t firstMissingPos(vector<int32_t>& A) {
  const uint32_t n = A.size();
  if (!n)
    return -1;

  for (uint32_t i = 0; i < n; ++i) {
    int32_t& v = A[i];
    if (v > 0 && v < n) {
      if (v != A[v-1]) {
        swap(A[v-1], v);
        --i;
      }
    }
  }

  for (uint32_t i = 0; i < n; ++i)
    if (A[i] != i+1)
      return i+1;

  return n+1;
}

/*
Given an array of integers, find the first repeating element in it. We need to find the element that occurs more than once and whose index of first occurrence is smallest.
 */
int32_t firstRepeating(const vector<int32_t>& a) {
}

/*
Given a sorted array of n integers where each integer is in the range from 0 to m-1 and m > n. Find the smallest number that is missing from the array.
 */
int32_t firstMissing(const uint32_t array[], const uint32_t n) {
  if (!n)
    throw exception();

  function<int32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t start, const uint32_t end) {
    if (start > end)
      return end+1;

    if (start != a[start])
      return start;

    const uint32_t mid = (start+end)/2;
    if (a[mid] > mid)
      return solve(start, mid);
    else
      return solve(mid+1, end);
  };

  return solve(0, n-1);
}

int main(int argc, char** argv) {
  vector<int32_t> A = {1,2,0};
  vector<int32_t> B = {3,4,-1,1};

  cout << firstMissingPos(A) << endl;
  cout << firstMissingPos(B) << endl;
}
