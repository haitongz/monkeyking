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
  uint32_t start, end;

  Interval(const uint32_t s, const uint32_t e)
      : start(s), end(e) {
  }
};
/*
vector<Interval> insert(vector<Interval>& itvls, Interval nv) {
  vector<Interval> res;
  uint32_t i = 0;

  for (; i < itvls.size() && itvls[i].end < nv.start; ++i) {
    res.push_back(itvls[i]);
  }

  if (i == itvls.size()) {
    res.push_back(nv);
    return res;
  }

  nv.start = min(nv.start, itvls[i].start);
  for (; i < itvls.size() && itvls[i].start <= nv.end; ++i) {
    nv.end = max(nv.end, itvls[i].end);
  }
  res.push_back(nv);

  for (; i < itvls.size(); ++i) {
    res.push_back(itvls[i]);
  }

  return res;
}
*/
vector<Interval> insert(vector<Interval>& itvls, Interval nv) {
  const uint32_t n = itvls.size();
  if (!n)
    return {nv};

  uint32_t idx = 0;
  vector<Interval> res;

  while (idx < n && itvls[idx].end < nv.start) {
    res.push_back(itvls[idx++]);
  }

  while (idx < n && nv.end >= itvls[idx].start) {
    nv.start = min(nv.start, itvls[idx].start);
    nv.end = max(nv.end, itvls[idx].end);
    ++idx;
  }

  res.push_back(nv);
  copy((itvls.begin()+idx), itvls.end(), back_inserter(res));

  return res;
}
/*
vector<Interval> insert_2(vector<Interval>& itvls, Interval ni) {
  const uint32_t n = itvls.size();
  if (!n)
    return {ni};

  function<int32_t(const bool)> find = [&](const bool find_max) -> int32_t {
    if (!find_max && ni.start <= itvls.front().end)
      return -1;
    else if (find_max && ni.end >= itvls.back().start)
      return n;

    uint32_t left = 0, right = n-1;
    while (left <= right) {
      const uint32_t mid = left + (right-left)/2;
      if (itvls[mid].end < ni.start) {
        left = mid+1;
      } else if(itvls[mid].start > ni.end) {
        right = mid-1;
      } else {
        if (find_max)
          left = mid+1;
        else
          right = mid-1;
      }
    }

    return find_max ? left : right;
  };

  int32_t max_id = find(true), min_id = find(false);
  vector<Interval> res;

  copy(itvls.begin(), (itvls.end()-min_id), back_inserter(res));

  uint32_t new_start = ni.start, new_end = ni.end;
  int overlap_l = min_id+1, overlap_r = max_id-1;
  if(overlap_l <= overlap_r && overlap_r >= 0) {
    new_start = min(new_start, itvls[overlap_l].start);
    new_end = max(new_end, itvls[overlap_r].end);
  }

  res.emplace_back(new_start, new_end);
  copy((itvls.begin()+max_id+1), itvls.end(), back_inserter(res));

  return res;
}
*/
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
  const uint32_t n = mtgs.size();
  if (!n)
    return false;

  sort(mtgs.begin(), mtgs.end(), [&](Interval a, Interval b) {return a.start < b.start;});

  for (uint32_t i = 1; i < n; ++i) {
    if (mtgs[i].start < mtgs[i-1].end)
      return false;
  }

  return true;
}

uint32_t minRooms(vector<Interval>& mtgs) {
  const uint32_t n = mtgs.size();
  if (!n)
    return 0;

  vector<int32_t> times;

  for (auto m : mtgs) {
    times.push_back(m.start);
    times.push_back(-m.end);
  }

  sort(times.begin(), times.end(), [](int32_t a, int32_t b) { return (abs(a) == abs(b)) ? (a < b) : (abs(a) < abs(b)); });

  uint32_t res = 0, curr = 0;

  for (auto t : times) {
    if (t >= 0)
      res = max(res, ++curr);
    else
      --curr;
  }

  return res;
}

/*
There are n pairs of numbers. In every pair, the first number is always smaller than the second number.
A pair (c, d) can follow another pair (a, b) if b < c. Chain of pairs can be formed in this fashion.
Find the longest chain which can be formed from a given set of pairs.

Given pairs {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}}, then the longest chain that can be formed is of length 3,
and the chain is {{5, 24}, {27, 40}, {50, 90}}
 */
struct Pair {
  Pair(const int32_t s, const int32_t e)
      : a(s), b(e) {
  }

  int32_t a;
  int32_t b;
};

bool operator<(const Pair& p1, const Pair& p2) {
  return p1.b < p2.b;
}

uint32_t maxPairChainLen_greedy(vector<Pair>& p) {
  const uint32_t n = p.size();
  if (n < 2)
    return n;

  sort(p.begin(), p.end());
  uint32_t active_p = 0;
  uint32_t res = 1;

  for (uint32_t i = 1; i < n; ++i) {
    if (p[i].a > p[active_p].b) {
      ++res;
      active_p = i;
    }
  }

  return res;
}

int main(int argc, char** argv) {
  Interval i1(1, 3), i2(6, 9), i3(2, 5);
  vector<Interval> ivs;
  ivs.push_back(i1);
  ivs.push_back(i2);

  vector<Interval> res = insert(ivs, i3);
  for (uint32_t i = 0; i < res.size(); ++i) {
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
  res = insert(ivs, Interval(4, 9));
  for (uint32_t i = 0; i < res.size(); ++i) {
    cout << "[" << res[i].start << "," << res[i].end << "],";
  }
  cout << endl;

  ivs.pop_back();
  ivs.pop_back();
  ivs[0] = Interval(1, 4);
  ivs[1] = Interval(4, 5);
  ivs[2] = Interval(3, 4);
  ivs[3] = Interval(2, 3);
  cout << "A person " << (canAttendAll(ivs) ? "can " : "cannot ") << "attend all meetings." << endl;

  ivs[1] = Interval(2, 3);
  ivs[3] = Interval(4, 5);
  cout << "Min room needed: " << minRooms(ivs) << endl;

  vector<Pair> p = {Pair(5, 24), Pair(39, 60), Pair(15, 28), Pair(27, 40), Pair(50, 90)};
  cout << "Longest chain of pairs length: " << maxPairChainLen_greedy(p) << endl;

  return 0;
}
