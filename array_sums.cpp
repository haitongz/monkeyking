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
Given an unsorted array, find the largest pair sum in it.
 */
int largestPairSum(const int a[], const uint n) {
  if (n < 2)
    throw exception();
  if (n == 2)
    return a[0]+a[1];

  int biggest = max(a[0], a[1]);
  int second = min(a[0], a[1]);

  // Traverse remaining array and find biggest and second largest elements in overall array
  for (uint i = 2; i < n; ++i) {
    if (a[i] > biggest) { /* if greater than biggest then update both biggest and second */
      second = biggest;
      biggest = a[i];
    } else if (a[i] > second && a[i] != biggest) /* if a[i] is in between biggest and second then update second  */
      second = a[i];
  }

  return (biggest+second);
}

/*
Given an array of integers, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target,
where index1 must be less than index2. Please note that your returned answers (both index1 and index2)
are not zero-based.
You may assume that each input would have exactly one solution.
Input: a[] = {2,7,11,15}, target = 9
Output: index1 = 1, index2 = 2
 */
pair<int,int>
twoSum(const int a[], const uint n, const int target) {
  if (!n)
    return {-1,-1};

  map<int,int> mem;
  pair<int,int> ret;

  for (uint i = 0; i < n; ++i) {
    int v = a[i];
    const int remain = target-v;
    if (mem.count(remain)) {
      ret.first = mem[remain]+1; // index1 and index2 are not zero-based.
      ret.second = i+1;
      return ret;
    }

    mem[v] = i;
  }

  return ret;
}

/*
Given a sorted array and a number x, find a pair in array whose sum is closest to x.
 */
pair<uint,uint>
twoSumClosest(int a[], const uint n, const int x) {
  if (!n)
    return {};

  // Initialize left and right indexes and difference between pair sum and x
  uint left = 0, right = n-1;
  int diff = MAX_LMT;
  pair<uint,uint> ret;

  while (left < right) {
    if (abs(a[left]+a[right]-x) < diff) { // Check if this pair is closer than the closest pair so far
      ret.first = left;
      ret.second = right;
      diff = abs(a[left]+a[right]-x);
    }

    // If this pair has more sum, move to smaller values.
    if (a[left]+a[right] > x)
      --right;
    else // Move to larger values
      ++left;
  }

  return ret;
}

/*
Given an array S of n integers, are there elements a, b, c in S such that a+b+c = 0?
Find all unique triplets in the array which gives the sum of zero. The solution set must not contain
duplicate triplets.
Note:
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
Given array S = {-1 0 1 2 -1 -4},
A solution set is:
(-1, 0, 1)
(-1, -1, 2)
 */
struct ThreeIndices {
  uint first, second, third;
};

vector<ThreeIndices> threeSumTo0(vector<int>& S) {
  const uint n = S.size();
  if (n < 3)
    return {};

  sort(S.begin(), S.end());

  vector<ThreeIndices> ret; // indices

  for (uint i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i]) // since we scan from left to right, all a[i] cases were covered in a[i-1] cases already
      continue;

    for (uint j = i+1, k = n-1; j < k;) {
      const int sum = S[i]+S[j]+S[k];
      if ((j > i+1 && S[j] == S[j-1]) || sum < 0)
        ++j;
      else if ((k < n-1 && S[k] == S[k+1]) || sum > 0)
        --k;
      else
        ret.push_back({i, j++, k--});
    }
  }

  return ret;
}

/*
Given an array S of n integers, find three integers in S such that
the sum is closest to a given number target. Return the sum of the three integers.
You may assume that each input would have exactly one solution.

Given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
int threeSumClosest(vector<int>& S, const int target) {
  const uint n = S.size();
  if (n < 3)
    throw exception();

  sort(S.begin(), S.end());

  int ret = 0;
  uint diff = MAX_LMT;

  for (uint i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i])
      continue;

    uint left = i+1, right = n-1;

    while (left < right) {
      int curr_sum = S[i]+S[left]+S[right];
      uint curr_diff = abs(curr_sum-target);
      if (curr_diff < diff) {
        diff = curr_diff;
        ret = curr_sum;
      }

      if (curr_sum < target)
        ++left;
      else if (curr_sum > target)
        --right;
      else
        return target;
    }
  }

  return ret;
}

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
Find longest continous subarray that sum up to zero.
For example:
{1, 2 -3, 1, 5, -5, 6} should return {2, -3, 1, 5, -5}
 */
vector<int> longestSubarraySumsTo0(const int a[], const uint n) {
  if (!n)
    return {};

  uint max_len = 0;
  int sum = 0, begin = -1;
  map<int,uint> mem; // = {{0, -1}};

  for (uint i = 0; i < n; ++i) {
    sum += a[i];
    if (mem.count(sum)) { // if this sum has appeared before, what's in the middle is a subarray with 0 sum
      auto pos = mem[sum];
      if (i-pos > max_len) {
        max_len = i-pos;
        begin = pos+1;
      }
    } else {
      mem[sum] = i;
    }
  }

  if (begin < 0)
    return {};
  else {
    vector<int> ret;
    for (uint i = 0; i < max_len; ++i)
      ret.push_back(a[begin+i]);

    return ret;
  }
}

/*
Given an array of unsorted non-negative integers, find if there's a continous subarray
that sum up to a target.
 */
