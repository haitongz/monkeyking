/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1,
find the area of largest rectangle in the histogram.

Solution:

For search the leftmost higher bar, search from left to right.
Use stack to store the position of leftmost bar which has smaller height than current bar.
Then we can calculate the width to the left. Similarly, we can search the rightmost higher bar.

For example, [2, 1, 5, 6, 2, 3].

First of all, for the first element, the leftmost bar is itself. Push the position 0 to the stack. The stack is [0].
For the second element 1, since 1 < 2, we pop out the position 0 and find that the leftmost bar is the first one.
                          Then push the position 1 to the stack. The stack is [1].
For the third element 5, since 5 > 1, the leftmost bar is itself. Push the position 2 to the stack. The stack is [1, 2].
For the fourth element 6, since 6 > 5, the leftmost bar is itself. Push the position 3 to the stack. The stack is [1, 2, 3].
For the fifth element 2, since 2 < 6, 2 < 5, 2 > 1, we pop out the positions 3 and 2.
                         The leftmost bar is the third element 5. Push the position 5. The stack is [1, 5].
For the last element 3, since 3 > 2, the leftmost bar is itself. Push the position 6.

Then search from right to the left to find the rightmost bar.

We observe that each element will be push and pop once. So the time complexity is O(n) instead of O(n^2).
 */
#include <iostream>
#include <stack>

using namespace std;

int largestRectangle(const uint hs[], const uint n) {
  if (!n) {
    return -1;
  }

  uint newHs[n+1];
  for (uint i = 0; i < n; ++i) {
    newHs[i] = hs[i];
  }
  newHs[n] = 0;

  stack<uint> stk;
  int ret = 0;

  for (uint i = 0; i < n; ++i) {
    uint idx = stk.top();
    if (stk.empty() || newHs[i] >= newHs[idx]) {
      stk.push(i);
    } else {
      stk.pop();
      ret = max(ret,
                (int)(newHs[idx]*(stk.empty() ? i : (i-stk.top()-1))));
      --i; // pay attention
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  uint heights[] = {2,1,5,6,2,3,1,1,0,1,1};
  cout << "Largest rectangle is: " << largestRectangle(heights, 11) << endl;

  return 0;
}
