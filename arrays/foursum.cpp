#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>
#include <functional>

using namespace std;

static const int MAX_LMT = numeric_limits<int>::has_infinity ?
                           numeric_limits<int>::infinity() : numeric_limits<int>::max();

static const int MIN_LMT = numeric_limits<int>::has_infinity ?
                           -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();

/*
1) Create an auxiliary array aux[] and store sum of all possible pairs in aux[].
The size of aux[] will be n*(n-1)/2 where n is the size of a[].
2) Sort the auxiliary array aux[].
3) Now the problem reduces to find two elements in aux[] with sum equal to X.
We can use method 1 of this post to find the two elements efficiently.
There is following important point to note though. An element of aux[] represents a pair from a[].
While picking two elements from aux[], we must check whether the two elements have an element
of a[] in common. For example, if first element sum of a[1] and a[2], and second element is
sum of a[2] and a[4], then these two elements of aux[] don't represent four distinct elements
of input array a[].
 */
struct PairSum {
  int sum; // pair sum
  uint first, second; // indices (in a[]) of elements in pair
};

vector<vector<uint>>
fourSum(const int a[], const uint n, const int target) { // O(n^2Logn)
  if (n < 4)
    return {};

  const uint size = n*(n-1)/2;
  vector<PairSum> aux(size, PairSum());
  for (uint i = 0, k = 0; i < n-1; ++i) { // generate all possible pairs from a[] and store sums of all possible pairs in aux[]
    for (uint j = i+1; j < n; ++j) {
      aux[k].sum = a[i]+a[j];
      aux[k].first = i;
      aux[k].second = j;
      ++k;
    }
  }

  // Sort the aux[] array using library function for sorting
  sort(aux.begin(), aux.end(), [](const PairSum& a, const PairSum& b) { return a.sum < b.sum; });

  // Function to check if two given pairs have any common element or not
  function<bool(const PairSum&,const PairSum&)> noCommon =
    [&](const PairSum& a, const PairSum& b) {
    return !(a.first == b.first ||
             a.first == b.second ||
             a.second == b.first ||
             a.second == b.second);
  };

  set<vector<uint>> ret;
  // Now start two index variables from two corners of array and move them toward each other.
  uint i = 0;
  int j = size-1;
  while (i < j+1) { //size && j >= 0) {
    int t_sum = aux[i].sum+aux[j].sum;
    if (t_sum == target) {
      if (noCommon(aux[i], aux[j])) {
        vector<uint> indices = {aux[i].first,aux[i].second,aux[j].first,aux[j].second};
        sort(indices.begin(), indices.end());
        ret.insert(indices);
      }
      ++i;
    } else if (t_sum < target)
      ++i;
    else
      --j;
  }

  // sort(ret.begin(), ret.end());
  return {ret.begin(), ret.end()};
}

/*
Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.
Sliding window
 */
int maxSizeKSubarraySum(const vector<int>& a) {
  const uint n = a.size();
}

/*
Given a pair-sum array and size of the original array (n), construct the original array.
A pair-sum array for an array is the array that contains sum of all pairs in ordered form. For example pair-sum array for a[] = {6, 8, 3, 4} is {14, 9, 10, 11, 12, 7}.
In general, pair-sum array for a[0..n-1] is {a[0]+a[1], a[0]+a[2], ..., a[1]+a[2], a[1]+a[3], ..., a[2]+a[3], a[2]+a[4], ..., a[n-2]+a[n-1}.
 */
void construct(int a[], const int pair[], const uint n) {
  if (!n)
    return;

  a[0] = (pair[0]+pair[1]-pair[n-1])/2;
  for (uint i = 1; i < n; ++i)
    a[i] = pair[i-1]-a[0];
}

