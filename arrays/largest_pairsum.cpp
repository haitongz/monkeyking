/*
Given an unsorted array, find the largest pair sum in it.
 */
#include <iostream>

using namespace std;

int largestPairSum(const int a[], const uint n) {
  if (n < 2) {
    throw exception();
  } else if (n == 2) {
    return a[0]+a[1];
  }

  int biggest = max(a[0], a[1]);
  int second = min(a[0], a[1]);
  for (uint i = 2; i < n; ++i) {
    if (a[i] >= biggest) { // ">=": we need to handle another "biggest" element
      second = biggest;
      biggest = a[i];
    } else if (a[i] > second) {
      second = a[i];
    }
  }

  return biggest+second;
}

int main(int argc, char** argv) {
  int a[] = {0,4,4,0,0,2,4,4};
  cout << "Largest pair sum is: " << largestPairSum(a, 8) << endl;

  return 0;
}
