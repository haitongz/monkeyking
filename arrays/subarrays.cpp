#include <iostream>
#include <map>
#include <queue>
#include <limits>

using namespace std;

namespace {
  const int MAX_LMT = numeric_limits<int>::has_infinity ?
                           numeric_limits<int>::infinity() : numeric_limits<int>::max();

  const int MIN_LMT = numeric_limits<int>::has_infinity ?
                           -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();
}

/*
Find two non-overlapping subarrays A and B, which |SUM(A) - SUM(B)| is the largest. Return the largest difference.
 */
int maxDiffSubarrays(const int a[], const uint n) {
  if (n < 2) {
    throw exception();
  }

  int minLeft[n];
  int minRight[n];
  int maxLeft[n];
  int maxRight[n];

  int sum1 = 0;
  int sum2 = 0;
  int minSum = MAX_LMT;
  int maxSum = MIN_LMT;

  for (uint i = 0; i < n; ++i) {
    sum1 += a[i];
    sum2 += a[i];

    minSum = min(minSum, sum1);
    maxSum = max(maxSum, sum2);
    minLeft[i] = minSum;
    maxLeft[i] = maxSum;
    sum1 = min(sum1, 0);
    sum2 = max(sum2, 0);
  }

  sum1 = 0;
  sum2 = 0;
  minSum = MAX_LMT;
  maxSum = MIN_LMT;

  for (int i = n; i > 0; --i) {
    sum1 += a[i-1];
    sum2 += a[i-1];
    minSum = min(minSum, sum1);
    maxSum = max(maxSum, sum2);
    minRight[i-1] = minSum;
    maxRight[i-1] = maxSum;
    sum1 = min(sum1, 0);
    sum2 = max(sum2, 0);
  }

  int ret = MIN_LMT;
  for (uint i = 0; i < n-1; ++i) {
    ret = max(ret, max(abs(maxLeft[i]-minRight[i+1]), abs(maxRight[i+1]-minLeft[i])));
  }

  return ret;
}

/*
Given an array of unsorted non-negative integers, find if there's a continous subarray
that sum up to a target.
 */
pair<int,int> targetSumSubarray(const uint a[], const uint n, const uint target) {
  if (!n) {
    return {-1,-1};
  }

  deque<uint> q;
  uint qSum = 0;
  uint i = 0;

  while (i < n) { // because it's non-negative, we can use sliding window
    if (a[i] == target) {
      return make_pair(i, i);
    }

    if (qSum+a[i] == target) { // move at both ends to find subarrys
      return {q.front(), i};
    } else if (qSum+a[i] > target) { // no contiguous subarray starting from q.front()
      qSum -= a[q.front()];
      q.pop_front();
    } else {
      q.push_back(i);
      qSum += a[i];
      ++i;
    }
  }

  return {-1,-1};
}

void targetSumSubarray_2(const uint a[], const uint n, const uint target) {
  uint currSum = a[0], start = 0;

  for (uint i = 1; i < n+1; ++i) {
    // If currSum exceeds target, then remove the starting elements
    while (currSum > target && start < i-1) {
      currSum -= a[start++];
    }

    // If currSum becomes equal to sum, then return true
    if (currSum == target) {
      cout << "Target sum found between indices " << start << " and " << i-1 << endl;
      return;
    }

    // Add this element to currSum
    if (i < n)
      currSum += a[i];
  }

  // If we reach here, then no subarray
  cout << "No subarray found!" << endl;
}

/*
Given an array of integers and a number x, find the smallest subarray
with sum greater than the given value.
 */
uint smallestSubarray(const int a[], const uint n, const int x) {
  if (!n) {
    return 0;
  }

  int currSum = 0, minLen = n+1;
  uint start = 0, end = 0;

  while (end < n) {
    while (currSum <= x && end < n) { // keep adding array elements while current sum is smaller than target
      currSum += a[end++];
    }

    while (currSum > x && start < n) {
      if (end-start < minLen) { // update minimum length if needed
        minLen = end-start;
      }

      // remove starting elements
      currSum -= a[start++];
    }
  }

  return minLen;
}

/*
Given an integer array, find a subarray where the sum of numbers is zero. Your code should return the index of the first number and the index of the last number.
 */
pair<int,int> zeroSumSubarray(int a[], const uint n) {
  if (!n) {
    return {-1,-1};
  }

  int sum = 0;
  map<int,uint> mem;

  for (uint i = 0; i < n; ++i) {
    sum += a[i];
    if (!sum) {
      return {0,i};
    }
    if (mem.count(sum)) { // if this sum has appeared before, what's in the middle is a subarray with 0 sum
      auto pos = mem[sum];
      return {pos+1,i};
    } else {
      mem[sum] = i;
    }
  }

  return {-1,-1};
}

