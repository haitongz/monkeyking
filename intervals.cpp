#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 */
struct Interval {
  Interval(const uint s, const uint e)
    : start(s), end(e) {
  }

  uint start, end;
};

vector<Interval>
insertMerge(vector<Interval>& itvls, Interval nv) {
  const uint n = itvls.size();
  if (!n)
    return {nv};

  uint idx = 0;
  vector<Interval> ret;

  while (idx < n && itvls[idx].end < nv.start) {
    ret.push_back(itvls[idx++]);
  }

  while (idx < n && nv.end >= itvls[idx].start) {
    nv.start = min(nv.start, itvls[idx].start);
    nv.end = max(nv.end, itvls[idx].end);
    ++idx;
  }

  ret.push_back(nv);
  copy((itvls.begin()+idx), itvls.end(), back_inserter(ret));

  return ret;
}

/*
Given a array of pairs where each pair contains the start and end time of a meeting (as in integer),
determine if a single person can attend all the meetings

Input array { pair(1,4), pair(4, 5), pair(3,4), pair(2,3) }
Output: false

Follow up:
determine the minimum number of meeting rooms needed to hold all the meetings.
(Or, giving lots of intervals [ai, bi], find a point intersect with the most number of intervals.)

Input array { pair(1, 4), pair(2,3), pair(3,4), pair(4,5) }
Output: 2
 */
bool canAttendAll(vector<Interval>& mtgs) {
  const uint n = mtgs.size();
  if (!n)
    return false;

  sort(mtgs.begin(), mtgs.end(), [&](const Interval& a, const Interval& b) {return a.start < b.start;});

  for (uint i = 1; i < n; ++i) {
    if (mtgs[i].start < mtgs[i-1].end) {
      return false;
    }
  }

  return true;
}

uint minRooms(vector<Interval>& mtgs) {
  const uint n = mtgs.size();
  if (!n)
    return 0;

  vector<int> times;

  for (const auto& m : mtgs) {
    times.push_back(m.start);
    times.push_back(-m.end);
  }

  sort(times.begin(), times.end(), [](const int a, const int b) {return (abs(a) == abs(b)) ? (a < b) : (abs(a) < abs(b));});

  uint ret = 0, curr = 0;

  for (const auto t : times) {
    if (t >= 0) {
      ret = max(ret, ++curr);
    } else {
      --curr;
    }
  }

  return ret;
}

/*
There are n pairs of numbers. In every pair, the first number is always smaller than the second number.
A pair (c, d) can follow another pair (a, b) if b < c. Chain of pairs can be formed in this fashion.
Find the longest chain which can be formed from a given set of pairs.

Given pairs {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}}, then the longest chain that can be formed is of length 3,
and the chain is {{5, 24}, {27, 40}, {50, 90}}
 */
struct Pair {
  Pair(const int s, const int e)
      : a(s), b(e) {
  }

  int a, b;
};

bool operator<(const Pair& p1, const Pair& p2) {
  return p1.b < p2.b;
}

uint maxPairChainLen_greedy(vector<Pair>& p) {
  const uint n = p.size();
  if (n < 2)
    return n;

  sort(p.begin(), p.end());
  uint active_p = 0;
  uint ret = 1;

  for (uint i = 1; i < n; ++i) {
    if (p[i].a > p[active_p].b) {
      ++ret;
      active_p = i;
    }
  }

  return ret;
}

int main(int argc, char** argv)
{
  Interval i1(1, 3), i2(6, 9), i3(2, 5);
  vector<Interval> ivs;
  ivs.push_back(i1);
  ivs.push_back(i2);

  vector<Interval> res = insertMerge(ivs, i3);
  for (uint i = 0; i < res.size(); ++i) {
    cout << "[" << res[i].start << "," << res[i].end << "],";
  }
  cout << endl;

  i1 = Interval(1, 2);
  i2 = Interval(3, 5);
  i3 = Interval(6, 7);
  Interval i4(8, 10), i5(12, 16);
  ivs.clear();
  ivs.push_back(i1);
  ivs.push_back(i2);
  ivs.push_back(i3);
  ivs.push_back(i4);
  ivs.push_back(i5);
  res = insertMerge(ivs, Interval(4, 9));
  for (uint i = 0; i < res.size(); ++i) {
    cout << "[" << res[i].start << "," << res[i].end << "],";
  }
  cout << endl;

  ivs.pop_back();
  ivs.pop_back();
  ivs[0] = Interval(1, 4);
  ivs[1] = Interval(4, 5);
  ivs[2] = Interval(3, 4);
  ivs[3] = Interval(2, 3);
  cout << "A person " << (canAttendAll(ivs) ? "can" : "cannot") << " attend all meetings." << endl;

  ivs[1] = Interval(2, 3);
  ivs[3] = Interval(4, 5);
  cout << "Min room needed: " << minRooms(ivs) << endl;

  vector<Pair> p = {Pair(5, 24), Pair(39, 60), Pair(15, 28), Pair(27, 40), Pair(50, 90)};
  cout << "Longest chain of pairs length: " << maxPairChainLen_greedy(p) << endl;

  return 0;
}
