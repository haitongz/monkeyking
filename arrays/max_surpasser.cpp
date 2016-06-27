/*
Given an array, return max number of surpassers.

A surpasser of a[i] is element a[j], while j > i and a[j] > a[i].
 */
#include <iostream>
#include <functional>
#include <map>

using namespace std;

uint maxSurpasserNo(const int a[], const uint n) {
  if (!n) {
    return 0;
  }

  int tmp[n];
  map<int,uint> mem;
  uint ret = 0;

  function<void(const uint,const uint, const uint)> merge =
    [&](const uint left, const uint mid, const uint right) {
    if (left >= right) {
      return;
    }

    uint32_t l = mid, r = right, curr = right;
    while (l >= left && r > mid) {
      if (a[l] < a[r]) {
        mem[a[l]] += r-mid;
        ret = max(ret, mem[a[l]]);
        tmp[curr--] = a[l--];
      } else {
        tmp[curr--] = a[r--];
      }
    }

    while (l >= left) {
      tmp[curr--] = a[l--];
    }

    while (r > mid) {
      tmp[curr--] = a[r--];
    }

    for (uint i = left; i < right+1; ++i) {
      tmp[i] = a[i];
    }
  };

  function<void(const uint,const uint)> sort =
    [&](const uint left, const uint right) {
    if (left >= right)
      return;

    const uint32_t mid = left + (right-left)/2;
    sort(left, mid);
    sort(mid+1, right);
    merge(left, mid, right);
  };

  sort(0, n-1);
  return ret;
}

int main(int argc, char** argv) {
  int a[] = {2,1,2,1,5,4,5,5};
  cout << maxSurpasserNo(a, 8) << endl;

  return 0;
}
