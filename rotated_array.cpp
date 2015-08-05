#include <iostream>
#include <functional>

using namespace std;

/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand. (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).  You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.

O(logn)
 */
int32_t searchInRotated(const int32_t A[], const uint32_t n, const int32_t target) {
  if (!n)
    return -1;

  function<int32_t(const int32_t,const int32_t)> solve =
    [&](const int32_t left, const int32_t right) {
    if (left > right)
      return -1;

    if (A[left] == target)
      return left;
    else if (A[right] == target)
      return right;

    const int32_t mid = left+(right-left)/2;
    if (target == A[mid])
      return mid;

    if ((A[left] <= A[mid] && A[left] < target && target < A[mid]) || // normal case
        (A[left] > A[mid] && target < A[mid]) || // pivot is in left half and target is small
        (A[left] > A[mid] && target > A[right])) // pivot is in right half and target is big
      return solve(left, mid-1);
    else
      return solve(mid+1, right);
  };

  return solve(0, n-1);
}

/*
What if duplicates are allowed? [1,3,1,1,1], 3
Would this affect the run-time complexity? How and why?
Write a function to determine if a given target is in the array.
 */
bool existsInRotated(const int32_t A[], const uint32_t n, const int32_t target) { // O(2*log(n))
  if (!n)
    return false;

  function<bool(const int32_t,const int32_t)> dfs =
    [&](const int32_t left, const int32_t right) {
    if (left > right)
      return false;

    if (A[left] == target)
      return true;
    else if (A[right] == target)
      return true;

    const int32_t mid = left+(right-left)/2;
    if (A[mid] == target)
      return true;

    if ((A[left] <= A[mid] && A[left] < target && target < A[mid]) || // normal case
        (A[left] > A[mid] && A[mid] > target) || // rotate point is in left half and target is small
        (A[left] > A[mid] && target > A[right])) // rotate point is in right half and target is big
      return dfs(left, mid-1);
    else
      return dfs(mid+1, right);
  };

  return dfs(0, n-1);
}

/*
Find minimum element in rotated array
 */
int32_t minInRotated(const int32_t A[], const uint32_t n) {
  if (!n)
    throw exception();

  function<int32_t(const int32_t,const int32_t)> dfs =
    [&](const int32_t left, const int32_t right) {
    if (left > right)
      return A[0];
    else if (right == left) // only one element
      return A[left];

    const int32_t mid = left+(right-left)/2;

    // Check if element (mid+1) is minimum element. Consider cases like {3, 4, 5, 1, 2}
    if (A[mid+1] < A[mid])
      return A[mid+1];

    // Check if mid itself is minimum element
    if (A[mid] < A[mid-1])
      return A[mid];

    // Decide whether we need to go to left half or right half
    return (A[right] > A[mid]) ?
      dfs(left, mid-1) : dfs(mid+1, right);
  };

  return dfs(0, n-1);
}

/*
Write a function rotate(ar[], d, n) that rotates arr[] of size n by d elements.
Divide the array in different sets where number of sets is equal to GCD of n and d and move the elements within sets.

Time complexity: O(n)
Auxiliary Space: O(1)
 */
void juggling(vector<int32_t>& a, const uint32_t d) {
  const uint32_t n = a.size();
  if (n <= d)
    return;

  function<uint32_t(const uint32_t,const uint32_t)> gcd =
    [&](const uint32_t a, const uint32_t b) {
    return !b ? a : gcd(b, a%b);
  };

  const uint32_t s = gcd(d, n);
  for (uint32_t i = 0; i < s; ++i) {
    int32_t temp = a[i];
    uint32_t j = i;

    while (true) {
      uint32_t k = j+d;
      if (k >= n)
        k -= n;
      if (k == i)
        break;

      a[j] = a[k];
      j = k;
    }

    a[j] = temp;
  }
}

/*
Let AB are the two parts of the input array where A = arr[0..d-1] and B = arr[d..n-1]. The idea of the algorithm is:
Reverse A to get ArB. // Ar is reverse of A
Reverse B to get ArBr. // Br is reverse of B
Reverse all to get (ArBr) r = BA.

For arr[] = [1, 2, 3, 4, 5, 6, 7], d =2 and n = 7
A = [1, 2] and B = [3, 4, 5, 6, 7]
Reverse A, we get ArB = [2, 1, 3, 4, 5, 6, 7]
Reverse B, we get ArBr = [2, 1, 7, 6, 5, 4, 3]
Reverse all, we get (ArBr)r = [3, 4, 5, 6, 7, 1, 2]
 */
void reversal(vector<int32_t>& a, const uint32_t d) {
  const uint32_t n = a.size();
  if (n <= d)
    return;

  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t start, const uint32_t end) {
    while (start < end) {
      int32_t temp = a[start];
      a[start] = a[end];
      a[end] = temp;
      ++start;
      --end;
    }
  };

  solve(0, d-1);
  solve(d, n-1);
  solve(0, n-1);
}

/*
Initialize A = arr[0..d-1] and B = arr[d..n-1]
1) Do following until size of A is equal to size of B
  a)  If A is shorter, divide B into Bl and Br such that Br is of same length as A. Swap A and Br to change ABlBr into BrBlA. Now A is at its final place, so recur on pieces of B.
  b)  If A is longer, divide A into Al and Ar such that Al is of same length as B Swap Al and B to change AlArB into BArAl. Now B is at its final place, so recur on pieces of A.

2)  Finally when A and B are of equal size, block swap them.
 */
/*This function swaps d elements starting at index fi with d elements starting at index si */
void swap(int32_t a[], const uint32_t fi, const uint32_t si, const uint32_t d) {
  for (uint32_t i = 0; i < d; ++i) {
    int32_t temp = a[fi+i];
    a[fi+i] = a[si+i];
    a[si+i] = temp;
  }
}

void blockswap(int32_t a1[], const uint32_t n1, const uint32_t d1) {
  function<void(int32_t*,const uint32_t,const uint32_t)> solve =
    [&](int32_t* a, const uint32_t n, const uint32_t d) {
    if (!d || n == d)
      return;

    if (n-d == d) { /* number of elements to be rotated is exactly half of array size */
      swap(a, 0, n-d, d);
      return;
    }

    if (d < n-d) { // A is shorter
      swap(a, 0, n-d, d);
      solve(a, d, n-d);
    } else { // B is shorter
      swap(a, 0, d, n-d);
      solve(a+n-d, 2*d-n, d); /*This is tricky*/
    }
  };

  solve(a1, n1, d1);
}

int main(int argc, char** argv) {
  int32_t d[7] = {4,5,6,7,0,1,2};
  int32_t target = 3;
  cout << "Index of number " << target << " in rotated array: " << searchInRotated(d, 7, target) << endl;
  cout << "Number " << target << (existsInRotated(d, 7, target) ? " does " : " does not ") << "exist in rotated array." << endl;

  int32_t a[7] = {1,3,1,1,1};
  target = 1;
  cout << "Number " << target << (existsInRotated(a, 5, target) ? " does " : " does not ") << "exist in rotated array." << endl;
}
