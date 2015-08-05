/*
You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists.

For example,
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]

The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// first: array id, second: element id
pair<int32_t,int32_t> min_range(const vector<vector<int32_t>>& nums) {
  using _pair = pair<int32_t,int32_t>;
  priority_queue<_pair,vector<_pair>,function<bool(_pair&,_pair&)>> heap {
    [&](_pair& a, _pair& b) { return nums[a.first][a.second] >= nums[b.first][b.second]; }
  };

  int32_t curr_max = numeric_limits::min();
  for (auto i = 0; i < nums.size(); ++i) {
    if (nums[i].empty())
      continue;

    heap.emplace(i, 0);
    curr_max = max(curr_max, nums[i][0]);
  }

  if (heap.empty())
    return {-1, -1};

  int32_t begin = nums[heap.top().first][heap.top().second];
  uint32_t min_len = curr_max-begin;

  while (heap.size() == nums.size()) {
    auto top = heap.top();
    heap.pop();

    if (top.second+1 < nums[top.first].size()) {
      int32_t new_begin = nums[heap.top().first][heap.top().second];
      int32_t new_num = nums[top.first][top.second+1];
      new_begin = min(new_begin, new_num);
      curr_max  = max(cur_max, new_num);
      if (curr_max-new_begin < min_len) {
        begin = new_begin;
        min_len = curr_max - new_begin;
      }

      heap.emplace(top.first, top.second+1);
    }
  }

  return {begin, begin+min_len};
}

int main(int argc, char** argv) {
  pair<int32_t,int32_t> res = min_range({{1,2,4,8,14,20}, {6,10,21,25,30}, {3,7,9,15,25}});
  res = min_range({{1,2,3}, {5,10}, {4,12}});
  res = min_range({{1,2,3}, {5,10}});
  res = min_range({{1,2,3}, {10}});
  res = min_range({{4,10,15,24,26}, {0,9,12,20}, {5,18,22,30}});
  return 0;
}
