/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent,
with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's,
then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?
 */
#include <iostream>

using namespace std;

void sortColors(uint8_t A[], const uint32_t n) {
  if (!n)
    return;

  uint32_t l_ptr = 0, m_ptr = 0, r_ptr = n-1;

  while (m_ptr <= r_ptr) {
    if (A[m_ptr] == 1) // white
      ++m_ptr;
    else if (!A[m_ptr]) { // red
      if (A[m_ptr] != A[l_ptr])
        swap(A[l_ptr++], A[m_ptr++]);
    }
    else if (A[m_ptr] == 2) { // blue
      if (A[m_ptr] != A[r_ptr])
        swap(A[m_ptr], A[r_ptr--]);
    }
  }
}

int main(int argc, char** argv) {
  uint8_t a[] = {1,2,0,0,2,2,2,1,0,1,2};
  const uint32_t n = 11; //sizeof(a)/sizeof(uint8_t);
  sortColors(a, n);

  for (uint32_t i = 0; i < n; ++i)
    cout << a[i] << " ";

  cout << endl;
  return 0;
}
