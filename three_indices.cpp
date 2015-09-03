/*
Given an array of integers, find 3 indices i, j and k such that i < j < k and a[i] < a[j] < a[k].
Best possible is an O(n) algorithm.
 */
#include <iostream>
#include <vector>

using namespace std;

struct Indices {
  int32_t first, second, third;
};

Indices threeIndices(const int32_t a[], const uint32_t n) {
  if (n < 3)
    return {};

  Indices ret {0,-1,0};
  int32_t min_idx = 0;

  for (uint32_t i = 1; i < n; ++i) {
    if (ret.second < 0) {
      if (a[i] < a[min_idx]) {
        min_idx = i;
        ret.first = i;
      } else if (a[i] > a[min_idx]) {
        ret.second = i;
      }
    } else {
      if (a[i] > a[ret.second]) { // found i,j,k
        ret.third = i;
        return ret;
      } else if (a[i] > a[ret.first]) {
        ret.second = i;
      } else if (a[i] > a[min_idx]) {
        ret.first = min_idx;
        ret.second = i;
      } else if (a[i] < a[min_idx]) {
        min_idx = i;
      }
    }
  }

  return {-1,-1,-1};
}

int main(int argc, char** argv) {
  int32_t a[] = {2,3,1,4};
  Indices res = threeIndices(a, 4);
  cout << res.first << " " << res.second << " " << res.third << endl;

  return 0;
}
