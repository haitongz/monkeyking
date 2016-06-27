#include <iostream>

using namespace std;

/*
Given an array of numbers between 0 and 9, find k-th smallest number.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
 */
int8_t kthSmallest(const uint8_t A[], const uint32_t n, const int32_t k) {
  if (!n || !k)
    return -1;

  uint32_t cnt[10];
  uint8_t existing = 0;

  for (uint32_t i = 0; i < n; ++i) {
    if (!cnt[A[i]])
      ++existing;

    ++cnt[A[i]];
  }

  if (existing < k) {
    cerr << "There are less than k numbers!" << endl;
    return -1;
  }

  for (uint8_t i = 0; i < 10; ++i) {
    if (cnt[i]) {
      if (--k > 0)
        continue;
      else
        return i;
    }
  }
}

/*
Follow up: what if integers can be of any value?
 */
int32_t kthSmallest(int32_t A[], const uint32_t n, const uint32_t k) {
  if (!n || !k)
    return -1;

  quickSort(A);

}

int main(int argc, char** argv) {
}
