#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

/*
A string of length n has n! permutation.

Below are the permutations of string ABC.
ABC, ACB, BAC, BCA, CAB, CBA
 */
set<string> stringPermus_recur(string s) {
  const uint len = s.length();
  if (len <= 1)
    return {s};

  set<string> ret;

  function<void(const uint)> solve =
    [&](const uint idx) {
    if (idx == len-1) {
      ret.insert(s);
      return;
    }

    for (uint i = idx; i < len; ++i) { // backtracking
      swap(s[idx], s[i]);
      solve(idx+1);
      swap(s[idx], s[i]);
    }
  };

  solve(0);
  return ret;
}

/*
Given a string of length n, print all permutation of the given string.
Repetition of characters is allowed. Print these permutations in lexicographically sorted order.
 */
vector<string> repeatingPermus_recur(string s) {
  const uint len = s.length();
  if (!len)
    return {};

  // Sort the input string so that we get all output strings in lexicographically sorted order
  sort(s.begin(), s.end());

  // Create a temp array that will be used by allLexicographicRecur()
  char mem[len+1];
  mem[len] = '\0';
  vector<string> ret;

  function<void(const uint)> solve =
    [&](const uint index) {
    if (index == len) {
      ret.push_back(mem);
      return;
    }

    // One by one fix all characters at the given index and recur for the subsequent indexes
    for (uint i = 0; i < len; ++i) {
      // Fix the ith character at index and if this is not the last index then recursively call for higher indexes
      mem[index] = s[i];
      solve(index+1);
    }
  };

  solve(0);
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
string kthPermu(const uint n, uint k) {
  function<uint(const uint)> factorial =
    [](const uint n) {
    uint ret = 1;

    for (uint i = 2; i < n+1; ++i)
      ret *= i;

    return ret;
  };

  uint total = factorial(n);
  string candidate = string("123456789").substr(0, n);
  string ret(n, ' ');

  for (uint i = 0; i < n; ++i) {
    total /= (n-i);
    const uint idx = (k-1)/total;
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
vector<vector<int>> numberPermus_recur(vector<int>& nums) {
  const uint n = nums.size();
  if (n <= 1)
    return {nums};

  vector<vector<int>> ret;

  function<void(const uint)> solve =
    [&](const uint idx) {
    if (idx == n) {
      ret.push_back(nums);
      return;
    }

    for (uint i = idx; i < n; ++i) { // backtracking
      swap(nums[i], nums[idx]);
      solve(idx+1);
      swap(nums[i], nums[idx]);
    }
  };

  solve(0);
  return ret;
}

/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.
For example,
[1,1,2] have the following unique permutations:
[1,1,2], [1,2,1], [2,1,1].
 */
vector<vector<int>> uniquePermus(vector<int>& nums) {
  const uint n = nums.size();
  if (n <= 1)
    return {nums};

  sort(nums.begin(), nums.end());

  function<bool()> nextPermu = [&](){
    uint first = 0, last = n;
    uint pre_last = last-1;

    while (first < pre_last) {
      uint t = pre_last;
      if (nums[--pre_last] < nums[t]) {
        uint l = last;
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

  vector<vector<int>> ret;

  do {
    ret.push_back(nums);
  } while (nextPermu());

  return ret;
}

/*
Implement function strstrp(string a, string b) returns index where any permutation of b is a substring of a.
 strstrp("hello", "ell") returns 0
 strstrp("hello", "lle") returns 1
 strstrp("hello", "wor") returns -1
 */
int strstrp(const string& a, const string& b) {
  const uint aLen = a.length(), bLen = b.length();
  if (!aLen || !bLen)
    return -1;

  int maxIdx = -1;

  for (uint i = 0; i < bLen; ++i) {
    string substr = b.substr(0, i+1);
    set<string> permus = stringPermus_recur(substr);

    bool allSub = true;

    for (auto& s : permus) {
      const char* p = strstr(a.c_str(), s.c_str());
      if (!p) {
        allSub = false;
        break;
      }
    }

    if (allSub) {
      maxIdx = max(maxIdx, (int)i);
    }
  }

  return maxIdx;
}

int main(int argc, char** argv) {
  string s = "lel"; //"ABC";
  cout << "All permutations of " << s << " are: ";
  set<string> permus = stringPermus_recur(s);
  for (const auto& i : permus) {
    cout << i << " ";
  }
  cout << endl;

  s = "ABC";
  vector<string> ps = repeatingPermus_recur(s);
  for (auto& i : ps)
    cout << i << " ";
  cout << endl;

  uint n = 3;
  uint k = 5;
  cout << k << "th permutation of [1,..." << n << "]:" << endl;
  cout << kthPermu(3, 5) << endl;

  vector<int> nums = {1,2,3};
  vector<vector<int>> res = numberPermus_recur(nums);

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

  cout << "strstrp: " << strstrp("hello", "ell") << endl;
  cout << "strstrp: " << strstrp("hello", "lle") << endl;
  cout << "strstrp: " << strstrp("hello", "wor") << endl;

  return 0;
}
