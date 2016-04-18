#include <iostream>
#include <limits>
#include <vector>
#include <functional>
#include <map>

using namespace std;

static const int MAX_LMT = numeric_limits<int>::has_infinity ?
                           numeric_limits<int>::infinity() : numeric_limits<int>::max();

static const int MIN_LMT = numeric_limits<int>::has_infinity ?
                           -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
For example:
A = [2,3,1,1,4], return true.
A = [3,2,1,0,4], return false.
 */
bool canJump(const vector<uint>& A) {
  const uint n = A.size();
  if (!n)
    return false;

  uint reach = 0;
  for (uint i = 0; i <= reach /*no need to continue if there's a gap*/&& i < n; ++i) {
    reach = max(i+A[i], reach);
  }

  if (reach < n-1)
    return false;
  return true;
}

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

Given array A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
 */
uint minJumps_recur(const vector<uint>& A) {
  const uint n = A.size();
  if (!n)
    return MAX_LMT;

  function<uint(const uint,const uint)> solve = // DFS
    [&](const uint start, const uint end) -> uint {
    // when source and destination are same
    if (start == end)
      return 0;

    // When nothing is reachable from the given source
    if (!A[start])
      return MAX_LMT;

    // Traverse through all the points reachable from A[l].
    // Recursively get the minimum number of jumps needed to reach arr[h] from these reachable points.
    uint ret = MAX_LMT;

    for (uint i = start+1; i < end+1 && i < start+A[start]+1; ++i) {
      uint jumps = solve(i, end);
      if (jumps != MAX_LMT)
        ret = min(ret, jumps+1);
    }

    return ret;
  };

  return solve(0, n-1);
}

uint minJumps_dp(const vector<uint>& A) {
  const uint n = A.size();
  if (!n || !A[0])
    return MAX_LMT;

  uint dp[n];
  dp[0] = 0;
  for (uint i = 1; i < n; ++i) {
    dp[i] = MAX_LMT;

    for (uint j = 0; j < i; ++j) {
      if (i <= j+A[j] && dp[j] != MAX_LMT) {
        dp[i] = min(dp[i], dp[j]+1);
        break;
      }
    }
  }

  return dp[n-1];
}

/*
Given a binary array R representing a river: 0 means water and 1 means stone.
Initial position R[0] is 1, initial speed is 1. You can choose to jump at old speed, or at speed+1 for next move.
Find minimum number of steps to jump river.
 */
uint minRiverJumps_recur(const vector<uint8_t>& R) {
  if (R.empty())
    return 0;

  map<pair<uint,uint>,int> recs;

  function<int(const uint, const uint)> solve = // DFS
    [&](const uint speed, const uint idx) -> int {
    if (idx >= R.size())
      return 0;

    if (recs.count({idx,speed}))
      return recs[{idx,speed}];

    int ret = -1;
    if (R[idx]) {
      int res0 = solve(speed, idx+speed);
      int res1 = solve(speed+1, idx+speed+1);

      if (res0 >= 0 && res1 >= 0) {
        ret = min(res0, res1) + 1;
      } else if (res0 < 0 && res1 < 0) {
        ret = -1;
      } else {
        ret = max(res0, res1) + 1;
      }
    }

    recs[{idx,speed}] = ret;
    return ret;
  };

  return solve(1, 0);
}

int minRiverJumps_dp(const vector<uint8_t>& R) {
  const uint n = R.size();
  if (!n)
    return 0;

  vector<vector<pair<uint,uint>>> dp(n);
  dp[0].emplace_back(1, 1);

  uint ret = MAX_LMT;

  for (auto i = 0; i < n; ++i) {
    if (!R[i])
      continue;

    for (auto pr : dp[i]) {
      if (i+pr.first >= n) {
        ret = min(pr.second, ret);
      } else if (R[i+pr.first]) {
        dp[i+pr.first].emplace_back(pr.first, pr.second+1);
      }
      if (i+pr.first+1 >= n) {
        ret = min(pr.second, ret);
      } else if (R[i+pr.first+1]) {
        dp[i+pr.first+1].emplace_back(pr.first+1, pr.second+1);
      }
    }
  }

  return (ret == MAX_LMT) ? -1 : (int)ret;
}

int main(int argc, char** argv) {
  vector<uint> A = {2, 3, 1, 1, 4};
  vector<uint> B = {3, 2, 1, 0, 4};

  cout << "Can reach end? " << (canJump(A) ? "true" : "false") << endl;
  cout << "Can reach end? " << (canJump(B) ? "true" : "false") << endl;
  cout << "Minimum jumps to reach last index: " << minJumps_dp(A) << endl;
  cout << "Minimum jumps to reach last index: " << minJumps_recur(A) << endl;

  vector<uint8_t> R = {1, 1, 1, 0, 1, 1, 0, 0};
  cout << "Minimum jumps to cross river: " << minRiverJumps_recur(R) << endl;
  cout << "Minimum jumps to cross river: " << minRiverJumps_dp(R) << endl;

  return 0;
}