/*
vector<vector<int> >
zeroSumInSorted_recur(const vector<int>& a, const uint begin, const uint count, const int target) {
  vector<vector<int> > res;
  vector<int> tuple;
  set<int> visited;
  if (count == 2) {
    uint i = begin, j = a.size()-1;
    while (i < j) {
      int sum = a[i]+a[j];
      if (sum == target && visited.find(a[i]) == visited.end()) {
        tuple.clear();
        visited.insert(a[i]);
        visited.insert(a[j]);
        tuple.push_back(a[i]);
        tuple.push_back(a[j]);
        res.push_back(tuple);
        ++i;
        --j;
      } else if (sum < target) {
        ++i;
      } else {
        --j;
      }
    }
  } else {
    for (uint i = begin; i < a.size(); ++i) {
      if (visited.find(a[i]) == visited.end()) {
        visited.insert(a[i]);
        vector<int> sub_res = zeroSumInSorted_recur(a, i+1, count-1, target-a[i]);
        if (!sub_res.empty()) {
          for (uint j = 0; j < sub_res.size(); ++j) {
            sub_res[j].insert(sub_res[j].begin(), a[i]);
          }
          res.insert(res.end(), sub_res.begin(), sub_res.end());
        }
      }
    }
  }
  return res;
}
vector<int> threeSum3(const vector<int>& a) {
  sort(a.begin(), num.end());
  return zeroSumInSorted(a, 0, 3, 0);
}
vector<int> fourSum(vector<int>& a, const int target) {
  sort(a.begin(), a.end());
  return zeroSumInSorted(a, 0, 4, target);
}
*/
/*
Given a sorted array (sorted in non-decreasing order) of positive numbers,
find the smallest positive integer value that cannot be represented as sum of elements
of any subset of given set. Expected time complexity is O(n).

If the current number is bigger than the smallest number you can't make so far,
then you know the smallest number you can't make - it's the one you've got recorded, and you're done.
Otherwise, the current number is smaller than the smallest number you can't make.
The claim is that you can indeed make this number. Right now, you know the smallest number
you can't make with the first k elements of the array (call it candidate) and are now looking
at value a[k]. The number candidate-a[k] therefore must be some number that you can indeed make
with the first k elements of the array, since otherwise candidate-a[k] would be a smaller number
than the smallest number you allegedly can't make with the first k numbers in the array.
Moreover you can make any number in the range candidate to candidate+a[k], inclusive,
because you can start with any number in the range from 1 to a[k], inclusive,
and then add candidate-1 to it. Therefore, set candidate to candidate+a[k] and increment k.
 */
uint smallestUnrepresentable(const uint a[], const uint n) {
  if (!n)
    throw exception();

  uint ret = 1;

  // Traverse the array and increment 'ret' if a[i] is smaller than or equal to 'ret'.
  for (uint i = 0; i < n && a[i] <= ret; ++i)
    ret += a[i];

  return ret;
}

/*
Given two sorted arrays such the arrays may have some common elements. Find the sum of the maximum sum path
to reach from beginning of any array to end of any of the two arrays. We can switch from one array to
another array only at common elements.
Expected time complexity is O(m+n) where m is the number of elements in a1[] and n is the number of
elements in a2[].
 */
int maxPathSum(int a1[], int a2[], const uint m, const uint n) {
  int ret = 0, sum1 = 0, sum2 = 0;
  uint i = 0, j = 0;

  // Below 3 loops are similar to merge in merge sort
  while (i < m && j < n) {
    // Add elements of ar1[] to sum1
    if (a1[i] < a2[j])
      sum1 += a1[i++];
    else if (a1[i] > a2[j]) // Add elements of ar2[] to sum2
      sum2 += a2[j++];
    else { // we reached a common point
      // Take the maximum of two sums and add to result
      ret += max(sum1, sum2);

      // Update sum1 and sum2 for elements after this intersection point
      sum1 = 0, sum2 = 0;

      // Keep updating result while there are more common elements
      while (i < m && j < n && a1[i] == a2[j]) {
        ret += a1[i];
        ++i;
        ++j;
      }
    }
  }

  // Add remaining elements of a1[]
  while (i < m)
    sum1 += a1[i++];
  // Add remaining elements of ar2[]
  while (j < n)
    sum2 += a2[j++];
  // Add maximum of two sums of remaining elements
  ret += max(sum1, sum2);

  return ret;
}

/*
Given an array of whose elements are positive numbers. Find the maximum sum of a subsequence with all
the constraint that no two numbers in the sequence should be adjacent in the array.
3 2 7 10 should return 13 (13 = 3 + 10)
3 2 5 10 7 should return 15 (15 = 3 + 5 + 7)
1 5 4 3 2 should return 8 (8 = 5 + 3)
 */
uint maxNoAdjSubseqSum(uint a[], const uint n) {
  if (!n)
    return 0;

  uint incl = a[0], excl = 0;
  uint excl_new;

  for (uint i = 1; i < n; ++i) {
    /* current max excluding i */
    excl_new = (incl > excl) ? incl: excl;

    /* current max including i */
    incl = excl+a[i];
    excl = excl_new;
  }

  /* return max of incl and excl */
  return ((incl > excl) ? incl : excl);
}