/*
Find longest continous subarray that sum up to zero.
For example:
{1, 2, -3, 1, 5, -5, 6} should return {2, -3, 1, 5, -5}
 */
pair<int,int> longest0SumSubarray(const int a[], const uint n) {
  if (!n) {
    return {-1,-1};
  }

  uint maxLen = 0;
  int sum = 0, begin = -1;
  map<int,uint> mem;

  for (uint i = 0; i < n; ++i) {
    sum += a[i];
    if (!sum) {
      mem[0] = i;
      if (i-0 > maxLen) {
        maxLen = i+1;
        begin = 0;
      }
    } else if (mem.count(sum)) { // if this sum has appeared before, what's in the middle is a subarray with 0 sum
      auto pos = mem[sum];
      if (i-pos > maxLen) {
        maxLen = i-pos;
        begin = pos+1;
      }
    } else {
      mem[sum] = i;
    }
  }

  if (begin < 0) {
    return {-1,-1};
  } else {
    return {begin,begin+maxLen};
  }
}

/*
Given an array that contains both positive and negative integers, find the product of the maximum product subarray.
Expected Time complexity is O(n) and only O(1) extra space can be used.
 */
int maxSubarrayProduct(const int a[], const uint n) {
  if (!n) {
    throw exception();
  }

  int currMax = 1;
  int currMin = 1;
  int ret = 1;

  /*
  currMax is always 1 or some positive product ending with a[i]
  currMin is always 1 or some negative product ending with a[i]
   */
  for (uint i = 0; i < n; ++i) {
    if (a[i] > 0) { // update currMax if positive; only update currMin when currMin is negative
      currMax *= a[i];
      currMin = min(currMin*a[i], 1);
    } else if (!a[i]) { /* If this element is 0, then the maximum product cannot end here,
                           make both currMax and currMin 0.
                           Assumption: Output is alway greater than or equal to 1. */
      currMax = 1;
      currMin = 1;
    } else {
    /* If element is negative. This is tricky: currMax can either be 1
       or positive. currMin can either be 1 or negative. next
       currMin will always be prev currMax*a[i].
       next currMax will be 1 if prev currMin is 1,
       otherwise next currMax will be prev currMin*a[i]
    */
      int tmp = currMax;
      currMax = max(currMin*a[i], 1);
      currMin = tmp*a[i];
    }

    // update ret, if needed
    ret = max(ret, currMax);
  }

  return ret;
}

/*
Given an array containing only 0s and 1s, find the largest subarray which contain equal no of 0s and 1s.
Expected time complexity is O(n).
 */
/*
1) Consider all 0 values as -1. The problem now reduces to find out the maximum length subarray with sum = 0.
2) Create a temporary array sumleft[] of size n. Store the sum of all elements from a[0] to a[i] in sumleft[i].
   This can be done in O(n) time.
3) There are two cases, the output subarray may start from 0th index or may start from some other index.
   We will return the max of the values obtained by two cases.
4) To find the maximum length subarray starting from 0th index, scan the sumleft[] and find the maximum i where sumleft[i] = 0.
5) Now, we need to find the subarray where subarray sum is 0 and start index is not 0.
   This problem is equivalent to finding two indexes i & j in sumleft[] such that sumleft[i] = sumleft[j] and j-i is maximum.
   To solve this, we can create a hash table with size = max-min+1 where min is the minimum value in the sumleft[] and
   max is the maximum value in the sumleft[]. The idea is to hash the leftmost occurrences of all different values
   in sumleft[]. The size of hash is chosen as max-min+1 because there can be these many different possible values
   in sumleft[]. Initialize all values in hash as -1
6) To fill and use hash[], traverse sumleft[] from 0 to n-1. If a value is not present in hash[],
   then store its index in hash. If the value is present, then calculate the difference of current index of
   sumleft[] and previously stored value in hash[]. If this difference is more than maxsize, then update the maxsize.
7) To handle corner cases (all 1s and all 0s), we initialize maxsize as -1. If the maxsize remains -1,
  then print there is no such subarray.
 */
