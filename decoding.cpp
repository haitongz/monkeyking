/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:
'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12). The number of ways decoding "12" is 2.
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

uint32_t decodeWays(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return 0;

  function<bool(const char)> isValid = [](const char c) {
    return (c < '7' && c > '0');
  };

  if (!isValid(s[0]))
    return 0;

  uint32_t pre_pre = 1, prev = 1, curr = 1;

  for (uint32_t i = 1; i < len; ++i) {
    char c = s[i];
    if (!isValid(c)) { // need to ask how to handle '0'
      return 0;
    }

    char p = s[i-1];
    curr = prev;
    if (p < '3' && c < '7')  // s[i] can combine with s[i-1], it's a new way of decoding
      curr += pre_pre;

    pre_pre = prev;
    prev = curr;
  }

  return curr;
}

int main() {
  cout << decodeWays("12") << endl;
  cout << decodeWays("123") << endl;
  cout << decodeWays("1225") << endl;
  return 0;
}
