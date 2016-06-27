/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.
 */
#include <iostream>
#include <map>

using namespace std;

uint longestConsecutivesLen(const int nums[], const uint n) {
  if (!n) {
    return 0;
  }

  map<int/*array element*/,uint/*length of sequence this element is part of*/> mem;
  uint ret = 0;

  for (uint i = 0; i < n; ++i) {
    const int v = nums[i];
    if (!mem.count(v)) {
      const uint leftLen = mem.count(v-1) ? mem[v-1] : 0;
      const uint rightLen = mem.count(v+1) ? mem[v+1] : 0;
      const uint newLen = leftLen+rightLen+1;
      mem[v] = newLen;
      if (rightLen) {
        mem[v+rightLen] = newLen;
      }
      if (leftLen) {
        mem[v-leftLen] = newLen;
      }

      ret = max(ret, newLen);
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  int a[] = {100, 4, 200, 1, 3, 2};
  cout << "Longest consecutive elements sequence length is: " << longestConsecutivesLen(a, 6) << endl;

  return 0;
}