pair<int,int> largestEqualSubarray(const uint a[], const uint n) {
  if (n < 2) {
    return {-1,-1};
  }

  // Create an auxiliary array sumleft[]. sumleft[i] will be sum of array elements from a[0] to a[i]
  uint32_t sumLeft[n];

// Fill sumleft array and get min and max values in it. Consider 0 values in arr[] as -1
  sumLeft[0] = !a[0] ? -1 : 1;
  uint minSum = a[0];
  uint maxSum = a[0];

  for (uint i = 1; i < n; ++i) {
    sumLeft[i] = sumLeft[i-1]+(!a[i] ? -1 : 1);
    minSum = min(sumLeft[i], minSum);
    maxSum = max(sumLeft[i], maxSum);
  }

  // Now calculate the max value of j-i such that sumleft[i] = sumleft[j].
  // The idea is to create a hash table to store indexes of all visited values.
  // If you see a value again, that it is a case of sumleft[i] = sumleft[j].
  // Check if this j-i is more than maxsize. The optimum size of hash will be max-min+1
  // as these many different values of sumleft[i] are possible. Since we use optimum size,
  // we need to shift all values in sumleft[] by min before using them as an index in hash[].
  int hash[maxSum-minSum+1];
  for (auto& i : hash) {
    i = -1;
  }

  uint maxLen = 0, start = 0;

  for (uint i = 0; i < n; ++i) {
    // Case 1: when the subarray starts from index 0
    if (!sumLeft[i]) {
      maxLen = i+1;
      start = 0;
    }

    // Case 2: fill hash table value. If already filled, then use it
    if (hash[sumLeft[i]-minSum] == -1) {
      hash[sumLeft[i]-minSum] = i;
    } else {
      if ((i-hash[sumLeft[i]-minSum]) > maxLen) {
        maxLen = i-hash[sumLeft[i]-minSum];
        start = hash[sumLeft[i]-minSum]+1;
      }
    }
  }

  if (!maxLen) {
    cerr << "No such subarray" << endl;
  } else {
    return {start, start+maxLen-1};
  }
}

/*
Find sum of contiguous subarray within an array of numbers which has largest sum.
 */
void largestSubarraySum(const int a[], const uint n) {
  if (!n) {
    throw exception();
  }

  int largest = MIN_LMT;
  int iSum = 0;
  uint start = 0, end = 0;

  for (uint i = 0; i < n; ++i) {
    // iSum: sum of contiguous subarray before i, either starting from 0 or not
    iSum += a[i]; // expands to i-th element
    if (iSum < largest) {
      end = i-1;
    } else {
      end = i;
    }

    largest = max(iSum, largest);

    if (iSum < 0) {
      start = min(i+1, n-1);
      end   = min(i+1, n-1);
    }

    iSum = max(0, iSum); // if current subarray sum is negative, remove it since next element as a subarry will only have bigger sum (which is a[i+1]). new contiguous subarray starts from i+1
  }

  cout << "Subarray starts from " << start << " and ends at " << end << " with largest sum " << largest << endl;
}

/*
Determine whether a given array can be partitioned into two subarrays such that the sum of elements
in both is same.
 */
bool checkPartition(const int a[], const uint n) {
  if (n < 2) {
    return false;
  }

  int sum = 0;
  for (uint i = 0; i < n; ++i) {
    sum += a[i];
  }

  if (sum%2 != 0) {
    return false;
  }

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

int main(int argc, char** argv) {
  // int a[] = {1, 2, -3, 1, 5, -5, 6};
  int a[] = {-3,1,2,-2,4};
  pair<int,int> res = longest0SumSubarray(a, 7);
  for (uint i = res.first; i < res.second; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;

  int b[] = {1,2,3,4,5,0,6};
  res = zeroSumSubarray(b, 7);
  for (uint i = res.first; i <= res.second; ++i) {
    cout << b[i] << " ";
  }
  cout << endl;

  int c[] = {0,4,4,0,0,2,4,4};
  cout << "Smallest subarray length: " << smallestSubarray(c, 8, 7) << endl;

  uint d[] = {0,4,4,0,0,2,4,4};
  res = targetSumSubarray(d, 8, 10);
  if (res.first == -1) {
    cout << "No such subarray!" << endl;
  } else {
    cout << "Subarray starts at " << res.first << " and ends at " << res.second << endl;
  }

  //targetSumSubarray_2(a, 8, 10);

  int e[] = {1,2,-3,1};
  cout << "Largest difference between two non-overlapping subarrays: " << maxDiffSubarrays(e, 4) << endl;

  uint f[10] = {1,1,1,1,1,0,0,0,0,0};
  res = largestEqualSubarray(f, 10);
  cout << "Largest subarray starts from " << res.first << " and ends at " << res.second << endl;

  int g[] = {-2,-3,-4,-1,-2,-1,-5,-3};
  largestSubarraySum(g, 8);

  bool can = checkPartition(e, 4);
  cout << (can ? "Yes" : "No") << endl;

  return 0;
}
