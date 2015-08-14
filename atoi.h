#ifndef _ATOI_H_
#define _ATOI_H_

#include <limits>
#include <ctype.h>

using namespace std;

static const int32_t MAX_LMT = numeric_limits<int32_t>::max();
static const int32_t MIN_LMT = numeric_limits<int32_t>::min();

int64_t atoi(const char* s) {
  // skip the leading spaces
  while (*s == ' ') {
    ++s;
  }

  int8_t sign = 1;
  if (*s == '+') {
    ++s;
  else if (*s == '-') {
    sign = -1;
    ++s;
  }

  int64_t ret = 0;

  while (*s) {
    char c = *s;

    // only the first occurence of sign, before any digits, is legal
    if (!isdigit(c)) {
      return sign*ret;
    } else if (c-'0' >= 0 && c-'9' <= 0) {
      ret *= 10;
      ret += (c-'0');
      // detect overflow by "cheating" using long long
      if (ret*sign > MAX_LMT || ret*sign < MIN_LMT)
        return (sign == 1) ? MAX_LMT : MIN_LMT;
    }

    ++s;
  }

  ret *= sign;
  return ret;
}
/*
int atoi(const char* str) {
  int64_t res = 0;

  while (isspace(*str))
    ++str;

  int sign = 1;
  if (*str == '-') {
    sign = -1;
    ++str;
  } else if (*str == '+')
    ++str;

  for ( ; isdigit(*str); ++str) {
    res = res*10 + (*str-'0');
    if (sign == 1 && res >= numeric_limits<int>::max())
      return res >= numeric_limits<int>::max();
    else if (res*sign < numeric_limits<int>::min())
      return numeric_limits<int>::min();
  }

  return res*sign;
}
*/
#endif // _ATOI_H_
