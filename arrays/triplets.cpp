#include <iostream>
#include <algorithm>

using namespace std;

/*
Given an array of integers, write a function that returns true if there is a triplet (a, b, c) that satisfies a2 + b2 = c2.
 */
bool isTriplet(vector<int32_t>& a) { // O(n^2)
  const uint32_t n = a.size();
  if (n < 3)
    return false;

  for (auto& i : a)
    i *= i;

  // Sort array elements
  sort(a.begin(), a.end());

  // Now fix one element one by one and find the other two elements
  for (uint32_t i = n-1; i > 1; --i) {
    // To find the other two elements, start two index variables from two corners of the array and move them toward each other
    uint32_t l = 0; // index of the first element in a[0..i-1]
    uint32_t r = i-1; // index of the last element in a[0..i-1]
    while (l < r) {
      // A triplet found
      if (a[l]+a[r] == a[i])
        return true;

      // Else either move 'l' or 'r'
      (a[l]+a[r] < a[i]) ? ++l : --r;
    }
  }

  // If we reach here, then no triplet found
  return false;
}

/*
Given an array of n integers, find the 3 elements such that a[i] < a[j] < a[k] and i < j < k in O(n) time. If there are
multiple such triplets, then print any one of them.
 */
struct Triplet {
  uint32_t i, j, k; // indices
};

/*
1) Create an auxiliary array smaller[0..n-1]. smaller[i] should store the index of a number which is smaller than a[i] and
is on left side of a[i]. smaller[i] should contain -1 if there is no such element.
2) Create another auxiliary array greater[0..n-1]. greater[i] should store the index of a number which is greater than a[i]
and is on right side of a[i]. greater[i] should contain -1 if there is no such element.
3) Finally traverse both smaller[] and greater[] and find the index i for which both smaller[i] and greater[i] are not -1.
 */
Triplet findTriplet(const int32_t a[], const uint32_t n) {
  if (n < 3)
    throw exception();

  uint32_t max = n-1; // Index of maximum element from right side
  uint32_t min = 0;   // Index of minimum element from left side

  // Create an array that will store index of a smaller element on left side. If there is no smaller element on left side,
  // then smaller[i] will be -1.
  int32_t smaller[n];
  smaller[0] = -1;  // first entry will always be -1
  for (uint32_t i = 1; i < n; ++i) {
    if (a[i] <= a[min]) {
      min = i;
      smaller[i] = -1;
    } else
      smaller[i] = min;
  }

  // Create another array that will store index of a greater element on right side. If there is no greater element on right
  // side, then greater[i] will be -1.
  int32_t greater[n];
  greater[n-1] = -1;  // last entry will always be -1
  for (int32_t i = n-2; i >= 0; i--) {
    if (a[i] >= a[max]) {
      max = i;
      greater[i] = -1;
    } else
      greater[i] = max;
  }

  // Now find a number which has both a greater number on right side and smaller number on left side
  for (uint32_t i = 0; i < n; ++i) {
    if (smaller[i] != -1 && greater[i] != -1) {
      return {smaller[i], i, greater[i]};
    }
  }

  // If we reach number, then there are no such 3 numbers
  // printf("No such triplet found");
   // Free the dynamically alloced memory to avoid memory leak
//   delete [] smaller;
  // delete [] greater;

  return {};
}
