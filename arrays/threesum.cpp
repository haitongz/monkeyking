/*
Given an array S of n integers, find three integers in S such that
the sum is closest to a given number target. Return the sum of the three integers.
You may assume that each input would have exactly one solution.

Given array S = {-1 2 1 -4}, and target = 1.
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

namespace {
  const uint MAX_LMT = numeric_limits<uint>::has_infinity ?
                       numeric_limits<uint>::infinity() : numeric_limits<uint>::max();
}

int threeSumClosest(vector<int>& S, const int target) {
  const uint n = S.size();
  if (n < 3) {
    throw exception();
  }

  sort(S.begin(), S.end());

  int ret = 0;
  uint diff = MAX_LMT;

  for (uint i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i]) {
      continue;
    }

    uint left = i+1, right = n-1;

    while (left < right) {
      int currSum = S[i]+S[left]+S[right];
      uint currDiff = abs(currSum-target);
      if (currDiff < diff) {
        diff = currDiff;
        ret = currSum;
      }

      if (currSum < target) {
        ++left;
      } else if (currSum > target) {
        --right;
      } else {
        return target;
      }
    }
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
set<vector<int>> threeZeroSum(vector<int>& S) {
  const uint n = S.size();
  if (n < 3)
    return {};

  sort(S.begin(), S.end());

  set<vector<int>> ret; // indices

  for (uint i = 0; i < n; ++i) {
    if (i > 0 && S[i-1] == S[i]) { // since we scan from left to right, all a[i] cases were covered in a[i-1] cases already
      continue;
    }

    for (uint j = i+1, k = n-1; j < k;) {
      const int sum = S[i]+S[j]+S[k];
      if ((j > i+1 && S[j] == S[j-1]) || sum < 0) {
        ++j;
      } else if ((k < n-1 && S[k] == S[k+1]) || sum > 0) {
        --k;
      } else {
        ret.insert({S[i], S[j++], S[k--]});
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  vector<int> S = {-1, 2, 1, -4};
  cout << "Closest sum: " << threeSumClosest(S, 1) << endl;

  S = {-1, 0, 1, 2, -1, -4};
  set<vector<int>> res = threeZeroSum(S);
  for (const auto& i : res) {
    for (const auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  return 0;
}
