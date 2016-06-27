#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <queue>
#include <algorithm>

using namespace std;

/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
 */
vector<vector<uint>> comb_iter(const uint n, const uint k) {
  if (!n || !k || k > n) { // k cannot be bigger than n
    return {};
  } else if (k == 1) {
    vector<vector<uint>> ret;
    for (uint i = 1; i < n+1; ++i)
      ret.push_back({i});

    return ret;
  }

  deque<vector<uint>> q;
  for (uint i = 1; i < n+1; ++i)
    q.push_back({i});

  vector<vector<uint>> ret;

  while (!q.empty()) {
    vector<uint>& list = q.front();
    if (list.size() == k) {
      ret.push_back(list);
    } else {
      for (uint i = list.back()+1; i < n+1; ++i) {
        vector<uint> next_list(list);
        next_list.push_back(i);
        q.push_back(next_list);
      }
    }
    q.pop_front();
  }

  return ret;
}

vector<vector<uint>> comb_recur(const uint n, const uint k) {
  if (!n || !k || k > n) // k cannot no bigger than n
    return {};

  vector<vector<uint>> ret;
  vector<uint> to_ext;

  function<void(const uint,const uint)> solve =
    [&](const uint idx, const uint remain) {
    if (!to_ext.empty() && !remain) {
      ret.push_back(to_ext);
      return;
    }

    for (uint i = idx; i < n+1; ++i) { // backtracking
      to_ext.push_back(i);
      solve(i+1, remain-1);
      to_ext.pop_back();
    }
  };

  solve(1, k);
  return ret;
}

/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C
where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:

