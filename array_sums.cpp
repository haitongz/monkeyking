#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>
#include <functional>

using namespace std;

static const int32_t MIN_LMT = numeric_limits<int32_t>::min();
static const int32_t MAX_LMT = numeric_limits<int32_t>::max();

/*
Given an unsorted array, find the largest pair sum in it.
 */
int32_t largestPairSum(const int32_t a[], const uint32_t n) {
  if (n < 2)
    throw exception();
  if (n == 2)
    return a[0]+a[1];

  int32_t biggest = max(a[0], a[1]);
  int32_t second = min(a[0], a[1]);

  // Traverse remaining array and find biggest and second largest elements in overall array
  for (uint32_t i = 2; i < n; ++i) {
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

Input: numbers = {2,7,11,15}, target = 9
Output: index1 = 1, index2 = 2
 */
pair<int32_t,int32_t> twoSum(const int32_t a[], const uint32_t n, const int32_t target) {
  if (!n)
    return {-1,-1};

  map<int32_t,int32_t> mem;
  pair<int32_t,int32_t> ret;

  for (uint32_t i = 0; i < n; ++i) {
    int32_t v = a[i];
    const int32_t remain = target-v;
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
pair<uint32_t,uint32_t> twoSumClosest(int32_t a[], const uint32_t n, const int32_t x) {
  if (!n)
    return {};

  // Initialize left and right indexes and difference between pair sum and x
  uint32_t left = 0, right = n-1;
  int32_t diff = MAX_LMT;
  pair<uint32_t,uint32_t> ret;

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
/*
set<vector<int32_t>> threeSum(const vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (n < 3)
    return {};

  deque<vector<uint32_t>> q;
  for (uint32_t i = 0; i < n; ++i) {
    vector<uint32_t> v;
    v.push_back(i);
    q.push_back(v);
  }

  set<vector<int32_t>> res;
  while (!q.empty()) {
    vector<uint32_t>& v = q.front();
    if (v.size() == 3) {
      int32_t sum = 0;
      multiset<int32_t> s;
      for (uint32_t i = 0; i < 3; ++i) {
        sum += a[v[i]];
        s.insert(a[v[i]]);
      }

      if (!sum) {
        vector<int32_t> tmp;
        for (multiset<int32_t>::const_iterator iter = s.begin(); iter != s.end(); ++iter) {
          tmp.push_back(*iter);
        }
        res.insert(tmp);
      }
    } else if (v.size() < 3) {
      for (uint32_t i = *(--v.end())+1; i < n; ++i) {
        vector<uint32_t> next_v(v);
        next_v.push_back(i);
        q.push_back(next_v);
      }
    }

    q.pop_front();
  }

  return res;
}
*/
vector<vector<uint32_t>> threeSumTo0(vector<int32_t>& S) {
  const uint32_t n = S.size();
  if (n < 3)
    return {};

  sort(S.begin(), S.end());

  vector<vector<uint32_t>> ret; // indices

  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i]) // since we scan from left to right, all a[i] cases were covered in a[i-1] cases already
      continue;

    for (uint32_t j = i+1, k = n-1; j < k;) {
      const int32_t sum = S[i]+S[j]+S[k];
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
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
Given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
int32_t threeSumClosest(vector<int32_t>& S, const int32_t target) {
  const uint32_t n = S.size();
  if (n < 3)
    throw exception();

  sort(S.begin(), S.end());

  int32_t ret = 0;
  uint32_t diff = MAX_LMT;

  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i])
      continue;

    uint32_t left = i+1, right = n-1;

    while (left < right) {
      int32_t curr_sum = S[i]+S[left]+S[right];
      uint32_t curr_diff = abs(curr_sum-target);
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

vector<vector<uint32_t>> fourSum(vector<int32_t>& S, const int32_t target) { // O(n^3)
  const uint32_t n = S.size();
  if (n < 4)
    return {};

  sort(S.begin(), S.end());
  vector<vector<uint32_t>> ret;

  for (uint32_t i = 0; i < n-3; ++i) {
    for (uint32_t j = i+1; j < n-2; ++j) {
      uint32_t left = j+1, right = n-1;

      // To find the remaining two elements, move the index variables (left &
      // right) toward each other.
      while (left < right) {
        int32_t t_sum = S[i]+S[j]+S[left]+S[right];
        if (t_sum == target) {
          vector<uint32_t> indices = {i,j,left,right};
          ret.push_back(indices);
          ++left;
          --right;
        } else if (t_sum < target)
          ++left;
        else
          --right;
      } // end of while
    } // end of inner for loop
  } // end of outer for loop

 // sort(ret.begin(), ret.end());
 // ret.erase(unique(ret.begin(), ret.end()), ret.end());
  return ret;
}

/*
1) Create an auxiliary array aux[] and store sum of all possible pairs in aux[]. The size of aux[] will be
n*(n-1)/2 where n is the size of a[].
2) Sort the auxiliary array aux[].
3) Now the problem reduces to find two elements in aux[] with sum equal to X. We can use method 1 of this
post to find the two elements efficiently. There is following important point to note though. An element of
aux[] represents a pair from a[]. While picking two elements from aux[], we must check whether the two
elements have an element of a[] in common. For example, if first element sum of a[1] and a[2], and second
element is sum of a[2] and a[4], then these two elements of aux[] don't represent four distinct elements
of input array a[].
 */
struct PairSum {
  int32_t sum; // pair sum
  uint32_t first, second; // indices (in a[]) of elements in pair
};

vector<vector<uint32_t>> fourSum(const int32_t a[], const uint32_t n, const int32_t target) { // O(n^2Logn)
  if (n < 4)
    return {};

  const uint32_t size = n*(n-1)/2;
  vector<PairSum> aux(size, PairSum());
  for (uint32_t i = 0, k = 0; i < n-1; ++i) { // generate all possible pairs from a[] and store sums of all possible pairs in aux[]
    for (uint32_t j = i+1; j < n; ++j) {
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

  vector<vector<uint32_t>> ret;
  // Now start two index variables from two corners of array and move them toward each other.
  uint32_t i = 0;
  int32_t j = size-1;
  while (i <= j ) { //size && j >= 0) {
    int32_t t_sum = aux[i].sum+aux[j].sum;
    if (t_sum == target) {
      if (noCommon(aux[i], aux[j])) {
        vector<uint32_t> indices = {aux[i].first,aux[i].second,aux[j].first,aux[j].second};
        sort(indices.begin(), indices.end());
        ret.push_back(indices);
      }
      ++i;
    } else if (t_sum < target)
      ++i;
    else
      --j;
  }

  sort(ret.begin(), ret.end());
  return ret;
}

/*
Find longest continous subarray that sum up to zero.
For example:
{1, 2 -3, 1, 5, -5, 6} should return {2, -3, 1, 5, -5}
 */
vector<int32_t> longestSubarraySumsTo0(const int32_t a[], const uint32_t n) {
  if (!n)
    return {};

  uint32_t max_len = 0;
  int32_t sum = 0, begin = -1;
  map<int32_t,uint32_t> mem; // = {{0, -1}};

  for (uint32_t i = 0; i < n; ++i) {
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
    vector<int32_t> ret;
    for (uint32_t i = 0; i < max_len; ++i)
      ret.push_back(a[begin+i]);

    return ret;
  }
}

/*
Given an array of unsorted non-negative integers, find if there's a continous subarray that sum up to a target
 */
pair<int32_t,int32_t> subarraySum2Target(const uint32_t a[], const uint32_t n, const uint32_t target) { // sliding window
  if (!n)
    return {};

  deque<uint32_t> q;
  uint32_t q_sum = 0;

  for (uint32_t i = 0; i < n;) {
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

void subarraySum2Target_2(const uint32_t a[], const uint32_t n, const uint32_t target) {
  uint32_t curr_sum = a[0], start = 0;

  /* Add elements one by one to curr_sum and if the curr_sum exceeds target, then remove starting element */
  for (uint32_t i = 1; i < n+1; ++i) {
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
Given an array of integers and a number x, find the smallest subarray with sum greater than the given value.
 */
int32_t smallestSubarrayBiggerSum(const int32_t a[], const uint32_t n, const int32_t target) {
  if (!n)
    return -1;

  int32_t curr_sum = 0, min_len = n+1;
  uint32_t start = 0, end = 0;

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
int32_t maxSubArraySum(const vector<int32_t>& a) { // this works for all negative a as well
  const uint32_t n = a.size();
  if (!n)
    throw exception();

  int32_t max_so_far = a[0];
  int32_t curr_max = a[0];

  for (uint32_t i = 1; i < n; ++i) {
    curr_max = max(a[i], curr_max+a[i]);
    max_so_far = max(max_so_far, curr_max);
  }

  return max_so_far;
}
 */
int32_t maxSubarraySum(const int32_t a[], const uint32_t n) {
  if (!n)
    throw exception();

  int32_t ret = MIN_LMT;
  int32_t i_sum = 0;
  uint32_t start = 0, end = 0;

  for (uint32_t i = 0; i < n; ++i) {
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
int32_t maxSizeKSubarraySum(const vector<int32_t>& a) {
  const uint32_t n = a.size();
}

/*
Given a pair-sum array and size of the original array (n), construct the original array.
A pair-sum array for an array is the array that contains sum of all pairs in ordered form. For example pair-sum array for a[] = {6, 8, 3, 4} is {14, 9, 10, 11, 12, 7}.
In general, pair-sum array for a[0..n-1] is {a[0]+a[1], a[0]+a[2], ..., a[1]+a[2], a[1]+a[3], ..., a[2]+a[3], a[2]+a[4], ..., a[n-2]+a[n-1}.
 */
void construct(int32_t a[], const int32_t pair[], const uint32_t n) {
  if (!n)
    return;

  a[0] = (pair[0]+pair[1]-pair[n-1])/2;
  for (uint32_t i = 1; i < n; ++i)
    a[i] = pair[i-1]-a[0];
}

/*
vector<vector<int32_t> >
zeroSumInSorted_recur(const vector<int32_t>& a, const uint32_t begin, const uint32_t count, const int32_t target) {
  vector<vector<int32_t> > res;
  vector<int32_t> tuple;
  set<int32_t> visited;

  if (count == 2) {
    uint32_t i = begin, j = a.size()-1;
    while (i < j) {
      int32_t sum = a[i]+a[j];
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
    for (uint32_t i = begin; i < a.size(); ++i) {
      if (visited.find(a[i]) == visited.end()) {
        visited.insert(a[i]);
        vector<int32_t> sub_res = zeroSumInSorted_recur(a, i+1, count-1, target-a[i]);
        if (!sub_res.empty()) {
          for (uint32_t j = 0; j < sub_res.size(); ++j) {
            sub_res[j].insert(sub_res[j].begin(), a[i]);
          }
          res.insert(res.end(), sub_res.begin(), sub_res.end());
        }
      }
    }
  }

  return res;
}

vector<int32_t> threeSum3(const vector<int32_t>& a) {
  sort(a.begin(), num.end());
  return zeroSumInSorted(a, 0, 3, 0);
}

vector<int32_t> fourSum(vector<int32_t>& a, const int32_t target) {
  sort(a.begin(), a.end());
  return zeroSumInSorted(a, 0, 4, target);
}
*/
/*
Given a sorted array (sorted in non-decreasing order) of positive numbers, find the smallest positive integer value that cannot be represented as sum of elements of any subset of given set.
Expected time complexity is O(n).

If the current number is bigger than the smallest number you can't make so far, then you know the smallest number you can't make - it's the one you've got recorded, and you're done. Otherwise, the current number is smaller than the smallest number you can't make. The claim is that you can indeed make this number. Right now, you know the smallest number you can't make with the first k elements of the array (call it candidate) and are now looking at value A[k]. The number candidate-A[k] therefore must be some number that you can indeed make with the first k elements of the array, since otherwise candidate-A[k] would be a smaller number than the smallest number you allegedly can't make with the first k numbers in the array. Moreover, you can make any number in the range candidate to candidate+A[k], inclusive, because you can start with any number in the range from 1 to A[k], inclusive, and then add candidate-1 to it. Therefore, set candidate to candidate+A[k] and increment k.
 */
uint32_t smallestUnrepresentable(const vector<uint32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    throw exception();

  uint32_t ret = 1;

  // Traverse the array and increment 'ret' if a[i] is smaller than or equal to 'ret'.
  for (uint32_t i = 0; i < n && a[i] <= ret; ++i)
    ret += a[i];

  return ret;
}

/*
Determine whether a given set can be partitioned into two subsets such that the sum of elements
in both subsets is same.
 */
bool partition(const int32_t a[], const uint32_t n) {
  if (n < 2)
    return false;

  int32_t sum = 0;
  for (uint32_t i = 0; i < n; ++i)
    sum += a[i];
  if (sum%2 != 0)
    return false;

  bool part[sum/2+1][n+1];
  for (uint32_t i = 0; i < n+1; ++i)
    part[0][i] = true;
  for (uint32_t i = 1; i < sum/2+1; ++i)
    part[i][0] = false;

  // Fill the partition table in botton up manner
  for (uint32_t i = 1; i < sum/2+1; ++i) {
    for (uint32_t j = 1; j < n+1; ++j) {
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
int32_t maxPathSum(int32_t a1[], int32_t a2[], const uint32_t m, const uint32_t n) {
  int32_t ret = 0, sum1 = 0, sum2 = 0;
  uint32_t i = 0, j = 0;

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
uint32_t maxNoAdjSubseqSum(uint32_t a[], const uint32_t n) {
  if (!n)
    return 0;

  uint32_t incl = a[0], excl = 0;
  uint32_t excl_new;

  for (uint32_t i = 1; i < n; ++i) {
    /* current max excluding i */
    excl_new = (incl > excl) ? incl: excl;

    /* current max including i */
    incl = excl+a[i];
    excl = excl_new;
  }

  /* return max of incl and excl */
  return ((incl > excl) ? incl : excl);
}

uint32_t maxNoAdjSubseqSum2(uint32_t a[], const uint32_t n) {
  if (!n)
    return 0;

  uint32_t ret = 0;

  function<void(const uint32_t,uint32_t)> solve =
    [&](const uint32_t idx, uint32_t curr_sum) {
    if (idx >= n) {
      return;
    }

    curr_sum += a[idx];
    ret = max(ret, curr_sum);
    for (uint32_t i = idx+2; i < n; ++i) {
      solve(i, curr_sum);
    }
  };

  for (uint32_t i = 0; i < n; ++i)
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
int32_t equilibrium(int32_t a[], const uint32_t n) {
  if (!n)
    return -1;

  int32_t sum = 0;     // initialize sum of whole array
  int32_t leftsum = 0; // initialize leftsum

  for (uint32_t i = 0; i < n; ++i)
    sum += a[i];

  for (uint32_t i = 0; i < n; ++i) {
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
int32_t kadane(const int32_t a[], const uint32_t n) {
  int32_t max_so_far = 0, max_ending_here = 0;

  for (uint32_t i = 0; i < n; ++i) {
    max_ending_here += a[i];
    if (max_ending_here < 0)
      max_ending_here = 0;
    max_so_far = max(max_so_far, max_ending_here);
  }

  return max_so_far;
}

int32_t maxCircularSum(int32_t a[], const uint32_t n) {
  // Case 1: get the maximum sum using standard kadane's algorithm
  int32_t max_kadane = kadane(a, n);

  // Case 2: Now find the maximum sum that includes corner elements.
  int32_t max_wrap = 0;
  for (uint32_t i = 0; i < n; ++i) {
    max_wrap += a[i]; // Calculate array-sum
    a[i] = -a[i];  // invert the array (change sign)
  }

  // max sum with corner elements will be: array-sum - (-max subarray sum of inverted array)
  max_wrap += kadane(a, n);

  // The maximum circular sum will be maximum of two sums
  return (max_wrap > max_kadane) ? max_wrap : max_kadane;
}

int main(int argc, char** argv) {
  int32_t a[] = {2,7,1,5};
  pair<uint32_t,uint32_t> indices = twoSum(a, 4, 9);
  cout << "Two sum:" << endl;
  cout << indices.first << "," << indices.second << endl;

  vector<int32_t> v = {-1,0,0,0,1,2,-1,-4};
/*  set<vector<int32_t> > res3 = threeSum(a);
  for (set<vector<int32_t> >::const_iterator citer = res3.begin(); citer != res3.end(); ++citer) {
    for (uint32_t i = 0; i < 3; ++i) {
      cout << (*citer)[i] << ",";
    }
    cout << endl;
  }
*/
  vector<vector<uint32_t>> res = threeSumTo0(v);
  cout << "Three sum indices:" << endl;
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  v = {2,3,4,5,6,7,8,9,8,7,6,5};
  res = fourSum(v, 26); // issues?
  cout << "Four sum indices:" << endl;
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  int32_t b[] = {2,3,4,5,6,7,8,9,8,7,6,5};
  res = fourSum(b, 12, 26);
  cout << "Four sum 2 indices:" << endl;
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  int32_t c[] = {-2,-3,-4,-1,-2,-1,-5,-3};
  maxSubarraySum(c, 8);

  int32_t d[] = {1, 2 -3, 1, 5, -5, 6};
  vector<int32_t> res1 = longestSubarraySumsTo0(d, 7);
  cout << "Longest subarray with sum 0: ";
  for (const auto& i : res1)
    cout << i << " ";
  cout << endl;

  uint32_t e[] = {1,2,3,4,5,6,7,8,9};
  const uint32_t target = 11;
  pair<int32_t,int32_t> indices1 = subarraySum2Target(e, 9, target);
  cout << "Subarray: " << indices1.first << " to " << indices1.second << endl;
  subarraySum2Target_2(e, 9, target);

  int32_t f[] = {1, 4, 45, 6, 10, 19};
  int32_t target1 = 51;
  uint32_t n1 = sizeof(f)/sizeof(f[0]);
  cout << "Length of smallest subarray with sum bigger than " << target1 << ": " << smallestSubarrayBiggerSum(f, n1, target1) << endl;
   /* int arr2[] = {1, 10, 5, 2, 7};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    x  = 9;
    cout << smallestSubWithSum(arr2, n2, x) << endl;

    int arr3[] = {1, 11, 100, 1, 0, 200, 3, 2, 1, 250};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    x  = 280;
    cout << smallestSubWithSum(arr3, n3, x);
 */
 //   vector<int32_t> a = {-2, -3, 4, -1, -2, 1, 5, -3};
 // subarrayMaxSum(a); //, n);
 // vector<int32_t> b = {-2, -3, -4, -1, -2, -1, -5, -3};
//  subarrayMaxSum(b); //, n); // indices don't work

  int32_t g[10] = {-10,-9,-3,0,2,3,6,7,8,9};
  int32_t h[6] = {-8,-2,0,2,10,11};
  cout << maxPathSum(g, h, 10, 6) << endl;

  uint32_t i[] = {3,2,7,10};
  cout << maxNoAdjSubseqSum(i, 4) << endl;
/*  uint32_t a6[] = {3,2,5,10,7};
  cout << maxNoAdjSubseqSum(a6, 5) << endl;
  uint32_t a7[] = {1,5,4,3,2};
  cout << maxNoAdjSubseqSum(a7, 5) << endl;
 */
  return 0;
}