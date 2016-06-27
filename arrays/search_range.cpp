/*
Given a sorted array of integers, find the starting and ending position of a given target value.
Your algorithm's runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].

Given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].
 */
#include <iostream>
#include <vector>

using namespace std;

pair<int32_t,int32_t> searchRange(const vector<int32_t>& nums, const int32_t target) {
  const uint32_t n = nums.size();
  if (!n)
    return {-1, -1};

  pair<int32_t,int32_t> ret = {-1,-1};
  uint32_t start = 0, end = n-1;

  while (start <= end) {
    const uint32_t mid = start+(end-start)/2;
    if (nums[mid] >= target)
      end = mid-1;
    else
      start = mid+1;
  }

  if (start >= n || nums[start] != target)
    return ret;

  ret.first = start;
  for (start = 0, end = n-1; start <= end;) {
    const uint32_t mid = start+(end-start)/2;
    if (nums[mid] <= target)
      start = mid+1;
    else
      end = mid-1;
  }

  ret.second = end;
  return ret;
}

int main(int argc, char** argv) {
  vector<int32_t> nums = {5, 7, 7, 8, 8, 10};
  uint32_t target = 8;
  pair<int32_t,int32_t> res = searchRange(nums, target);
  cout << "[" << res.first << ", " << res.second << "]" << endl;
}