All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, ..., ak) must be in non-descending order. (ie, a1 <= a2 <= ... ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7,
A solution set is:
[7]
[2, 2, 3]
 */
vector<vector<uint>> combSum_recur(vector<uint>& C, const uint T) {
  const uint n = C.size();
  if (!n)
    return {};

  sort(C.begin(), C.end());

  vector<vector<uint>> ret;
  vector<uint> to_ext;

  function<void(const uint,const uint)> solve =
    [&](const uint idx, const uint curr_sum) {
    if (curr_sum == T) {
      ret.push_back(to_ext);
      return;
    }

    if (idx == n || curr_sum > T)
      return;

    for (uint i = idx; i < n; ++i) { // backtracking
      to_ext.push_back(C[i]);
      solve(i, curr_sum+C[i]);
      to_ext.pop_back();
    }
  };

  solve(0, 0);
  return ret;
}

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C
where the candidate numbers sum to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, ..., ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 10,1,2,7,6,1,5 and target 8,
A solution set is:
[1, 7]
[1, 2, 5]
[2, 6]
[1, 1, 6]
 */
vector<vector<uint>> uniqueSumComb_recur(vector<uint>& C, const uint T) {
  const uint n = C.size();
  if (!n)
    return {};

  sort(C.begin(), C.end());
  vector<uint> to_ext;
  set<vector<uint>> ret;

  function<void(const uint,const uint)> solve =
    [&](const uint idx, const uint remain) {
    if (!to_ext.empty() && !remain)
      ret.insert(to_ext);

    for (uint i = idx; i < n; ++i) { // backtracking
      if (remain < C[i])
        return;

      to_ext.push_back(C[i]);
      solve(i+1, remain-C[i]);
      to_ext.pop_back();
    }
  };

  solve(0, T);
  return vector<vector<uint>>(ret.begin(), ret.end());
}

/*
Given three vector<string> a, b and c, pick one element from each array if array is not empty. There's no duplicates.
 */
vector<vector<string>> arrayComb(const vector<string>& a,
                                 const vector<string>& b,
                                 const vector<string>& c) {
  vector<string> to_ext;
  const vector<string>* arrs[] = {&a, &b, &c};
  vector<vector<string>> ret;

  function<void(const uint)> solve =
    [&](const uint idx) {
    if (idx == 3) {
      ret.push_back(to_ext);
      return;
    } else if (arrs[idx]->empty()) {
      solve(idx+1);
    } else {
      for (uint i = 0; i < arrs[idx]->size(); ++i) { // backtracking
        to_ext.push_back((*arrs[idx])[i]);
        solve(idx+1);
        to_ext.pop_back();
      }
    }
  };

  solve(0);
  return ret;
}

#if 0
/*
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters is just like on the telephone buttons.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
 */
static map<char,string> dict = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

vector<string> letterComb_recur(const string& digits) {
  const uint len = digits.length();
  if (!len)
    return {};

  vector<string> ret;
  string to_ext = "";

  function<void(const uint)> solve =
    [&](const uint idx) {
    if (idx == len) {
      ret.push_back(to_ext);
      return;
    }

    const auto str = dict[digits[idx]];
    for (const auto c : str) { // backtracking
      to_ext.push_back(c);
      solve(idx+1);
      to_ext.pop_back();
    }
  };

  solve(0);
  return ret;
}

vector<string> letterComb_iter(const string& digits) {
  const uint len = digits.length();
  if (!len)
    return {};

  deque<string> q;
  for (const auto c : dict[digits[0]])
    q.push_back(string(c));

  for (uint i = 1; i < len; ++i) {
    while (!q.empty()) {
      auto front = q.front();
      if (front.length() != i)
        break;

      q.pop_front();
      for (const auto c : dict[digits[i]])
        q.push_back(front+c);
    }
  }

  return {q.begin(), q.end()};
}

/*
Password combinations
eg. origin: facebook
      f -> {f, F}
      a -> (a, A, @)
      c -> {c, C}
      ....
print all combinations.
 */
static map<char,string> dict2 = {
    {'a', "aA@"}, {'b', "bB"}, {'c', "cC"}, {'d', "dD"},
    {'e', "eE"}, {'f', "fF"}, {'g', "gG"}};

vector<string> passwordComb_recur(const std::string& s) {
  const uint len = s.length();
  if (!len)
    return {};

  string to_ext = "";
  vector<string> ret;

  function<void(const uint)> solve =
    [&](const uint idx) {
    if (idx == len) {
      ret.push_back(to_ext);
      return;
    }

    const string str = dict2[s[idx]];
    for (auto c : str) { // backtracking
      to_ext.push_back(c);
      solve(idx+1);
      to_ext.pop_back();
    }
  };

  solve(0);
  return ret;
}

vector<string> passwordComb_iter(const std::string& s) {
  const uint len = s.length();
  if (!len)
    return {};

  deque<string> q;
  for (const auto c : dict2[s[0]])
    q.push_back(string(c));

  for (uint i = 1; i < len; ++i) {
    while (!q.empty()) {
      auto front = q.front();
      if (front.length() != i)
        break;

      q.pop_front();
      for (const auto c : dict2[s[i]])
        q.push_back(front+c);
    }
  }

  return {q.begin(), q.end()};
}
#endif

int main(int argc, char** argv) {
  cout << "Recursive" << endl;
  vector<vector<uint>> res = comb_recur(4, 2); //10, 7);
  for (const auto& i : res) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  cout << "Iterative" << endl;
  res = comb_iter(4, 2); //10, 7);
  for (const auto& i : res) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  vector<uint> nums = {2,3,6,7};
  uint target = 7;
  res = combSum_recur(nums, target);
  cout << "Combinations sum to " << target << ":" << endl;
  for (const auto& i : res) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }

  nums.clear();
  nums = {10,1,2,7,6,1,5};
  target = 8;
  res = uniqueSumComb_recur(nums, target);

  cout << "Unique combinations with sum " << target << ":" << endl;
  for (const auto& i : res) {
    for (const auto j : i)
      cout << j << " ";
    cout << endl;
  }
/*
  string digits = "23"; //"12345";
  vector<string> res2 = letterComb_recur(digits);
  for (const auto& i : res2) {
    cout << i << " ";
  }
  cout << endl;

  res2 = letterComb_iter(digits);
  for (const auto& i : res2) {
    cout << i << " ";
  }
  cout << endl;
 */
  return 0;
}
