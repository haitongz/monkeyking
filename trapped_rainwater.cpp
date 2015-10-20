/*
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 */
#include <iostream>
#include <vector>

using namespace std;

uint32_t trappedRainwater(const vector<uint32_t>& heights) {
  const uint32_t n = heights.size();
  if (!n)
    return 0;

  uint32_t left_edge[n], right_edge[n], res = 0;
  left_edge[0] = heights[0];
  right_edge[n-1] = heights[n-1];

  for (uint32_t i = 1; i < n; ++i) { // scan from both ends
    left_edge[i] = max(heights[i], left[i-1]);
    right_edge[n-i-1] = max(heights[n-i-1], right[n-i]);
  }

  for (uint32_t i = 0; i < n; ++i) {
    res += min(left_edge[i], right_edge[i])-heights[i]; // could be zero
  }

  return res;
}

int main(int argc, char** argv) {
  vector<uint32_t> a = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  cout << "Rainwater trapped: " << trappedRainwater(a) << endl;
  //cout << "Rainwater trapped: " << trappedRainwater2(a, 12) << endl;
}
