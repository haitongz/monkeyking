/*
Write an efficient C function to return maximum occurring character in the input string e.g., if input string is 'test string' then function should return 't'.
 */
#include <iostream>

using namespace std;

char maxOccurring(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return '\0';

  uint32_t count[26];
  for (auto& i : count)
    i = 0;
  for (uint32_t i = 0; i < len; ++i) {
    uint8_t idx = s[i]-'a';
    ++count[idx];
  }

  uint32_t max_occurring = 0;
  uint8_t max_idx = 0;
  for (uint32_t i = 0; i < 26; ++i) {
    if (count[i] > max_occurring) {
      max_occurring = count[i];
      max_idx = i;
    }
  }

  return 'a'+max_idx;
}

int main(int argc, char** argv) {
  string s = "test string";
  cout << maxOccurring(s) << endl;
}
