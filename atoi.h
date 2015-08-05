#ifndef _ATOI_H_
#define _ATOI_H_

#include <limits>

using namespace std;

int atoi(const char* str) {
  char c = *str;
  bool sign_set = false;
  int64_t res = 0;
  int sign = 1;

  // skip the leading spaces
  while (c == ' ') {
    ++str;
    c = *str;
  }

  while (*str) {
    c = *str;

    // only the first occurence of sign, before any digits, is legal
    if (c == '+' || c == '-') {
      if (!sign_set) {
        sign = (c == '+') ? 1 : -1;
        sign_set = true;
      } else {
        return sign*res;
      }
    } else if (c-'0' >= 0 && c-'9' <= 0) {
      sign_set = true;
      res *= 10;
      res += (c-'0');
      // detect overflow by "cheating" using long long
      if ((res*sign > numeric_limits<int>::max()) || (res*sign < numeric_limits<int>::min()))
        return (sign == 1) ? numeric_limits<int>::max() : numeric_limits<int>::min();
    } else { // return if encounter "other" characters
      return sign*res;
    }
    ++str;
  }

  return sign*res;
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
