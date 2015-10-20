/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") -> false
isMatch("aa","aa") -> true
isMatch("aaa","aa") -> false
isMatch("aa", "a*") -> true
isMatch("aa", ".*") -> true
isMatch("ab", ".*") -> true
isMatch("aab", "c*a*b") -> true
 */
#include <iostream>
//#include <vector>
#include <cstring>
#include <functional>

using namespace std;
/*
bool isMatch_dp(const char* s, const char* p) {
  if (!s || !p)
    return false;

  const uint32_t s_len = strlen(s);
  const uint32_t p_len = strlen(p);
  if (!s_len || !p_len)
    return false;

  vector<vector<bool>> dp(s_len+1, vector<bool>(p_len+1, false));
  dp[0][0] = true;

  for (uint32_t i = 1; i < p_len+1; ++i) {
    if (p[i-1] == '*') {
      dp[0][i] = dp[0][i-2];
    }
  }

  for (uint32_t j = 1; j < p_len+1; ++j) {
    if (p[j-1] == '*') {
      if (p[j-2] != '.') {
        for (uint32_t i = 1; i < s_len+1; ++i) {
          if (dp[i][j-1] || dp[i][j-2])
            dp[i][j] = true;
          else if (dp[i-1][j] && i > 1 && p[j-2] == s[i-2] && s[i-2] == s[i-1]) {
            dp[i][j] = true;
          }
        }
      } else {// p[j-1] == '*' && p[j-2] == '.'
        for (uint32_t i = 1; i < s_len+1; ++i) {
          if (dp[i][j-1] || dp[i][j-2]) {
            dp[i][j] = true;

            while (i <= s_len) {
              dp[i][j] = true;
              ++i;
            }
          }
        }
      }
    } else { // p[j-1] != '*'
      for (uint32_t i = 1; i < s_len+1; ++i) {
        if (p[j-1] == s[i-1] || p[j-1] == '.') {
          dp[i][j] = dp[i-1][j-1];
        }
      }
    }
  }

  return dp[s_len][p_len];
}
*/
bool isMatch_dp(const char* s, const char* p) {
  if (!s || !p)
    return false;

  const uint32_t s_len = strlen(s);
  const uint32_t p_len = strlen(p);
  if (!s_len || !p_len)
    return false;

  function<bool(const char,const char)> match = [](const char a, char b) {
    return (a == b || b == '.');
  };

  dp[s_len+1][p_len+1];
  for (uint32_t i = 0; i < s_len+1; ++i)
    for (uint32_t j = 0; j < p_len+1; ++j)
      dp[i][j] = false;
  dp[0][0] = true;

  for (uint32_t i = 0; i < s_len+1; ++i) {
    for (uint32_t j = 1; j < p_len+1; ++j) {
      if (i > 0) {
        // match exactly one character, index of both string and pattern move forward by 1
        if (dp[i-1][j-1] && match(s[i-1], p[j-1])) {
          dp[i][j] = true;
          continue;
        }
      }
      if (i > 0 && j > 1) {
        if (p[j-1] == '*' && dp[i-1][j] && match(s[i-1], p[j-2])) { // match multiple elements
          dp[i][j] = true;
          continue;
        }
      }
      if (j > 1) {
        if (p[j-1] == '*' && dp[i][j-2]) { // match 0 preceding element, like removing p[j-2]
          dp[i][j] = true;
          continue;
        }
      }
    }
  }

  return dp[s_len][p_len];
}

bool isMatch_recur(const char* s, const char* p) {
  if (!s || !p)
    return false;

  function<bool(const char*,const char*)> match = [](const char* a, const char* b) {
    return (*a == *b || *b == '.');
  };

  function<bool(const char*,const char*)> dfs =
    [&](const char* lhs, const char* rhs) {
    if (*rhs == '\0')
      return (*lhs == '\0');

    if (*(rhs+1) != '*') { // If the next character of p is NOT '*', then it must match the current character of s.
                           // Continue pattern matching with the next character of both s and p.
      return match(lhs, rhs) && dfs(++lhs, ++rhs);
    } else { // If the next character of p is '*', then we do a brute force exhaustive matching of 0, 1,
             // or more repeats of current character of p...until we could not match any more characters.
      while (*lhs && match(lhs, rhs)) {
        if (dfs(lhs, rhs+2)) // rhs+2 gets past rhs+1, where '*' doesn't apply anymore
          return true;

        ++lhs;
      }

      return dfs(lhs, rhs+2);
    }
  };

  return dfs(s, p);
}

int main(int argc, char** argv) {
  cout << "Dynamic Programming..." << endl;
  cout << (isMatch_dp("aa","a") ? "true" : "false") << endl;
  cout << (isMatch_dp("aa","aa") ? "true" : "false") << endl;
  cout << (isMatch_dp("aaa","aa") ? "true" : "false") << endl;
  cout << (isMatch_dp("aa","a*") ? "true" : "false") << endl;
  cout << (isMatch_dp("aa",".*") ? "true" : "false") << endl;
  cout << (isMatch_dp("ab",".*") ? "true" : "false") << endl;
  cout << (isMatch_dp("aab","c*a*b") ? "true" : "false") << endl;
  cout << (isMatch_dp("aab","*a*b") ? "true" : "false") << endl;

  cout << "Recursive..." << endl;
  cout << (isMatch_recur("aa","a") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa","aa") ? "true" : "false") << endl;
  cout << (isMatch_recur("aaa","aa") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa","a*") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa",".*") ? "true" : "false") << endl;
  cout << (isMatch_recur("ab",".*") ? "true" : "false") << endl;
  cout << (isMatch_recur("aab","c*a*b") ? "true" : "false") << endl;
  cout << (isMatch_recur("aab","*a*b") ? "true" : "false") << endl;

  return 0;
}
