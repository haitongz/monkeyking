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
#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<vector<uint32_t>> comb_iter(const uint32_t n, const uint32_t k) {
  if (!n || !k || k > n) { // k cannot be bigger than n
    return {};
  } else if (k == 1) {
    vector<vector<uint32_t>> ret;
    for (uint32_t i = 1; i < n+1; ++i)
      ret.push_back({i});

    return ret;
  }

  deque<vector<uint32_t>> q;
  for (uint32_t i = 1; i < n+1; ++i)
    q.push_back({i});

  vector<vector<uint32_t>> ret;

  while (!q.empty()) {
    vector<uint32_t>& list = q.front();
    if (list.size() == k) {
      res.push_back(list);
    } else {
      for (uint32_t i = list.back()+1; i < n+1; ++i) {
        vector<uint32_t> next_list(list);
        next_list.push_back(i);
        q.push_back(next_list);
      }
    }
    q.pop_front();
  }

  return res;
}

vector<vector<uint32_t>> comb_recur(const uint32_t n, const uint32_t k) {
  if (!n || !k || k > n) // k cannot no bigger than n
    return {};

  vector<vector<uint32_t>> ret;
  vector<uint32_t> to_ext;

  function<void(const uint32_t,const uint32_t)> backtrack =
    [&](const uint32_t remaining, const uint32_t idx) {
    if (!to_ext.empty() && !remaining) {
      ret.push_back(to_ext);
      return;
    }

    for (uint32_t i = idx; i < n+1; ++i) {
      to_ext.push_back(i);
      backtrack(remaining-1, i+1);
      to_ext.pop_back();
    }
  };

  backtrack(k, 1);
  return ret;
}

/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

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
vector<vector<uint32_t>> combSum_recur(vector<uint32_t>& C, const uint32_t T) {
  const uint32_t n = C.size();
  if (!n)
    return {};

  sort(C.begin(), C.end());

  vector<vector<uint32_t>> ret;
  vector<uint32_t> to_ext;

  function<void(const uint32_t,const uint32_t)> backtrack =
    [&](const uint32_t curr_sum, const uint32_t idx) {
    if (curr_sum == T) {
      ret.push_back(to_ext);
      return;
    }

    if (idx == n || curr_sum > T)
      return;

    for (uint32_t i = idx; i < n; ++i) {
      to_ext.push_back(C[i]);
      backtrack(curr_sum+C[i], i);
      to_ext.pop_back();
    }
  };

  backtrack(0, 0);
  return ret;
}

/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sum to T.

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
vector<vector<uint32_t>> uniqueSumComb_recur(vector<uint32_t>& C, const uint32_t T) {
  const uint32_t n = C.size();
  if (!n)
    return {};

  sort(C.begin(), C.end());
  vector<uint32_t> to_ext;
  set<vector<uint32_t>> ret;

  function<void(const uint32_t,const uint32_t)> backtrack =
    [&](const uint32_t remaining, const uint32_t idx) {
    if (!to_ext.empty() && !remaining)
      ret.insert(to_ext);

    for (uint32_t i = idx; i < n; ++i) {
      if (remaining < C[i])
        return;

      to_ext.push_back(C[i]);
      backtrack(remaining-C[i], i+1);
      to_ext.pop_back();
    }
  };

  backtrack(T, 0);
  return vector<vector<uint32_t>>(ret.begin(), ret.end());
}

/*
Given a digit string, return all possible letter combinations that the number could represent.
A mapping of digit to letters is just like on the telephone buttons.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
 */
vector<string> letterComb_recur(const string& digits) {
  const uint32_t len = digits.length();
  if (!len)
    return {};

  static unordered_map<char,string> dict = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

  vector<string> ret;
  string to_ext = "";

  function<void(const uint32_t)> backtrack =
    [&](const uint32_t idx) {
    if (idx == len) {
      ret.push_back(to_ext);
      return;
    }

    auto str = dict[digits[idx]];
    for (auto c : str) {
      to_ext.push_back(c);
      backtrack(idx+1);
      to_ext.pop_back();
    }
  };

  backtrack(0);
  return ret;
}

vector<string> letterComb_iter(const string& digits) {
  const uint32_t len = digits.length();
  if (!len)
    return {};

  static unordered_map<char,string> dict = {
    {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
    {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

  deque<string> q;
  for (auto c : dict[digits[0]])
    q.push_back(string(c));

  for (uint32_t i = 1; i < len; ++i) {
    while (!q.empty()) {
      auto front = q.front();
      if (front.length() != i)
        break;

      q.pop_front();
      for (auto c : dict[digits[i]])
        q.push_back(front+c);
    }
  }

  return {q.begin(), q.end()};
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

  function<void(const uint8_t)> backtrack = [&](const uint8_t idx) {
    if (idx == 3) {
      ret.push_back(to_ext);
      return;
    } else if (arrs[idx]->empty()) {
      backtrack(idx+1);
    } else {
      for (uint32_t i = 0; i < arrs[idx]->size(); ++i) {
        to_ext.push_back((*arrs[idx])[i]);
        backtrack(idx+1);
        to_ext.pop_back();
      }
    }
  };

  backtrack(0);
  return ret;
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
vector<string> passwordComb_recur(const std::string& s) {
  const uint32_t len = s.length();
  if (!len)
    return {};

  static unordered_map<char,string> dict = {
    {'a', "aA@"}, {'b', "bB"}, {'c', "cC"}, {'d', "dD"},
    {'e', "eE"}, {'f', "fF"}, {'g', "gG"}};

  string to_ext = "";
  vector<string> ret;

  function<void(const uint32_t)> backtrack =
    [&](const uint32_t idx) {
    if (idx == len) {
      ret.push_back(to_ext);
      return;
    }

    const string str = dict[s[idx]];
    for (auto c : str) {
      to_ext.push_back(c);
      backtrack(idx+1);
      to_ext.pop_back();
    }
  };

  backtrack(0);
  return ret;
}

vector<string> passwordComb_iter(const std::string& s) {
  const uint32_t len = s.length();
  if (!len)
    return {};

  static unordered_map<char,string> dict = {
    {'a', "aA@"}, {'b', "bB"}, {'c', "cC"}, {'d', "dD"},
    {'e', "eE"}, {'f', "fF"}, {'g', "gG"}};

  deque<string> q;
  for (auto c : dict[s[0]])
    q.push_back(string(c));

  for (uint32_t i = 1; i < len; ++i) {
    while (!q.empty()) {
      auto front = q.front();
      if (front.length() != i)
        break;

      q.pop_front();
      for (auto c : dict[digits[i]])
        q.push_back(front+c);
    }
  }

  return {q.begin(), q.end()};
}

int main(int argc, char** argv) {
  cout << "Recursive" << endl;
  vector<vector<uint32_t>> res = comb_recur(4, 2); //10, 7);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  cout << "Iterative" << endl;
  res = comb_iter(4, 2); //10, 7);
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  vector<uint32_t> nums = {2,3,6,7};
  uint32_t target = 7;
  res = combSum_recur(nums, target);
  cout << "Combinations sum to " << target << ":" << endl;
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  nums.clear();
  nums = {10,1,2,7,6,1,5};
  target = 8;
  res = uniqueSumComb_recur(nums, target);

  cout << "Unique combinations with sum " << target << ":" << endl;
  for (auto& i : res) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  string digits = "23"; //"12345";
  vector<string> res2 = letterComb_recur(digits);
  for (auto& i : res2) {
    cout << i << " ";
  }
  cout << endl;

  res2 = letterComb_iter(digits);
  for (auto& i : res2) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
