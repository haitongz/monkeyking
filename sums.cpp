#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <deque>
#include <algorithm>
#include <limits>
#include <functional>

using namespace std;

static const int32_t MIN_LIMIT = numeric_limits<int32_t>::min();
static const int32_t MAX_LIMIT = numeric_limits<int32_t>::max();

/*
Given an unsorted array, find the largest pair sum in it.
 */
int largestPairSum(const int32_t a[], const uint32_t n) {
  if (!n)
    throw exception();
  if (n < 2)
    return a[0];
  if (n < 3)
    return a[0]+a[1];

  // Initialize first and second largest element
  int32_t first = max(a[0], a[1]);
  int32_t second = min(a[0], a[1]);

  // Traverse remaining array and find first and second largest elements in overall array
  for (uint32_t i = 2; i < n; ++i) {
    /* If current element is greater than first then update both first and second */
    if (a[i] > first) {
      second = first;
      first = a[i];
    } else if (a[i] > second && a[i] != first) /* If arr[i] is in between first and second then update second  */
      second = a[i];
  }

  return (first+second);
}

/*
Given an array of integers, find two numbers such that they add up to a specific target number. The function twoSum
should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers = {2,7,11,15}, target = 9
Output: index1 = 1, index2 = 2
 */
pair<int32_t,int32_t> twoSum(const vector<int32_t>& a, const int32_t target) {
  const uint32_t n = a.size();
  if (!n)
    return {-1,-1};

  unordered_map<int32_t,int32_t> recs;
  pair<int32_t,int32_t> ret;

  for (uint32_t i = 0; i < n; ++i) {
    const int32_t remaining = target-a[i];
    if (recs.count(remaining)) {
      ret.first = recs[remaining]+1; // index1 and index2 are not zero-based.
      ret.second = i+1;
      return ret;
    }

    recs[a[i]] = i;
  }

  return ret;
}

/*
Given an array S of n integers, are there elements a, b, c in S such that a+b+c = 0? Find all unique triplets in the array
which gives the sum of zero. The solution set must not contain duplicate triplets.

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
vector<vector<int32_t>> threeSumTo0(vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (n < 3)
    return {};

  sort(a.begin(), a.end());

  vector<vector<int32_t>> ret;

  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0 && a[i] == a[i-1]) // since we scan from left to right, all a[i] cases were covered in a[i-1] cases already
      continue;

    for (uint32_t j = i+1, k = n-1; j < k;) {
      const int32_t sum = a[i]+a[j]+a[k];
      if ((j > i+1 && a[j] == a[j-1]) || sum < 0)
        ++j;
      else if ((k < n-1 && a[k] == a[k+1]) || sum > 0)
        --k;
      else
        ret.push_back({a[i], a[j++], a[k--]});
    }
  }

  return ret;
}

vector<vector<int32_t>> fourSum(vector<int32_t>& a, const int32_t target) {
  const uint32_t n = a.size();
  if (n < 4)
    return {};

  sort(a.begin(), a.end());

  vector<vector<int32_t>> ret;
  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = i+1; j < n; ++j) {
      uint32_t k = j+1, l = n-1;
      while (k < l) {
        const int32_t sum = a[i]+a[j]+a[k]+a[l];
        if (sum == target) {
          res.push_back({a[i],a[j],a[k],a[l]});
          ++k;
          --l;
        } else if (sum < target) {
          ++k;
        } else if (sum > target) {
          --l;
        }
      }
    }
  }

  sort(ret.begin(), ret.end());
  ret.resize(unique(ret.begin(), ret.end())-ret.begin());
  return ret;
}

/*
1) Create an auxiliary array aux[] and store sum of all possible pairs in aux[]. The size of aux[] will be n*(n-1)/2
where n is the size of A[].
2) Sort the auxiliary array aux[].
3) Now the problem reduces to find two elements in aux[] with sum equal to X. We can use method 1 of this post to find
the two elements efficiently. There is following important point to note though. An element of aux[] represents a pair
from A[]. While picking two elements from aux[], we must check whether the two elements have an element of A[] in common.
For example, if first element sum of A[1] and A[2], and second element is sum of A[2] and A[4], then these two elements of
aux[] don't represent four distinct elements of input array A[].
 */
