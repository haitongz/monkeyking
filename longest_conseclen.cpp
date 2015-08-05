/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

uint32_t longestConsecutivesLen(const vector<int32_t>& nums) {
  const uint32_t n = nums.size();
  if (!n)
    return 0;

  unordered_map<int32_t/*array element*/,uint32_t/*length of sequence this element is part of*/> recs;
  uint32_t ret = 0;

  for (uint32_t i = 0; i < n; ++i) {
    const int32_t v = nums[i];
    if (!recs.count(v)) {
      const uint32_t left_len = recs.count(v-1) ? recs[v-1] : 0;
      const uint32_t right_len = recs.count(v+1) ? recs[v+1] : 0;
      const uint32_t new_len = left_len+right_len+1;
      recs[v] = new_len;
      if (right_len)
        recs[v+right_len] = new_len;
      if (left_len)
        recs[v-left_len] = new_len;

      ret = max(ret, new_len);
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  int32_t a2[] = {100, 4, 200, 1, 3, 2};
  cout << "Longest consecutive elements sequence length is: " << longestConsecutivesLen(a2, 6) << endl;

  return 0;
}
