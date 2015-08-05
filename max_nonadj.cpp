/*
Given an array of whose elements are positive numbers. Find the maximum sum of a subsequence with all the constraint that no two numbers in the sequence should be adjacent in the array.
3 2 7 10 should return 13 (13 = 3 + 10)
3 2 5 10 7 should return 15 (15 = 3 + 5 + 7)
1 5 4 3 2 should return 8 (8 = 5 + 3)
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

uint32_t maxNoAdjSubseqSum2(const vector<uint32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return 0;

  uint32_t ret = 0;

  function<void(const uint32_t,uint32_t)> solve =
    [&](const uint32_t idx, uint32_t curr_sum) {
    if (idx >= n) {
      return;
    }

    curr_sum += a[idx];
    ret = max(ret, curr_sum);
    for (uint32_t i = idx+2; i < n; ++i) {
      solve(i, curr_sum);
    }
  };

  for (uint32_t i = 0; i < n; ++i)
    solve(i, 0);

  return ret;
}

uint32_t maxNoAdjSubseqSum(const vector<uint32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return 0;

  uint32_t incl = a[0], excl = 0;
  uint32_t excl_new;

  for (uint32_t i = 1; i < n; ++i) {
    /* current max excluding i */
    excl_new = (incl > excl) ? incl: excl;

    /* current max including i */
    incl = excl+a[i];
    excl = excl_new;
  }

  /* return max of incl and excl */
  return ((incl > excl) ? incl : excl);
}

int main(int argc, char** argv) {
  vector<uint32_t> a = {3,2,7,10};
  cout << maxNoAdjSubseqSum(a) << endl;
  a = {3,2,5,10,7};
  cout << maxNoAdjSubseqSum(a) << endl;
  a = {1,5,4,3,2};
  cout << maxNoAdjSubseqSum(a) << endl;

  return 0;
}
