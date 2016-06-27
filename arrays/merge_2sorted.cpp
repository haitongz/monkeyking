/*
Given two sorted integer arrays A and B, merge B into A as one sorted array.
You may assume that A has enough space (size that is greater or equal to m + n) to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
 */
#include <iostream>

using namespace std;

void merge2Sorted(int A[], const uint m, int B[], const uint n) {
  if (!n) {
    return;
  }

  int i = m-1, j = n-1;

  while (i >= 0 && j >= 0) {
    if (A[i] > B[j]) {
      A[i+j+1] = A[i];
      --i;
    } else {
      A[i+j+1] = B[j];
      --j;
    }
  }

  while (j >= 0) {
    A[j] = B[j];
    --j;
  }
}

int main(int argc, char** argv) {
  int A[] = {1, 5, 9, 0, 0, 0, 0};
  int B[] = {2, 3, 8, 13};
  const uint n = sizeof(B)/sizeof(B[0]);

  merge2Sorted(A, 3, B, n);

  for (const auto i : A) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
