#include <iostream>

using namespace std;

/*
Given an integers array A, define B[i] = A[0] * ... * A[i-1] * A[i+1] * ... * A[n-1], calculate B WITHOUT divide operation.
 */
int* productWOSelf(const int A[], const uint n) {
  if (!n) {
    return nullptr;
  }

  int* B = new int[n];
  for (uint i = 0; i < n; ++i) {
    B[i] = 1;

    for (uint j = 0; j < i; ++j) {
      B[i] *= A[j];
    }
    for (uint j = i+1; j < n; ++j) {
      B[i] *= A[j];
    }
  }

  return B;
}

/*
Given a sequence of non-negative integers, find the subsequence of length 3 having maximum product
with the numbers of the subsequence being in ascending order.

Time complexity: O(nLogn).
First create two arrays LSL[] and LGR[] of size n each where n is number of elements in input array arr[].
The main task is to fill two arrays LSL[] and LGR[]. Once we have these two arrays filled,
all we need to find maximum product LSL[i]*a[i]*LGR[i] where 0 < i < n-1
(Note that LSL[i] doesn't exist for i = 0 and LGR[i] doesn't exist for i = n-1).
We can fill LSL[] in O(nLogn) time. The idea is to use a Balanced Binary Search Tree like AVL.
We start with empty AVL tree, insert the leftmost element in it. Then we traverse the input array
starting from the second element to second last element. For every element currently being traversed,
we find the floor of it in AVL tree. If floor exists, we store the floor in LSL[], otherwise we store NULL.
After storing the floor, we insert the current element in the AVL tree. We can fill LGR[] in O(n) time.
The idea is similar to "replace with next biggest" problem. We traverse from right side
and keep track of the largest element. If the largest element is greater than current element,
we store it in LGR[], otherwise we store NULL. Finally, we run a O(n) loop and return maximum of LSL[i]*a[i]*LGR[i].
Overall complexity of this approach is O(nLogn)+O(n)+O(n) which is O(nLogn). Auxiliary space required is O(n).
Note that we can avoid space required for LSL, we can find and use LSL values in final loop.
 */
int main(int argc, char** argv) {
  int A[] = {1, 2, 3};
  int* B = productWOSelf(A, 3);

  for (uint i = 0; i < 3; ++i) {
    cout << B[i] << " ";
  }
  cout << endl;

  return 0;
}
