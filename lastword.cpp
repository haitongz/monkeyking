/*
Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
return the length of last word in the string. If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,

Given s = "Hello World",
return 5.
 */
#include <iostream>
#include <cstring>

uint32_t lastWordLen(const char* s) {
  uint32_t len = 0, prev = 0;
  for (uint32_t i = 0; s[i] != '\0'; ++i) {
    if (s[i] != ' ') {
      ++len;
      prev = len;
    } else {
      len = 0;
    }
  }

  return !len ? prev : len;
}

int main(int argc, char** argv) {
  string str = "get length of last word";
  cout << "Length of last word: " << lastWordLen(str.c_str()) << endl;
}
