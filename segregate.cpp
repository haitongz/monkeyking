#include <iostream>
#include <vector>

using namespace std;

/*
Given an array A[], write a function that segregates even and odd numbers.
The functions should put all even numbers first, and then odd numbers.

Input = {12, 34, 45, 9, 8, 90, 3}
Output = {12, 34, 8, 90, 45, 9, 3}
 */
void segregate(vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return;

  uint32_t low = 0;
  int32_t high = n-1;

  while (low < high) {
    while (a[low]%2 == 0 && low < high)
      ++low;
    while (a[high]%2 != 0 && low < high)
      --high;

    if (low < high)
      swap(a[low++], a[high--]);
  }
}

/*
Given an array of positive integers.
All numbers occur even number of times except one number which occurs odd number of times.
Find the number in O(n) time & constant space.
 */
uint32_t oddOccurNum(const vector<uint32_t>& a) {
  const uint32_t n = a.size();
  uint32_t ret = 0;

  for (uint32_t i = 0; i < n; ++i)
    ret ^= a[i];

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
pair<uint32_t,uint32_t> largestSub(const uint8_t a[], const uint32_t n) {
  if (!n)
    return {};
  if (n < 2)
    return {};

  // Create an auxiliary array sumleft[]. sumleft[i] will be sum of array elements from a[0] to a[i]
  uint32_t sumleft[n];

// Fill sumleft array and get min and max values in it. Consider 0 values in arr[] as -1
  sumleft[0] = !a[0] ? -1 : 1;
  uint32_t min_sum = a[0];
  uint32_t max_sum = a[0];

  for (uint32_t i = 1; i < n; ++i) {
    sumleft[i] = sumleft[i-1]+(!a[i] ? -1 : 1);
    min_sum = min(sumleft[i], min_sum);
    max_sum = max(sumleft[i], max_sum);
  }

  // Now calculate the max value of j-i such that sumleft[i] = sumleft[j].
  // The idea is to create a hash table to store indexes of all visited values.
  // If you see a value again, that it is a case of sumleft[i] = sumleft[j].
  // Check if this j-i is more than maxsize. The optimum size of hash will be max-min+1
  // as these many different values of sumleft[i] are possible. Since we use optimum size,
  // we need to shift all values in sumleft[] by min before using them as an index in hash[].
  int32_t hash[max_sum-min_sum+1];
  for (auto& i : hash)
    i = -1;

  uint32_t max_len = 0, start_idx = 0;

  for (uint32_t i = 0; i < n; ++i) {
    // Case 1: when the subarray starts from index 0
    if (!sumleft[i]) {
      max_len = i+1;
      start_idx = 0;
    }

    // Case 2: fill hash table value. If already filled, then use it
    if (hash[sumleft[i]-min_sum] == -1)
      hash[sumleft[i]-min_sum] = i;
    else {
      if ((i-hash[sumleft[i]-min_sum]) > max_len) {
        max_len = i-hash[sumleft[i]-min_sum];
        start_idx = hash[sumleft[i]-min_sum]+1;
      }
    }
  }

  if (!max_len)
    cerr << "No such subarray" << endl;
  else
    return {start_idx, start_idx+max_len-1};
}

int main(int argc, char** argv) {
  vector<int32_t> a = {12, 34, 45, 9, 8, 90, 3};
  segregate(a);
  for (uint32_t i = 0; i < a.size(); ++i)
    cout << a[i] << ",";
  cout << endl;

  uint8_t b[10] = {1,1,1,1,1,0,0,0,0,0};
  pair<uint32_t,uint32_t> res = largestSub(b, 10);
  cout << "Largest subarray starts from " << res.first << " and ends at " << res.second << endl;

  return 0;
}
