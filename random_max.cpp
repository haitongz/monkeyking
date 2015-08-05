/*
Given an array, return random index of maximum elements in the array. Do it with O(1) space.
For example, given array [2,1,2,1,5,4,5,5], return random index within [4,6,7].
*/
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int32_t random_max(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return -1;

  uint32_t res = 0, count = 0, max = numeric_limits::min();
  for (uint32_t i = 0; i < n; ++i) {
    if (nums[i] > max) {
      max = nums[i];
      count = 1;
      res = i;
    } else if (nums[i] == max) {
      if ((rand() % ++count) == 0)
        res = i;
    }
  }

  return res;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {2,1,2,1,5,4,5,5};
  cout << random_max(a) << endl;

  return 0;
}
