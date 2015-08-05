/*
Given a string having parenthesis like '(((X)) (((Y))))', we need to find the maximum depth of balanced parenthesis, like 4 in above example. Since 'Y' is surrounded by 4 balanced parenthesis.
 */
#include <iostream>
#include <stack>

using namespace std;

int32_t maxBalancedParenDepth(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return -1;

  int32_t ret = -1;
  stack<uint32_t> stk;

  for (uint32_t i = 0; i < len; ++i) {
    if (s[i] == '(') {
      stk.push(i);
      ret = max(ret, stk.size());
    } else if (s[i] == ')') {
      if (s[stk.top()] == '(')
        stk.pop();
      else
        stk.push(i);
    }
  }

  return ret;
}

int32_t maxBalancedParenDepth(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return -1;

  uint32_t current_max = 0; // current count
  uint32_t ret = 0;    // overall maximum count

  for (auto i : s) {
    if (i == '(') {
      ++current_max;

      // update max if required
      ret = max(ret, current_max)
    } else if (i == ')') {
      if (current_max > 0)
        --current_max;
      else
        return -1;
    }
  }

  // finally check for unbalanced string
  if (current_max)
    return -1;

  return ret;
}
