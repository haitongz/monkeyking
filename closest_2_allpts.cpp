#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();

/*
Given a two dimensional array, obstacles are marked as '1', points are marked as 'P', empty cells are marked as '0'.
Given k points, find the cell with smallest distance sum to all points.
 */
typedef pair<uint32_t,uint32_t> Point;

Point closest2AllPts(const vector<vector<char>>& mat) {
  const uint32_t m = mat.size(), n = mat[0].size();
  if (!m || !n)
    return {};

  vector<Point> pts;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (mat[i][j] == 'P')
        pts.push_back({i,j});
    }
  }

  struct Node {
    uint32_t dist_sum {0};
    bool visited {false};
  };

  static const vector<pair<const int8_t,const int8_t>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
  vector<vector<Node>> nodes(m, vector<Node>(n));
  const uint32_t k = pts.size();

  for (uint32_t i = 0; i < k; ++i) {
    for (auto& j : nodes)
      for (auto& l : j)
        l.visited = false;

    deque<Point> q {pts[i]};
    deque<uint32_t> dists {0};
    nodes[pts[i].first][pts[i].second].visited = true;

    while (!q.empty()) {
      auto curr = q.front();
      q.pop_front();
      auto dist = dists.front();
      dists.pop_front();

      for (const auto& d : dirs) {
        Point newp = {d.first+curr.first, d.second+curr.second};
        if (newp.first < 0 || newp.second < 0 || newp.first >= m || newp.second >= n)
          continue;
        if (mat[newp.first][newp.second] == '1')
          continue;
        if (nodes[newp.first][newp.second].visited)
          continue;

        nodes[newp.first][newp.second].visited = true;
        nodes[newp.first][newp.second].dist_sum += dist+1;
        q.push_back(newp);
        dists.push_back(dist+1);
      }
    }
  }

  uint32_t min_sum = MAX_LMT;
  Point ret;
  for (uint32_t i = 0; i < m; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (mat[i][j] == '0') {
        if (nodes[i][j].dist_sum < min_sum) {
          min_sum = nodes[i][j].dist_sum;
          ret = {i,j};
        }
      }
    }
  }

  return ret;
}

/*
Given NxN matrix, -1 represent a closed room, MAX_LIMIT represents an open room, 0 represents a policeman. Return a NxN
matrix with each element representing shortest distance of nearest policeman.
 */
void policeRooms(vector<vector<int32_t>>& rooms) {
  const uint32_t n = rooms.size();
  if (!n)
    return;

  static const vector<pair<const int8_t,const int8_t>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
  set<Point> visited;
  deque<Point> q;
  deque<uint32_t> dists;

  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = 0; j < n; ++j) {
      if (!rooms[i][j]) {
        q.push({i,j});
        visited.insert({i,j});
        dists.push(0);
      }
    }
  }

  while (!q.empty()) {
    auto pos = q.front();
    q.pop();

    auto dist = dists.front();
    dists.pop();

    for (const auto& dir : dirs) {
      Point curr = {dir.first+pos.first, dir.second+pos.second};
      if (curr.first < 0 || curr.second < 0 || curr.first >= n || curr.second >= n)
        continue;

      if (visited.count(curr))
        continue;

      if (rooms[curr.first][curr.second] == -1) {
        visited.insert(curr);
        continue;
      }

      visited.insert(curr);
      dists.push(dist+1);
      q.push(curr);

      rooms[curr.first][curr.second] = min(rooms[curr.first][curr.second], dist+1);
    }
  }
}

int main(int argc, char** argv) {
  return 0;
}
