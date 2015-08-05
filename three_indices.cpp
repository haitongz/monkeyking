/*
Given a array of integers, find 3 indices i,j,k such that i<j<k and a[i]<a[j]<a[k]. Best possible is a O(n) algorithm.
 */
#include <iostream>
#include <vector>

using namespace std;

vector<int32_t> threeIndices(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (n < 3)
    return {};

  vector<int32_t> res = {0,-1,0};
  int32_t min_idx = 0;

  for (uint32_t i = 1; i < n; ++i) {
    if (res[1] < 0) {
      if (nums[i] < nums[min_idx]) {
        min_idx = i;
        res[0] = i;
      } else if (nums[i] > nums[min_idx]) {
        res[1] = i;
      }
    } else {
      if (nums[i] > nums[res[1]]) { // found i,j,k
        res[2] = i;
        return res;
      } else if (nums[i] > nums[res[0]]) {
        res[1] = i;
      } else if (nums[i] > nums[min_idx]) {
        res[0] = min_idx;
        res[1] = i;
      } else if (nums[i] < nums[min_idx]) {
        min_idx = i;
      }
    }
  }

  return {};
}

int main(int argc, char** argv) {
  vector<int32_t> nums = {2,3,1,4};
  vector<int32_t> res = threeIndices(nums);
  if (res.size())
    cout << "No valid indices!" << endl;

  for (auto i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
