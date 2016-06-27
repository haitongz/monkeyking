#include <iostream>

using namespace std;

/*
Given a string and an offset, rotate string by offset. (rotate from left to right)
Given "abcdefg"

for offset=0, return "abcdefg"
for offset=1, return "gabcdef"
for offset=2, return "fgabcde"
for offset=3, return "efgabcd"
 */
string rotateString(const string& s, const uint offset) {
  const uint len = s.length();
  if (!len || len < offset || !offset)
    return s;

  string first = s.substr(0, len-offset-1);
  string second = s.substr(len-offset, len-1);

  return second+first;
}

/*
Given a string s1 and a string s2, write a snippet to say whether s2 is a rotation of s1 using only one call to strstr routine?
 */
bool areRotations(const string& s1, const string& s2) {
  const uint len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2 || len1 != len2)
    return false;

  string tmp = s1;
  tmp += s1;

  /* Now check if str2 is a substring of temp */
  char* ptr = strstr(tmp.c_str(), str2);
  return ptr ? true : false;
}

int main() {
  const string s = "abcdefg";
  cout << rotateString(s, 0) << endl;
  cout << rotateString(s, 1) << endl;
  cout << rotateString(s, 2) << endl;
  cout << rotateString(s, 3) << endl;

  return 0;
}