uint maxNoAdjSubseqSum2(uint a[], const uint n) {
  if (!n)
    return 0;

  uint ret = 0;

  function<void(const uint,uint)> solve =
    [&](const uint idx, uint curr_sum) {
    if (idx >= n) {
      return;
    }

    curr_sum += a[idx];
    ret = max(ret, curr_sum);
    for (uint i = idx+2; i < n; ++i) {
      solve(i, curr_sum);
    }
  };

  for (uint i = 0; i < n; ++i)
    solve(i, 0);

  return ret;
}

/*
Equilibrium index of an array is an index such that the sum of elements at lower indices is equal to the
sum of elements at higher indices.
 */
/*
1) Get the total sum of the array as sum;
2) Iterate through the array and for each index i, do following.
   a)  Update sum to get the right sum.
       sum -= a[i] // sum is now right sum
   b) If leftsum is equal to sum, then return current index.
   c) leftsum += a[i] // update leftsum for next iteration.
4) return -1 // If we come out of loop without returning then there is no equilibrium index
 */
int equilibrium(int a[], const uint n) {
  if (!n)
    return -1;

  int sum = 0;     // initialize sum of whole array
  int leftsum = 0; // initialize leftsum

  for (uint i = 0; i < n; ++i)
    sum += a[i];

  for (uint i = 0; i < n; ++i) {
    sum -= a[i]; // sum is now right sum for index i
    if (leftsum == sum)
      return i;

    leftsum += a[i];
  }

  return -1;
}

/*
Given n numbers (both +ve and -ve), arranged in a circle, fnd the maximum sum of consecutive number.
 */
// Standard Kadane's algorithm to find maximum subarray sum
// See http://www.geeksforgeeks.org/archives/576 for details
int kadane(const int a[], const uint n) {
  int max_so_far = 0, max_ending_here = 0;

  for (uint i = 0; i < n; ++i) {
    max_ending_here += a[i];
    if (max_ending_here < 0)
      max_ending_here = 0;
    max_so_far = max(max_so_far, max_ending_here);
  }

  return max_so_far;
}

int maxCircularSum(int a[], const uint n) {
  // Case 1: get the maximum sum using standard kadane's algorithm
  int max_kadane = kadane(a, n);

  // Case 2: Now find the maximum sum that includes corner elements.
  int max_wrap = 0;
  for (uint i = 0; i < n; ++i) {
    max_wrap += a[i]; // Calculate array-sum
    a[i] = -a[i];  // invert the array (change sign)
  }

  // max sum with corner elements will be: array-sum - (-max subarray sum of inverted array)
  max_wrap += kadane(a, n);

  // The maximum circular sum will be maximum of two sums
  return (max_wrap > max_kadane) ? max_wrap : max_kadane;
}

int main(int argc, char** argv) {

  int a[] = {2,7,1,5};
  pair<uint,uint> indices = twoSum(a, 4, 9);
  cout << "Two sum:" << endl;
  cout << indices.first << "," << indices.second << endl;

  int b[] = {2,3,4,5,6,7,8,9,8,7,6,5};
  vector<vector<uint>> res = fourSum(b, 12, 26);
  cout << "Four sum 2 indices:" << endl;
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

   /* int arr2[] = {1, 10, 5, 2, 7};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    x  = 9;
    cout << smallestSubWithSum(arr2, n2, x) << endl;
    int arr3[] = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    x  = 280;
    cout << smallestSubWithSum(arr3, n3, x);
 */
 //   vector<int> a = {-2, -3, 4, -1, -2, 1, 5, -3};
 // subarrayMaxSum(a); //, n);
 // vector<int> b = {-2, -3, -4, -1, -2, -1, -5, -3};
//  subarrayMaxSum(b); //, n); // indices don't work

  int g[10] = {-10,-9,-3,0,2,3,6,7,8,9};
  int h[6] = {-8,-2,0,2,10,11};
  cout << "Max path sum between two arrays: " << maxPathSum(g, h, 10, 6) << endl;

  uint i[] = {3,2,7,10};
  cout << "Max subsequence sum w/o adjacents: " << maxNoAdjSubseqSum(i, 4) << endl;
/*  uint a6[] = {3,2,5,10,7};
  cout << maxNoAdjSubseqSum(a6, 5) << endl;
  uint a7[] = {1,5,4,3,2};
  cout << maxNoAdjSubseqSum(a7, 5) << endl;
 */
  uint j[] = {1, 3, 4, 5};
  n = sizeof(j)/sizeof(j[0]);
  cout << "Smallest unrepresentable number: " << smallestUnrepresentable(j, n) << endl;

  return 0;
}