struct PairSum {
  uint32_t first, second; // index (int A[]) of first element in pair
  int32_t sum; // sum of the pair
};

vector<vector<uint32_t>> fourSum_n2logn(const int32_t a[], const uint32_t n, const int32_t target) {
  if (n < 4)
    throw exception;

  const uint32_t size = n*(n-1)/2;
  PairSum aux[size];

  /* Generate all possible pairs from A[] and store sums of all possible pairs in aux[] */
  uint32_t k = 0;
  for (uint32_t i = 0; i < n-1; ++i) {
    for (uint32_t j = i+1; j < n; ++j) {
      aux[k].sum = a[i]+a[j];
      aux[k].first = i;
      aux[k].second = j;
      ++k;
    }
  }

  // Sort the aux[] array using library function for sorting
  sort(aux.begin(), aux.end(), [](const PairSum& a, const PairSum& b) { return a.sum > b.sum; });

  // Function to check if two given pairs have any common element or not
  function<bool(const PairSum&,const PairSum&)> noCommon = [](const PairSum& a, const PairSum& b) {
    return !(a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second);
  };

  vector<vector<uint32_t>> ret;
  // Now start two index variables from two corners of array and move them toward each other.
  uint32_t i = 0;
  int32_t j = size-1;
  while (i < size && j >=0) {
    if ((aux[i].sum+aux[j].sum) == target && noCommon(aux[i], aux[j]))
      ret.push_back({aux[i].first,aux[i].second,aux[j].first,aux[j].second});
    else if (aux[i].sum+aux[j].sum < target)
      ++i;
    else
      --j;
  }

  return ret;
}

/*
Given a sorted array and a number x, find a pair in array whose sum is closest to x.
 */
pair<uint32_t,uint32_t> twoSumClosest(const vector<int32_t>& a, const int32_t x) {
  const uint32_t n = a.size();
  if (!n)
    return {};

  pair<uint32_t,uint32_t> ret;
  // Initialize left and right indexes and difference between pair sum and x
  uint32_t l = 0, r = n-1;
  int32_t diff = MAX_LIMIT;

  while (r > l) {
    // Check if this pair is closer than the closest pair so far
    if (abs(a[l]+a[r]-x) < diff) {
      ret.first = l;
      ret.second = r;
      diff = abs(a[l]+a[r]-x);
    }

    // If this pair has more sum, move to smaller values.
    if (a[l]+a[r] > x)
      --r;
    else // Move to larger values
      ++l;
  }

  return ret;
}

/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target.
Return the sum of the three integers. You may assume that each input would have exactly one solution.

Given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
int32_t threeSumClosest(vector<int32_t>& a, const int32_t target) {
  const uint32_t n = a.size();
  if (!n)
    throw exception();

  sort(a.begin(), a.end());

  int32_t ret = 0;
  uint32_t diff = max_lmt;

  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0 && a[i-1] == a[i])
      continue;

    uint32_t k = i+1, l = n-1;

    while (k < l) {
      int32_t curr_sum = a[i]+a[k]+a[l];
      uint32_t curr_diff = abs(curr_sum-target);
      if (curr_diff < diff) {
        diff = curr_diff;
        ret = curr_sum;
      }

      if (curr_sum < target)
        ++k;
      else if (curr_sum > target)
        --l;
      else
        return target;
    }
  }

  return ret;
}

/*
Find longest continous subarray that sum up to zero.
For example:
{1, 2 -3, 1, 5, -5, 6} should return {2, -3, 1, 5, -5}
 */
vector<int32_t> longestSubarrayWithZeroSum(const vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return {};

  uint32_t max_len = 0;
  int32_t sum = 0, begin = -1;
  unordered_map<int,int> recs = {{0, -1}};

  for (uint32_t i = 0; i < n; ++i) {
    sum += a[i];
    if (recs.count(sum)) {
      auto first = recs[sum];
      if (i-first > max_len) {
        max_len = i-first;
        begin = first+1;
      }
    } else {
      recs[sum] = i;
    }
  }

  if (begin < 0)
    return {};
  else
    return vector<int32_t>(a.begin()+begin, a.begin()+begin+max_len);
}

