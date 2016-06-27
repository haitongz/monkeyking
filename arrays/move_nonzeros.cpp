#include <iostream>
// #include <vector>

using namespace std;

/*
Given an array of integers. Move all non-zero elements to the left of all zero elements.
 */
void moveNonZeros(int a[], const uint n) {
  if (!n) {
    return;
  }

  for (uint i = 0, flag = 0; i < n; ++i) {
    if (a[i]) {
      swap(a[i], a[flag++]);
    }
  }

  for (uint i = 0; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;
}

/*
Follow up:
Put all non-zero elements at left of array, minimum changes to this array, left-most elements can be anything,
returns number of non-zero elements.
 */
uint moveNonZeros_2(int a[], const uint n) { // issue: not all non-zero are at left
  if (!n) {
    return 0;
  }

  uint ret = 0;
  uint left = 0, right = n-1;

  while (left <= right) {
    while (!a[left]) {
      ++left;
    }

    if (left > right) {
      break;
    }

    if (!a[right]) {
      a[left++] = 0;
    }

    ++ret;
    --right;
  }

  return ret;
}

int main(int argc, char** argv) {
  int a[] = {1,0,2,3,4,0};
  moveNonZeros(a, 6);

  int b[] = {1,0,2,3,4,0};
  cout << "There are " << moveNonZeros_2(b, 6) << " non-zero elements!" << endl;

  return 0;
}
