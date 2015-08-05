/*
Implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ... false
isMatch("aa","aa") ... true
isMatch("aaa","aa") ... false
isMatch("aa", "*") ... true
isMatch("aa", "a*") ... true
isMatch("ab", "?*") ... true
isMatch("aab", "c*a*b") ... false
 */
#include <iostream>
#include <cstring>

using namespace std;
/*
bool isMatch(const char* s, const char* p) {
  const uint32_t len1 = strlen(s);
  const uint32_t len2 = strlen(p);
  if (!len1 || !len2)
    return false;

  bool star = false;
  const char* ptr;

  for (const char* str = s, ptr = p; *str != '\0'; ++str, ++ptr) {
    switch (*ptr) {
      case '?':
        break;
      case '*': {
        star = true;
        s = str, p = ptr;

        while (*p == '*')
          ++p;
        if (*p == '\0')
          return true;

        str = s-1;
        ptr = p-1;
        break;
      }
      default: {
        if (*str != *ptr) {
          if (!star)
            return false;
          ++s;
          str = s-1;
          ptr = p-1;
        }
      }
    }
  }

  while (*ptr== '*')
    ++ptr;

  return (*ptr == '\0');
}

bool isMatch(const char* s, const char* p) {
  auto star = false;
  auto pre_s = s; //, pre_p = p;

  while (*s) {
    if (*s == *p || *p == '?') {
      ++s;
      ++p;
    } else {
      if (*p == '*') {
        while (*p == '*')
          ++p;
        if (*p == '\0')
          return true;

        star = true;
        pre_s = s;
//        pre_p = p;
      } else if (star) {
        s = ++pre_s;
    //    p = pre_p;
      } else {
        return false;
      }
    }
  }

  while (*p == '*')
    ++p;

  return *p == '\0';
}
*/
bool isMatch(const char* s, const char* p) {
  const char* star = nullptr;
  const char* ss = s;

  while (*s) {
    if (*p == '?' || *p == *s) {
      ++s;
      ++p;
      continue;
    }
    if (*p == '*') {
      star = p++;
      ss = s;
      continue;
    }
    if (star) {
      p = star+1;
      s = ++ss;
      continue;
    }

    return false;
  }

  while (*p == '*')
    ++p;

  return !*p;
}

/*
bool isMatch(const char* s, const char* p) {
  const uint32_t s_len = strlen(s), p_len = strlen(p);
  if (!s_len || !p_len)
    return false;

  if (s_len > 300 && p[0] =='*' && p[p_len-1] == '*')
    return false;

  bool check[s_len+1][p_len+1];
  check[0][0] = true;

  for (uint32_t i = 1; i <= p_len; ++i) {
    if (p[i-1] == '*')
      check[0][i] = true;
    else
      break;
  }

  for (uint32_t i = 1; i < s_len+1; ++i) {
    for (uint32_t j = 1; j < p_len+1; ++j) {
      if (p[j-1] == '*') {
        if (check[i-1][j] || check[i][j-1])
          check[i][j] = true;
        else
          check[i][j] = false;
      } else if (check[i-1][j-1]) {
        check[i][j] = (s[i-1] == p[j-1] || s[i-1] == '?' || p[j-1] == '?') ? true : false;
      } else
        check[i][j] = false;
    }
  }

  return check[s_len][p_len];
}

bool isMatch_recur(const char* s, const char* p) {
  if (!s || !p)
    return false;

  if (*p == '\0')
    return *s == '\0';

  if (*(p+1) == '*') {
    while (*s && (*s == *p || *p == '.')) {
      if (isMatch_recur(s, p+2))
        return true;
      ++s;
    }

    return isMatch_recur(s, p+2);
  } else {
    return (*s == *p || (*s && *p == '.')) && (isMatch_recur(++s, ++p));
  }
}
*/
int main(int argc, char** argv) {
  cout << (isMatch("aa", "a") ? "true" : "false") << endl;
  cout << (isMatch("aa", "aa") ? "true" : "false") << endl;
  cout << (isMatch("aaa", "aa") ? "true" : "false") << endl;
  cout << (isMatch("aa", "*") ? "true" : "false") << endl;
  cout << (isMatch("aa", "a*") ? "true" : "false") << endl;
  cout << (isMatch("ab", "?*") ? "true" : "false") << endl;
  cout << (isMatch("aab", "c*a*b") ? "true" : "false") << endl;
  cout << (isMatch("aab", "*ca*b") ? "true" : "false") << endl;
/*
  cout << (isMatch_recur("aa", "a") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa", "aa") ? "true" : "false") << endl;
  cout << (isMatch_recur("aaa", "aa") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa", "*") ? "true" : "false") << endl;
  cout << (isMatch_recur("aa", "a*") ? "true" : "false") << endl;
  cout << (isMatch_recur("ab", "?*") ? "true" : "false") << endl;
  cout << (isMatch_recur("aab", "c*a*b") ? "true" : "false") << endl;
*/
  return 0;
}
