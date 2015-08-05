#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

using namespace std;

/*
Print all factors of the product of a given list of distinct primes.
Example:
Input: 2 3 7
Output: 1 2 3 6 7 14 21 42
 */
vector<uint32_t> allFactors_iter(const vector<uint32_t>& primes) {
  const uint32_t n = primes.size();
  if (!n)
    return {};
  else if (n == 1) {
    vector<uint32_t> res = {1,primes[0]};
    return res;
  }

  vector<uint32_t> res = {1};
  vector<uint32_t> ext;
  for (uint32_t i = 0; i < n; ++i) {
    const uint32_t cp = ext.size();
    ext.push_back(primes[i]);

    for (uint32_t j = 0; j < cp; ++j) {
      ext.push_back(ext[j]*primes[i]);
    }
  }

  res.insert(res.end(), ext.begin(), ext.end());
  return res;
}

vector<uint32_t> allFactors_recur(const vector<uint32_t>& primes) {
  const uint32_t n = primes.size();
  if (!n)
    return {};

  vector<uint32_t> res;

  function<void(const uint32_t,const uint32_t)> dfs =
    [&](const uint32_t curr, const uint32_t idx) {
    if (idx == n) {
      res.push_back(curr);
      return;
    }

    dfs(curr, idx+1);
    dfs(curr*primes[idx], idx+1);
  };

  dfs(1, 0);
  sort(res.begin(), res.end());
  return res;
}

/*
Print all unique combination of factors (except 1) of a given number.
For example:
Input: 12
Output: [[2, 2, 3], [2, 6], [3, 4]]
Input: 15
Output: [[3, 5]]
Input: 28
Output: [[2, 2, 7], [2, 14], [4, 7]]
 */
vector<vector<uint32_t>> factorsComb_recur(const uint32_t n) {
  if (n <= 1)
    return {{}};

  vector<vector<uint32_t>> res;
  vector<uint32_t> to_ext;

  function<void(const uint32_t)> backtrack = [&](const uint32_t num) {
    const uint32_t last = to_ext.empty() ? 2 : to_ext.back();
    for (uint32_t i = last; i < num; ++i) {
      if (num%i != 0)
        continue;

      to_ext.push_back(i);
      backtrack(num/i);
      to_ext.pop_back();
    }

    if (!to_ext.empty() && num >= last) {
      to_ext.push_back(num);
      res.push_back(to_ext);
      to_ext.pop_back();
    }
  };

  backtrack(n);
  return res;
}

int main(int argc, char** argv) {
  vector<uint32_t> primes = {2, 3, 7};
  vector<uint32_t> res = allFactors_iter(primes);
  for (auto i : res)
    cout << i << " ";
  cout << endl;

  res = allFactors_recur(primes);
  for (auto i : res)
    cout << i << " ";
  cout << endl;

  vector<vector<uint32_t>> res2 = factorsComb_recur(12);
  for (auto i : res2) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  return 0;
}
