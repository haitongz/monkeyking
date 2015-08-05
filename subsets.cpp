#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
Given a set of distinct integers, S, return all possible subsets.
 */
vector<vector<int32_t>> subsets(vector<int32_t>& S) {
  const uint32_t n = S.size();
  if (n <= 1)
    return {S};

  sort(S.begin(), S.end());

  vector<vector<int32_t>> ret;
  vector<int32_t> to_ext;

  function<void(const uint32_t)> backtrack =
    [&](const uint32_t idx) {
    ret.push_back(to_ext);

    if (idx >= n)
      return;

    for (uint32_t i = idx; i < n; ++i) {
      to_ext.push_back(S[i]);
      backtrack(i+1);
      to_ext.pop_back();
    }
  };

  backtrack(0);

  return ret;
}

/*
Follow Up:
Given a collection of integers that might contain duplicates, S, return all possible subsets.
 */
vector<vector<int32_t>> subsetsWithDup_iter(vector<int32_t>& S) {
  const uint32_t n = S.size();
  if (n <= 1)
    return {S};

  sort(S.begin(), S.end());

  vector<vector<int32_t>> ret(1);
  set<vector<int32_t>> sv(ret.begin(), ret.end());

  for (uint32_t i = 0; i < n; ++i) {
    for (int32_t j = ret.size()-1; j >= 0; --j) {
      ret.push_back(ret[j]);
      ret.back().push_back(S[i]);
      sv.insert(ret.back());
    }
    ret.assign(sv.begin(), sv.end());
  }

  return ret;
}

vector<vector<int32_t>> subsetsWithDup_recur(vector<int32_t>& S) {
  if (S.empty())
    return {};

  unordered_map<int32_t,uint32_t> counts;
  for (auto i : S)
    ++counts[i];

  vector<int32_t> uniq_nums;
  for (auto p : counts)
    uniq_nums.push_back(p.first);

  sort(uniq_nums.begin(), uniq_nums.end());

  const uint32_t n = uniq_nums.size();

  vector<vector<int32_t>> ret;
  vector<int32_t> to_ext;

  function<void(const uint32_t)> backtrack =
    [&](const uint32_t idx) {
    ret.push_back(to_ext);

    for (uint32_t i = idx; i < n; ++i) {
      uint32_t count = counts[uniq_nums[i]];
      for (uint32_t j = 1; j < count+1; ++j) {
        for (uint32_t k = 1; k < j+1; ++k)
          to_ext.push_back(uniq_nums[i]);

        backtrack(i+1);

        for (uint32_t k = 1; k < j+1; ++k)
          to_ext.pop_back();
      }
    }
  };

  backtrack(0);
  return ret;
}

/*
Follow Up:
Let's change the function signature, suppose the input is only a integer N, please just print all power sets for {1,2,...,N}.
How can you reduce the memory usage?
 */
void printPowerSets(const uint32_t n) {
  uint32_t pow_set_size = pow(2, n);

  // Run from i 000..0 to 111..1
  for (uint32_t i = 0; i < pow_set_size; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      // Check if j-th bit in i is set. If set then pront j-th element from set
      if (i & (1 << j))
        cout << j+1 << " ";
    }
    cout << endl;
  }
}

/*
Given two arrays: a1[0..m-1] and a2[0..n-1]. Find whether a2[] is a subset of a1[] or not. Both the arrays are not in sorted order.

Time Complexity: O(mLogm + nLogn)
 */
bool isSubset(int32_t a1[], int32_t a2[], const uint32_t m, const uint32_t n) {
  if (m < n)
    return 0;

  quickSort(a1, 0, m-1);
  quickSort(a2, 0, n-1);

  uint32_t i, j;
  while (i < n && j < m) {
    if (a1[j] < a2[i])
      ++j;
    else if (a1[j] == a2[i]) {
      ++j;
      ++i;
    } else if (a1[j] > a2[i])
      return 0;
  }

  if (i < n)
    return 0;
  else
    return 1;
}

int main(int argc, char** argv) {
  vector<int32_t> v = {1,2,2};
  vector<vector<int32_t>> res = subsetsWithDup_iter(v);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  res = subsetsWithDup_recur(v);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
