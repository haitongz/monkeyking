#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*
A string of length n has n! permutation.

Below are the permutations of string ABC.
ABC, ACB, BAC, BCA, CAB, CBA
 */
set<string> allPermus(string s) {
  const uint32_t len = s.length();
  if (!len)
    return {};

  set<string> ret;

  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t start, const uint32_t end) {
    if (start == end) {
      ret.insert(s);
      return;
    }

    for (uint32_t i = start; i < end+1; ++i) {
      swap(s[start], s[i]);
      solve(start+1, end);
      swap(s[start], s[i]);
    }
  };

  solve(0, len-1);
  return ret;
}

/*
The set [1,2,3,...,n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order, we get the following sequence (ie, for n = 3):
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.
Note: Given n will be between 1 and 9 inclusive.
 */
string kthPermu(const uint8_t n, uint32_t k) {
  function<uint32_t(const uint8_t)> factorial =
    [](const uint8_t n) {
    uint32_t ret = 1;

    for (uint8_t i = 2; i < n+1; ++i)
      ret *= i;

    return ret;
  };

  uint32_t total = factorial(n);
  string candidate = string("123456789").substr(0, n);
  string ret(n, ' ');

  for (uint8_t i = 0; i < n; ++i) {
    total /= (n-i);
    const uint8_t idx = (k-1)/total;
    ret[i] = candidate[idx];
    candidate.erase(idx, 1);
    k -= idx*total;
  }

  return ret;
}

/*
Given a collection of numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2] and [3,2,1].
 */
vector<vector<int32_t>> allPermus_recur(vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (n <= 1)
    return {nums};

  vector<vector<int32_t>> ret;

  function<void(const uint32_t)> backtrack =
    [&](const uint32_t idx) {
    if (idx == n) {
      ret.push_back(nums);
      return;
    }

    for (uint32_t i = idx; i < n; ++i) {
      swap(nums[i], nums[idx]);
      backtrack(idx+1);
      swap(nums[i], nums[idx]);
    }
  };

  backtrack(0);
  return ret;
}

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.
For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], [2,1,1].
 */
vector<vector<int32_t>> uniquePermus(vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (n <= 1)
    return {nums};

  sort(nums.begin(), nums.end());

  function<bool(void)> nextPermu = [&](void) -> bool {
    uint32_t first = 0, last = n;
    uint32_t pre_last = last-1;

    while (first < pre_last) {
      uint32_t t = pre_last;
      if (nums[--pre_last] < nums[t]) {
        uint32_t l = last;
        while (nums[--l] <= nums[pre_last]);

        swap(nums[l], nums[pre_last]);
        reverse(nums.begin()+t, nums.end());
        return true;
      }

      if (!pre_last) {
        reverse(nums.begin(), nums.end());
        return false;
      }
    }
  };

  vector<vector<int32_t>> ret;

  do {
    ret.push_back(nums);
  } while (nextPermu());

  return ret;
}

int main(int argc, char** argv) {
  uint32_t n = 3;
  uint32_t k = 5;
  cout << k << "th permutation of [1,..." << n << "]:" << endl;
  cout << kthPermu(3, 5) << endl;

  vector<int32_t> nums = {1,2,3};
  vector<vector<int32_t>> res = allPermus_recur(nums);

  cout << "All permutations of {1,2,3}:" << endl;
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  nums = {1,1,2};
  res = uniquePermus(nums);

  cout << "Unique permutations of {1,1,2}:" << endl;
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
