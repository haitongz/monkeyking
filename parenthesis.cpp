#include <iostream>
#include <vector>
#include <functional>
#include <stack>

using namespace std;

/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
 */
uint32_t longestValidParenLen(const string& s) {
  const uint32_t len = s.length();
  if (len < 2)
    return 0;

  stack<uint32_t> stk;
  uint32_t res = 0;

  for (uint32_t i = 0; i < len; ++i) {
    const char c = s[i];
    if (c == '(') {
      stk.push(i);
    } else if (c == ')') {
      if (stk.empty()) {
        stk.push(i); // can't return here since it can be ')()'
      } else {
        uint32_t idx = stk.top();
        if (s[idx] == '(') { // top is left parenthesis, match off
          stk.pop();
          idx = stk.top();
          res = stk.empty() ? max(res, i+1) : max(res, i-idx);
        } else { // left top is right parenthesis, can't match off
          stk.push(i);
        }
      }
    } else {
      throw exception();
    }
  }

  return res;
}

uint32_t longestValidParenLen_dp(const string& s) {
  const uint32_t len = s.length();
  if (len < 2)
    return 0;

  vector<uint32_t> dp(len+1, 0);
  uint32_t ret = 0;

  for (uint32_t i = 1; i < len; ++i) {
    if (s[i] == ')' && s[i-dp[i]-1] == '(') {
      dp[i+1] = dp[i]+dp[i-dp[i]-1]+2;
      ret = max(ret, dp[i+1]);
    }
  }

  return ret;
}

/*
Given a string with parentheses, return a string with balanced parentheses by removing the fewest characters possible. You cannot add anything to the string.

Examples:
balance("()") -> "()"
balance(")(") -> "".
balance("(((((") -> ""
balance("(()()(") -> "()()"
balance(")(())(") -> "(())"

Note: balance(")(())(") != "()()"
 */
string balance(const string& s) {
  const uint32_t len = s.length();
  if (len < 2)
    return "";

  stack<uint32_t> stk;
  bool to_rm[len];
  for (auto& i : to_rm)
    i = false;

  for (uint32_t i = 0; i < len; ++i) {
    const char c = s[i];
    if (c == '(') {
      stk.push(i);
    } else if (c == ')') {
      if (stk.empty())
        to_rm[i] = true;
      else
        stk.pop();
    } else {
      throw exception();
    }
  }

  while (!stk.empty()) {
    const uint32_t idx = stk.top();
    to_rm[idx] = true;
    stk.pop();
  }

  string res;
  for (uint32_t i = 0; i < len; ++i) {
    if (!to_rm[i])
      res += s[i];
  }

  return res;
}

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
For example, given n = 3, a solution set is:
"((()))", "(()())", "(())()", "()(())", "()()()"
 */
vector<string> generateParentheses(const uint32_t n) {
  if (!n)
    return {};

  vector<string> res;

  function<void(const uint32_t,const uint32_t,const string&)> dfs =
    [&](const uint32_t left_num, const uint32_t right_num, const string& curr) {
    if (curr.size() == 2*n) {
      res.push_back(curr);
      return;
    }

    if (right_num < left_num)
      dfs(left_num, right_num+1, curr+")");
    if (left_num < n)
      dfs(left_num+1, right_num, curr+"(");
  };

  dfs(1, 0, "(");
  return res;
}

/*
Given a string having parenthesis like '(((X)) (((Y))))', we need to find the maximum depth of balanced parenthesis, like 4 in above example. Since 'Y' is surrounded by 4 balanced parenthesis.
 */
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

int32_t maxBalancedParenDepth_2(const string& s) {
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

int main(int argc, char** argv) {
  const string s = ")()())";
  cout << "Longest valid parentheses length: " << longestValidParenLen(s) << endl;
 // cout << "Longest valid parentheses length: " << longestValidParenLen(s) << endl;
  cout << "Longest valid parentheses length: " << longestValidParenLen_dp(s) << endl;

  cout << balance("()") << endl;
  cout << balance(")(") << endl;
  cout << balance("(((((") << endl;
  cout << balance("(()()(") << endl;
  cout << balance(")(())(") << endl;
  cout << balance("(()))(()") << endl;
  cout << balance("(((()()(()))(((()()") << endl;

  vector<string> res = generateParentheses(3);
  for (auto& i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
