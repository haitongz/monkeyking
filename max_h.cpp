/*
Given an array, find h that at least h elements are no smaller than h.

For example:
array is {2,3,5}, return 2.
array is {5,6,7,8}, return 4.
 */
#include <iostream>
#include <vector>

using namespace std;

int32_t find_h_s(const vector<int>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return -1;

  int32_t res = 0;

  for (uint32_t low = 0, high = n-1; low < high;) {
    const uint32_t mid = low+(high-low)/2;
    nth_element(nums.begin()+low, nums.begin()+mid, nums.begin()+high, greater<int32_t>());
    if (nums[mid] >= mid+1){
      res = max(res, mid+1);
      low = mid+1;
    } else {
      high = mid;
    }
  }

  return res;
}

int32_t find_h_c(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    throw exception();

  vector<int32_t> m(n+1, 0);
  for (auto v : nums) {
    if (v >= n)
      ++m[n];
    else
      ++m[v];
  }

  for (uint32_t i = n, sum = 0; i > 0; --i) {
    sum += m[i];
    if (sum >= i)
      return i;
  }

  return 0;
}

int32_t find_h_sort(vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    throw exception();

  sort(nums.begin(), nums.end(), greater<int32_t>());
  for (uint32_t i = n; i > 0; --i) {
    if (i <= nums[i-1])
      return i;
  }

  return 0;
}

int main(int argc, char** argv) {
}
