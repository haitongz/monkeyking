/*
Find the K closest points to the origin in 2D plane
 */
#include <iostream>
#include <vector>

using namespace std;

// time complexity O(nlogk);
/*
struct Point {
  double x, y;

  double distanceFromOrigin() {
    return (x*x + y*y); // there is no need add the square root overhead as we only need to compare the distance
  }

  int32_t compareTo(const Point& p2) {
    double dist1 = distanceFromOrigin();
    double dist2 = p2.distanceFromOrigin();

    if (dist1 < dist2)
      return -1;
    else if (dist1 > dist2)
      return 1;
    else
      return 0;
  }
};

vector<Point> kCloestPoints(vector<Point>& pts, const uint32_t K) {
  if (!K)
    return {};

  priority_queue<Point> heap(K);

  for (auto& curr : pts) {
    heap.add(curr.distanceFromOrigin());
    if (heap.size() > k) {
      heap.pop();
    }
  }

  vector<Point> ret(K);
  Point pollNode;
  uint32_t idx = 0;

  while (heap.size() > 0) {
    pollNode = heap.top();
    heap.pop();

    ret[idx] = pollNode;
    ++idx;
  }

  return ret;
}
*/
/*
given an array of n points in the plane, and the problem is to find out the closest pair of points in the array.
 */
pair<pair<float,float>,pair<float,float>> closestPair(vector<pair<float,float>>& A) { // O(nlogn)
  const uint32_t n = A.size();
  if (!n)
    return {};

  function<float(const pair<int32_t,int32_t>&,const pair<int32_t,int32_t>&)> dist =
    [&](const pair<int32_t,int32_t> A, const pair<int32_t,int32_t>& B) {
    float xdif = pow(A.first-B.first, 2);
    float ydif = pow(A.second-B.second, 2);
    xdif += ydif;
    return sqrt(xdif);
  };

  function<pair<pair<float,float>,pair<float,float>>(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t L, const uint32_t R) {
    float min = MIN_LIMIT;
    pair<pair<float,float>,pair<float,float>> ret;

    if (R-L <= 4) {
      for (uint32_t i = L+1; i < R+1; ++i) {
        for (uint32_t j = L; j < i; ++j) {
          if (dist(A[i], A[j]) < min) {
            min = dist(A[i], A[j]);
            ret = make_pair(A[i], A[j]);
          }
        }
      }
    } else {
      uint32_t mid = floor((R+L)/2);
      pair<pair<float,float>,pair<float,float>> Ch = solve(L, mid);
      pair<pair<float,float>,pair<float,float>> Ra = solve(mid+1, R);
      float LM = dist(Ch.first, Ch.second);
      float RM = dist(Ra.first, Ra.second);

      for (uint32_t i = L; i <= mid; ++i) {
        for (uint32_t j = mid+1; j <= R; ++j) {
          if (dist(A[i], A[j]) < min) {
            min = dist(A[i], A[j]);
            ret = make_pair(A[i], A[j]);
          }
        }
      }

      if (LM < min || RM < min)
        return RM < LM ? Ra : Ch;
    }

    return ret;
  };

  return solve(0, n-1);
}

/*
Write a function that takes the following inputs and gives the following outputs.

Input: A list of points in 2-dimensional space, and an integer k
Output: The k input points closest to (5, 5), using Euclidean distance

Example:
Input: {(-2, -4), (0, 0), (10, 15), (5, 6), (7, 8), (-10, -30)}, k = 2
Output: {(5, 6), (7, 8)}
 */
struct Point {
  int32_t x, y;
  int32_t distance(const Point& p) {
    return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
  }
  Point(const int32_t x_, const int32_t y)
      : x(x_), y(y_) {
  }
};

vector<Point> kClosestPoints(const vector<Point>& pts, const uint32_t k) {
  const uint32_t n = pts.size();
  if (!n || !k || n < k)
    return pts;

  Point origin(5, 5);
  vector<Point> heap(pts.begin(), pts.begin()+k);

  auto comp = [&](const Point& p1, const Point& p2) -> bool {
    return origin.distance(p1) < origin.distance(p2);
  };

  make_heap(heap.begin(), heap.end(), comp);

  for (uint32_t i = k; i < n; ++i) {
    heap.push_back(pts[i]);
    push_heap(heap.begin(), heap.end(), comp);
    pop_heap(heap.begin(), heap.end(), comp);
    heap.pop_back();
  }

  return heap;
}

// Driver program to test above functions
int main(int argc, char** argv) {
  Point P[] = {{2,3},{12,30},{40,50},{5,1},{12,10},{3,4}};
  const uint32_t n = sizeof(P)/sizeof(P[0]);
  cout << "The smallest distance is " << closest(P, n) << endl;

  return 0;
}
