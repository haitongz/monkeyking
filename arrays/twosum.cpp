#include <iostream>
#include <limits>

using namespace std;

namespace {
  const int MAX_LMT = numeric_limits<int>::has_infinity ?
                      numeric_limits<int>::infinity() : numeric_limits<int>::max();
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
  if (!n) {
    return {-1,-1};
  }

  map<int,int> mem;
  pair<int,int> ret;

  for (uint i = 0; i < n; ++i) {
    const int remains = target-a[i];
    if (mem.count(remains)) {
      ret.first = mem[remains]+1; // index1 and index2 are not zero-based.
      ret.second = i+1;
      return ret;
    }

    mem[a[i]] = i;
  }

  return ret;
}

/*
Given a sorted array and a number x, find a pair in array whose sum is closest to x.
 */
pair<uint,uint>
twoSumClosest(int a[], const uint n, const int x) {
  if (!n) {
    return {-1,-1};
  }

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
    if (a[left]+a[right] > x) {
      --right;
    } else { // Move to larger values
      ++left;
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<int> S = {-1, 2, 1, -4};
  cout << "Closest sum: " << threeSumClosest(S, 1) << endl;

  return 0;
}
