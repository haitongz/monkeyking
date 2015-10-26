/*
Given two strings str1 and str2, find the shortest string that has both str1 and str2 as subsequences.
 */
#include <iostream>
#include <cstring>
#include <functional>

using namespace std;

#define MAX_CHARS 1000001

int32_t fail[MAX_CHARS];

int32_t shortestSuperseqLen(const char* s1, const uint32_t len1,
                            const char* s2, const uint32_t len2) {
  if (!s1 || !len1)
    return len2;
  if (!s2 || !len2)
    return len1;

  int32_t i, j;

  function<int32_t(const char*,const uint32_t,const char*,const uint32_t)> solve = // KMP
    [&](const char* txt, const uint32_t t_len, const char* pat, const uint32_t p_len) {
    fail[0] = -1;

    for (j = 1; j < p_len; ++j) {
      for (i = fail[j-1]; i >= 0 && pat[i+1] != pat[j]; i = fail[i])
        ;
      fail[j] = (pat[i+1] == pat[j]) ? i+1 : -1;
    }
    for (i = j = 0; i < t_len && j < p_len; ++i) {
      if (txt[i] == pat[j])
        ++j;
      else if (j) {
        j = fail[j-1]+1;
        --i;
      }
    }

    return j == p_len ? (i-p_len) : -1;
  };

  int32_t pos = solve(s1, len1, s2, len2);
  int32_t u = 0;
  if (pos != -1)
    u = len2;
  else if (i == len1 && j > 0 && (s1[len1-1] == s2[j-1]))
    u = j;

  pos = solve(s2, len2, s1, len1);
  int32_t v = 0;
  if (pos != -1)
    v = len1;
  else if (i == len2 && j > 0 && s2[len2-1] == s1[j-1])
    v = j;

  return len1+len2-max(u, v);
}

int main(int argc, char** argv) {
  char str[2][MAX_CHARS];

  while (true) {
    gets(str[0]);
    gets(str[1]);
    const uint32_t len1 = strlen(str[0]);
    const uint32_t len2 = strlen(str[1]);

    cout << shortestSuperseqLen(str[0], len1, str[1], len2) << endl;
  }

  return 0;
}
