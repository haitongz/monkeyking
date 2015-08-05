/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;
struct Point {
  uint32_t x;
  uint32_t y;
  Point() : x(0), y(0) {
  }
  Point(const uint32_t a, const uint32_t b) : x(a), y(b) {
  }
};

bool isSame(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

/*
uint32_t samePoints(const uint32_t pos, const vector<Point>& points) {
  uint32_t res = 1;
  for (uint32_t i = pos+1; i < points.size(); ++i) {
    if (isSame(points[pos], points[i])) {
      ++res;
    }
  }

  return res;
}

uint32_t maxPointsOnALine(const vector<Point>& points) {
  map<double, uint32_t> ump_di1;
  map<double, uint32_t> ump_di2;
  uint32_t same_ps = samePoints(0, points);
  if (same_ps == points.size())
    return same_ps;

  for (uint32_t i = 0; i < points.size(); ++i) {
    for (uint32_t j = i+1; j < points.size(); ++j) {
      if (isSame(points[i], points[j]))
        continue;

      double a = points[i].x - points[j].x;
      double b = points[i].y - points[j].y;
      double k = (a == 0.0) ? INF : b/a;
      if (ump_di1.count(k)) {
        if (ump_di1[k] != i)
          continue;
      } else {
        ump_di1[k] = i;
        ump_di2[k] = same_ps;
      }
      ++ump_di2[k];
    }

    same_ps = samePoints(i+1, points);
  }

  int max_ps = 0;
  for (auto x:ump_di2)
    max_ps = max(max_ps, x.second);
  return max_ps;
}
*/

uint32_t maxPoints(const vector<Point>& points) {
  const uint32_t n = points.size();
  if (!n)
    return 0;

  function<int32_t(const int32_t,const int32_t)> gcd =
    [](const int32_t x, const int32_t y) {
    return x ? gcd(y%x, x) : y;
  };

  uint32_t res = 0;

  for (uint32_t i = 0; i < n; ++i) {
    map<pair<uint32_t,uint32_t>,uint32_t> recs;
    uint32_t same_pt = 1, max_val = 0;

    for (uint32_t j = i+1; j < n; ++j) {
      int32_t x = points[i].x - points[j].x;
      int32_t y = points[i].y - points[j].y;
      auto g = gcd(x, y);
      if (!g) {
        ++same_pt;
        continue;
      }

      max_val = max(max_val, ++recs[make_pair(x/g, y/g)]);
    }

    res = max(res, max_val+same_pt);
  }

  return res;
}

int main(int argc, char** argv) {
}
