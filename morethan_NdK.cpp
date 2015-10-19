/*
Given an array of size n, find all elements in array that appear more than n/k times.

Given input array {3, 1, 2, 2, 1, 2, 3, 3} and k is 4, then the output should be [2, 3].
Note that size of array is 8 (or n = 8), so we need to find all elements
that appear more than 2 (or 8/4) times. There are two elements that appear more than two times, 2 and 3.
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int32_t>
moreThanNdK(const int32_t a[], const uint32_t n,
            const uint32_t k, map<int32_t,uint32_t>& recs) { // O(nlogk)
  if (n <= k)
    return {};

  uint32_t distinctcnt = 0;
  for (uint32_t i = 0; i < n; ++i) {
    if (recs.count(a[i])) {
      ++recs[a[i]];
      continue;
    }

    if ((distinctcnt = recs.size()) == k-1) {
      for (auto it = recs.begin(); it != recs.end()/* not hoisted */;/* no increment */) {
        if (!--(it->second))
          recs.erase(it++);
        else
          ++it;
      }
    }
    else
      recs[a[i]] = 1;
  }

  distinctcnt = 0;
  for (auto& i : recs)
    i.second = 0;

  vector<int32_t> ret;
  for (uint32_t i = 0; i < n; ++i) {
    if (recs.count(a[i]))
      continue;
    if (++recs[a[i]] > n/k)
      ret[distinctcnt++] = a[i];
  }

  recs.clear();
  return ret;
}

int main(int argc, char** argv) {
  cout << "First test..." << endl;
  int32_t a1[] = {4, 5, 6, 7, 8, 4, 4};
  uint32_t n = sizeof(a1)/sizeof(a1[0]);
  uint32_t k = 3;
  map<int32_t,uint32_t> recs;
  vector<int32_t> res = moreThanNdK(a1, n, k, recs);
  for (const auto& i : res)
    cout << i << " ";
  cout << endl;

  cout << "Second test..." << endl;
  int32_t a2[] = {4, 2, 2, 7};
  n = sizeof(a2)/sizeof(a2[0]);
  k = 3;
 // moreThanNdK(a2, n, k);

  cout << "Third test..." << endl;
  int32_t a3[] = {2, 7, 2};
  n = sizeof(a3)/sizeof(a3[0]);
  k = 2;
 // moreThanNdK(a3, n, k);

  cout << "Fourth test..." << endl;
  int32_t a4[] = {2, 3, 3, 2};
  n = sizeof(a4)/sizeof(a4[0]);
  k = 3;
 // moreThanNdK(a4, n, k);

  return 0;
}
