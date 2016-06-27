/*
Write an efficient C function to return maximum occurring character in the input string

Given input string 'test string' then function should return 't'.
 */
#include <iostream>

using namespace std;

char mostOccurringChar(const string& s) {
  const uint len = s.length();
  if (!len) {
    return '\0';
  }

  uint count[26];
  for (auto& i : count) {
    i = 0;
  }

  for (uint i = 0; i < len; ++i) {
    uint idx = s[i]-'a';
    ++count[idx];
  }

  uint occurringNo = 0;
  uint idx = 0;

  for (uint i = 0; i < 26; ++i) {
    if (count[i] > occurringNo) {
      occurringNo = count[i];
      idx = i;
    }
  }

  return 'a'+idx;
}

int main(int argc, char** argv) {
  string s = "test string";
  cout << mostOccurringChar(s) << endl;

  return 0;
}
