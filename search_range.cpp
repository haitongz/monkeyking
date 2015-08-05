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

  pair<int32_t,int32_t> res = {-1,-1};
  uint32_t low = 0, high = n-1;

  while (low <= high) {
    const uint32_t mid = low + ((high-low)>>1);
    if (nums[mid] >= target)
      high = mid-1;
    else
      low = mid+1;
  }

  if (low >= n || nums[low] != target)
    return res;

  res.first = low;
  for (low = 0, high = n-1; low <= high;) {
    const uint32_t mid = low + ((high-low)>>1);
    if (nums[mid] <= target)
      low = mid+1;
    else
      high = mid-1;
  }

  res.second = high;
  return res;
}

int main(int argc, char** argv) {
  vector<int32_t> nums = {5, 7, 7, 8, 8, 10};
  uint32_t target = 8;
  pair<int32_t,int32_t> res = searchRange(nums, target);
  cout << "[" << res.first << ", " << res.second << "]" << endl;
}
