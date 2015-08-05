/*
Given an array, return max number of surpassers.

A surpasser of a[i] is element a[j], while j > i and a[j] > a[i].
*/
#include <iostream>
#include <vector>

using namespace std;

uint32_t maxSurpasserNum(vector<int32_t> nums) {
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  vector<int32_t> temp(n);
  uint32_t res = 0;
  unordered_map<int32_t, uint32_t> counts;

  auto merge = [&](const uint32_t left, const uint32_t mid, const uint32_t right) {
    if (left >= right)
      return;

    uint32_t l = mid, r = right, curr = right;
    while (l >= left && r > mid) {
      if (nums[l] < nums[r]) {
        counts[nums[l]] += r - mid;
        res = max(res, counts[nums[l]]);
        temp[curr--] = nums[l--];
      } else {
        temp[curr--] = nums[r--];
      }
    }

    while (l >= left)
      temp[curr--] = nums[l--];
    while (r > mid)
      temp[curr--] = nums[r--];

    copy(temp.begin()+left, temp.begin()+right+1, nums.begin()+left);
  };

  function<void(const uint32_t, const uint32_t)> sort = [&](const uint32_t left, const uint32_t right) {
    if (left >= right)
      return;

    const uint32_t mid = left + (right-left)/2;
    sort(left, mid);
    sort(mid+1, right);
    merge(left, mid, right);
  };

  sort(0, n-1);
  return res;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {2,1,2,1,5,4,5,5};
  cout << maxSurpasserNum(a) << endl;

  return 0;
}
