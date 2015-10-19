/*
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
Find two lines, which together with x-axis forms a container, such that the container contains the most water.
Note: You may not slant the container.
 */
#include <iostream>
#include <set>
#include <queue>
#include <vector>

using namespace std;

uint32_t maxWater(const vector<uint32_t>& heights) {
  const uint32_t n = heights.size();
  if (!n)
    return 0;

  auto area = [&](const uint32_t left, const uint32_t right) {
    return min(heights[left], heights[right])*(right-left);
  };

  uint32_t res = 0;
  uint32_t l = 0, r = n-1;
  while (l < r) {
    res = max(area(l, r), res);
    if (height[l] <= height[r]) {
      ++l;
    } else {
      --r;
    }
  }

  return res;
}

int main(int argc, char** argv) {
}