/*
Given an array of positive integers, find if there's a continous subarray that sum up to a target
 */
pair<int32_t,int32_t> subarrayWithTargetSum(const vector<uint32_t>& a, const uint32_t target) { // sliding window
  const uint32_t n = a.size();
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
int32_t maxSubarraySum(const vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    throw exception();

  int32_t ret = min_lmt;
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
A pair-sum array for an array is the array that contains sum of all pairs in ordered form. For example pair-sum array
for a[] = {6, 8, 3, 4} is {14, 9, 10, 11, 12, 7}.
In general, pair-sum array for a[0..n-1] is {a[0]+a[1], a[0]+a[2], ..., a[1]+a[2], a[1]+a[3], ..., a[2]+a[3], a[2]+a[4], ...,
a[n-2]+a[n-1}.
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
Given a sorted array (sorted in non-decreasing order) of positive numbers, find the smallest positive integer value that
cannot be represented as sum of elements of any subset of given set.

Expected time complexity is O(n).

If the current number is bigger than the smallest number you can't make so far, then you know the smallest number you
can't make - it's the one you've got recorded, and you're done. Otherwise, the current number is smaller than the smallest
number you can't make. The claim is that you can indeed make this number. Right now, you know the smallest number you can't
make with the first k elements of the array (call it candidate) and are now looking at value A[k]. The number candidate-A[k]
therefore must be some number that you can indeed make with the first k elements of the array, since otherwise candidate-A[k]
would be a smaller number than the smallest number you allegedly can't make with the first k numbers in the array. Moreover,
you can make any number in the range candidate to candidate+A[k], inclusive, because you can start with any number in the
range from 1 to A[k], inclusive, and then add candidate-1 to it. Therefore, set candidate to candidate+A[k] and increment k.
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
Determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is same.
 */
bool partition(const int32_t a[], const uint32_t n) {
  if (n < 2)
    return false;

  int32_t sum = 0;
  for (const auto& i : a)
    sum += i;

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
            /* // uncomment this part to print table 
     for (i = 0; i <= sum/2; i++)  
     {
       for (j = 0; j <= n; j++)  
          printf ("%4d", part[i][j]);
       printf("\n");
     } */

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

int main(int argc, char** argv) {
  vector<int32_t> a = {2,7,1,5};
  pair<uint32_t,uint32_t> indices = twoSum(a, 9);
  cout << "Two sum:" << endl;
  cout << indices.first << "," << indices.second << endl;

  a.clear();
  a = {-1,0,0,0,1,2,-1,-4};

/*  set<vector<int32_t> > res3 = threeSum(a);
  for (set<vector<int32_t> >::const_iterator citer = res3.begin(); citer != res3.end(); ++citer) {
    for (uint32_t i = 0; i < 3; ++i) {
      cout << (*citer)[i] << ",";
    }
    cout << endl;
  }
*/
  vector<vector<int32_t>> res = threeSumTo0(a);
  cout << "Three sum:" << endl;
  for (auto& i : res) {
    for (auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  a.clear();
  a = {-2,-3,-4,-1,-2,-1,-5,-3};
  largestSubarraySum(a); //, n);

  vector<uint32_t> a1 = {1,2,3,4,5,6,7,8,9};
  const uint32_t target = 11;
  pair<int32_t,int32_t> res1 = subarrayWithTargetSum(a1, target);
  cout << "Subarray: " << res1.first << " to " << res1.second << endl;

 //   vector<int32_t> a = {-2, -3, 4, -1, -2, 1, 5, -3};
 // subarrayMaxSum(a); //, n);
 // vector<int32_t> b = {-2, -3, -4, -1, -2, -1, -5, -3};
//  subarrayMaxSum(b); //, n); // indices don't work

  int32_t a3[10] = {-10,-9,-3,0,2,3,6,7,8,9};
  int32_t a4[6] = {-8,-2,0,2,10,11};

  cout << maxPathSum(a3, a4, 10, 6) << endl;
  return 0;
}
