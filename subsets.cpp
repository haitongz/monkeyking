#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

/*
Given a set of distinct integers, S, return all possible subsets.
 */
vector<vector<int>> subsets(vector<int>& S) {
  const uint n = S.size();
  if (n <= 1)
    return {S};

  sort(S.begin(), S.end());

  vector<vector<int>> ret;
  vector<int> to_ext;

  function<void(const uint)> solve =
    [&](const uint idx) {
    ret.push_back(to_ext);

    if (idx >= n)
      return;

    for (uint i = idx; i < n; ++i) { // backtracking
      to_ext.push_back(S[i]);
      solve(i+1);
      to_ext.pop_back();
    }
  };

  solve(0);

  return ret;
}

/*
Follow Up:
Given a collection of integers that might contain duplicates, S, return all possible subsets.
 */
vector<vector<int>> subsetsWithDup_iter(vector<int>& S) {
  const uint n = S.size();
  if (n <= 1)
    return {S};

  sort(S.begin(), S.end());

  vector<vector<int>> ret(1);
  set<vector<int>> sv(ret.begin(), ret.end());

  for (uint i = 0; i < n; ++i) {
    for (int j = ret.size()-1; j >= 0; --j) {
      ret.push_back(ret[j]);
      ret.back().push_back(S[i]);
      sv.insert(ret.back());
    }
    ret.assign(sv.begin(), sv.end());
  }

  return ret;
}

vector<vector<int>> subsetsWithDup_recur(vector<int>& S) {
  if (S.empty())
    return {};

  map<int,uint> counts;
  for (auto i : S)
    ++counts[i];

  vector<int> uniqNos;
  for (auto p : counts)
    uniqNos.push_back(p.first);

  sort(uniqNos.begin(), uniqNos.end());

  const uint n = uniqNos.size();

  vector<vector<int>> ret;
  vector<int> to_ext;

  function<void(const uint)> solve =
    [&](const uint idx) {
    ret.push_back(to_ext);

    for (uint i = idx; i < n; ++i) {
      uint count = counts[uniqNos[i]];
      for (uint j = 1; j < count+1; ++j) { // backtracking
        for (uint k = 1; k < j+1; ++k)
          to_ext.push_back(uniqNos[i]);

        solve(i+1);

        for (uint k = 1; k < j+1; ++k)
          to_ext.pop_back();
      }
    }
  };

  solve(0);
  return ret;
}

/*
Given two arrays: a1[0..m-1] and a2[0..n-1]. Find whether a2[] is a subset of a1[] or not.
Both the arrays are not in sorted order.

Time Complexity: O(mLogm + nLogn)
 */
bool isSubset(int a1[], int a2[], const uint m, const uint n) {
  if (m < n)
    return 0;

  // quickSort(a1, 0, m-1);
  // quickSort(a2, 0, n-1);

  uint i, j;
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
  vector<int> S = {1,2,3};
  vector<vector<int>> res = subsets(S);
  for (const auto& i : res) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  S = {1,2,2};
  res = subsetsWithDup_iter(S);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  res = subsetsWithDup_recur(S);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
