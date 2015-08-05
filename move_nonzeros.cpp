#include <iostream>
#include <vector>

using namespace std;
/*
Given an array of integers. Move all non-zero elements to the left of all zero elements.
 */
void moveNonZeros(vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return;

  for (uint32_t i = 0, flag = 0; i < n; ++i) {
    if (nums[i])
      swap(nums[i], nums[flag++]);
  }
}

/*
Follow up:
Put all non-zero elements at left of array, minimum changes to this array, left-most elements can be anything, returns number of non-zero elements.
 */
uint32_t moveNonZeros_2(vector<int32_t>& nums) { // issue: not all non-zero are at left
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  uint32_t ret = 0;
  uint32_t left = 0, right = n-1;

  while (left <= right) {
    while (!nums[left])
      ++left;

    if (left > right)
      break;

    if (!nums[right])
      nums[left++] = 0;

    ++ret;
    --right;
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {1,0,2,3,4,0};
  moveNonZeros(a);
  for (auto i : a) {
    cout << i << ",";
  }
  cout << endl;

  a = {1,0,2,3,4,0};
  cout << "There are " << moveNonZeros_2(a) << " non-zero elements!" << endl;
  return 0;
}