pair<int,int>
subarraySum2Target(const uint a[], const uint n, const uint target) { // sliding window
  if (!n)
    return {};

  deque<uint> q;
  uint q_sum = 0;

  for (uint i = 0; i < n;) {
    if (a[i] == target) {
      return make_pair(i, i);
    }

    if (q_sum+a[i] == target)
      return {q.front(), i};
    else if (q_sum+a[i] > target) { // no contiguous subarray starting from q.front()
      q_sum -= a[q.front()];
      q.pop_front();
    } else {
      q.push_back(i);
      q_sum += a[i];
      ++i;
    }
  }

  return {-1,-1};
}

void subarraySum2Target_2(const uint a[], const uint n, const uint target) {
  uint curr_sum = a[0], start = 0;

  for (uint i = 1; i < n+1; ++i) {
    // If curr_sum exceeds the sum, then remove the starting elements
    while (curr_sum > target && start < i-1) {
      curr_sum -= a[start++];
    }

    // If curr_sum becomes equal to sum, then return true
    if (curr_sum == target) {
      cout << "Target sum found between indexes " << start << " and " << i-1 << endl;
      return;
    }

    // Add this element to curr_sum
    if (i < n)
      curr_sum += a[i];
  }

  // If we reach here, then no subarray
  cout << "No subarray found!" << endl;
}

/*
Given an array of integers and a number x, find the smallest subarray
with sum greater than the given value.
 */
int smallestSubarrayBiggerSum(const int a[], const uint n, const int target) {
  if (!n)
    return -1;

  int curr_sum = 0, min_len = n+1;
  uint start = 0, end = 0;

  while (end < n) {
    // Keep adding array elements while current sum is smaller than target
    while (curr_sum <= target && end < n)
      curr_sum += a[end++];

    while (curr_sum > target && start < n) {
      // Update minimum length if needed
      if (end-start < min_len)
        min_len = end-start;

      // remove starting elements
      curr_sum -= a[start++];
    }
  }

  return min_len;
}

/*
Find sum of contiguous subarray within a one-dimensional array of numbers which has largest sum.
int maxSubArraySum(const vector<int>& a) { // this works for all negative a as well
  const uint n = a.size();
  if (!n)
    throw exception();
  int max_so_far = a[0];
  int curr_max = a[0];
  for (uint i = 1; i < n; ++i) {
    curr_max = max(a[i], curr_max+a[i]);
    max_so_far = max(max_so_far, curr_max);
  }
  return max_so_far;
}
 */
int maxSubarraySum(const int a[], const uint n) {
  if (!n)
    throw exception();

  int ret = MIN_LMT;
  int i_sum = 0;
  uint start = 0, end = 0;

  for (uint i = 0; i < n; ++i) {
    // i_sum: sum of contiguous subarray before i, either starting from 0 or not
    i_sum += a[i]; // expands to i-th element
    if (i_sum < ret) {
      end = i-1;
    } else {
      end = i;
    }

    ret = max(i_sum, ret);

    if (i_sum < 0) {
      start = min(i+1, n-1);
      end   = min(i+1, n-1);
    }

    i_sum = max(0, i_sum); // if current subarray sum is negative, remove it since next element as a subarry will only have bigger sum (which is a[i+1]). new contiguous subarray starts from i+1
  }

  cout << "Subarray starts from " << start << " and ends at " << end << " with largest sum " << ret << endl;
  return ret;
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
Determine whether a given set can be partitioned into two subsets such that the sum of elements
in both subsets is same.
 */
bool partition(const int a[], const uint n) {
  if (n < 2)
    return false;

  int sum = 0;
  for (uint i = 0; i < n; ++i)
    sum += a[i];
  if (sum%2 != 0)
    return false;

  bool part[sum/2+1][n+1];
  for (uint i = 0; i < n+1; ++i)
    part[0][i] = true;
  for (uint i = 1; i < sum/2+1; ++i)
    part[i][0] = false;

  // Fill the partition table in botton up manner
  for (uint i = 1; i < sum/2+1; ++i) {
    for (uint j = 1; j < n+1; ++j) {
      part[i][j] = part[i][j-1];
      if (i >= a[j-1])
        part[i][j] = part[i][j] || part[i-a[j-1]][j-1];
    }
  }

  return part[sum/2][n];
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

  vector<int> v = {-1,0,0,0,1,2,-1,-4};
  vector<ThreeIndices> res0 = threeSumTo0(v);
  cout << "Three sum indices:" << endl;
  for (const auto& i : res0) {
    cout << i.first << " " << i.second << " " << i.third << endl;
  }

  int b[] = {2,3,4,5,6,7,8,9,8,7,6,5};
  vector<vector<uint>> res = fourSum(b, 12, 26);
  cout << "Four sum 2 indices:" << endl;
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  int c[] = {-2,-3,-4,-1,-2,-1,-5,-3};
  maxSubarraySum(c, 8);

  int d[] = {1, 2 -3, 1, 5, -5, 6};
  vector<int> res1 = longestSubarraySumsTo0(d, 7);
  cout << "Longest subarray with sum 0: ";
  for (const auto& i : res1)
    cout << i << " ";
  cout << endl;

  uint e[] = {1,2,3,4,5,6,7,8,9};
  const uint target = 11;
  pair<int,int> indices1 = subarraySum2Target(e, 9, target);
  cout << "Subarray: " << indices1.first << " to " << indices1.second << endl;
  subarraySum2Target_2(e, 9, target);

  int f[] = {1, 4, 45, 6, 10, 19};
  int target1 = 51;
  uint n = sizeof(f)/sizeof(f[0]);
  cout << "Length of smallest subarray with sum bigger than " << target1 << ": " << smallestSubarrayBiggerSum(f, n, target1) << endl;
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
