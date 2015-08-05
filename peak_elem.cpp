/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] != num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine. You may imagine that num[-1] = num[n] = INT_MIN. For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
 */

//Binary search. If mid is the peak, return it. If mid is not the peak, it must be less than or equal to one of its neighbors. Suppose it is less than or equal to its left, then the left half must contains a peak. Why? If the left half is not monotonically decreasing, there must contains a peak. If the left half is monotonically decreasing, the peak is the first element.
#include <iostream>
#include <functional>

using namespace std;

int32_t peakElement(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    throw exception();

  uint32_t head = 0, tail = n-1;
  while (head < tail-1) {
    uint32_t mid = head+(tail-head)/2;
    if (nums[mid] > nums[mid-1] && num[mid] > num[mid+1])
      return mid;
    if (nums[mid] <= nums[mid-1])
      tail = mid;
    else
      head = mid;
  }

  return nums[head] > nums[tail] ? head : tail;
}

/*
Linear scanning, O(n)
 */
int32_t peakElement2(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    throw exception();

  for (uint32_t i = 1; i < n-1; ++i) {
    if (num[i]>num[i+1] && num[i] > num[i-1]) {
      return i;
    }
  }

  if (num[0] > num[1])
    return 0;
  if (num[len-1] > num[len-2])
    return len-1;
}

/*
Binary search, O(logn)
 */
int32_t peakElement3(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    throw exception();

  function<int32_t(const uint32_t,const uint32_t)> dfs =
    [&](const uint32_t start, const uint32_t end) {
    if (start == end)
      return start;
    if (end-start == 1)
      return nums[start] > nums[end] ? start : end;

    const uint32_t mid = start+(end-start)/2;
    if (nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1])
      return mid;
    else if (nums[mid] < nums[mid-1])
      return dfs(start, mid-1);
    else
      return dfs(mid+1, end);
  };

  return dfs(0, n-1);
}

int main(int argc, char** argv) {
}
