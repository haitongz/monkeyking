/*
Equilibrium index of an array is an index such that the sum of elements at lower indexes is equal to the sum of elements at higher indexes.
 */
#include <iostream>

using namespace std;

/*
1) Get the total sum of the array as sum;
2) Iterate through the array and for each index i, do following.
   a)  Update sum to get the right sum.
       sum -= a[i] // sum is now right sum
   b) If leftsum is equal to sum, then return current index.
   c) leftsum += a[i] // update leftsum for next iteration.
4) return -1 // If we come out of loop without returning then there is no equilibrium index
 */
int32_t equilibrium(const vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return -1;

  int32_t sum = 0;     // initialize sum of whole array
  int32_t leftsum = 0; // initialize leftsum

  for (const auto i : a)
    sum += i;

  for (uint32_t i = 0; i < n; ++i) {
    sum -= a[i]; // sum is now right sum for index i
    if (leftsum == sum)
      return i;

    leftsum += a[i];
  }

  return -1;
}
