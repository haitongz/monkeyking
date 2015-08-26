/*
Given a function int f(unsigned int x) which takes a non-negative integer x as input and returns an integer as output.
The function is monotonically increasing with respect to value of x, i.e., the value of f(x+1) is greater than f(x) for
every input x. Find the value 'n' where f() becomes positive for the first time. Since f() is monotonically increasing,
values of f(n+1), f(n+2),¿ must be positive and values of f(n-2), f(n-3), .. must be negative.

Find n in O(logn) time, you may assume that f(x) can be evaluated in O(1) time for any input x.
 */
#include <iostream>

int f(int x) { return (x*x - 10*x - 20); }

// Returns the value x where above function f() becomes positive first time.
int findFirstPositive() {
  // When first value itself is positive
  if (f(0) > 0)
    return 0;

  // Find 'high' for binary search by repeated doubling
  uint32_t i = 1;
  while (f(i) <= 0)
    i = i*2;

  return binarySearch(i/2, i);
}

// Searches first positive value of f(i) where low <= i <= high
int binarySearch(int low, int high)
{
  if (high >= low) {
    int mid = low + (high - low)/2; /* mid = (low + high)/2 */

    // If f(mid) is greater than 0 and one of the following two conditions is true:
    // a) mid is equal to low
    // b) f(mid-1) is negative
    if (f(mid) > 0 && (mid == low || f(mid-1) <= 0))
      return mid;

    // If f(mid) is smaller than or equal to 0
    if (f(mid) <= 0)
      return binarySearch((mid + 1), high);
    else // f(mid) > 0
      return binarySearch(low, (mid -1));
  }

  /* Return -1 if there is no positive value in given range */
  return -1;
}

int main() {
  printf("The value n where f() becomes positive first is %d",
          findFirstPositive());
  return 0;
}
