/*
Given a string, recursively remove adjacent duplicate characters from string. The output string should not have any adjacent
duplicates.

O(n):
1) Start from the leftmost character and remove duplicates at left corner if there are any.
2) The first character must be different from its adjacent now. Recur for string of length n-1 (string without first character).
3) Let the string obtained after reducing right substring of length n-1 be rem_str. There are three possible cases
  a) If first character of rem_str matches with the first character of original string, remove the first character from rem_str.
  b) Else if the last removed character in recursive calls is same as the first character of the original string. Ignore 
  the first character of original string and return rem_str.
  c) Else, preppend the first character of the original string at the beginning of rem_str.
4) Return rem_str.
 */
#include <iostream>
#include <functional>
#include <cstring>

using namespace std;

const char* rmAdjDups_recur(char* str) {
  char last_removed = '\0';

  function<char*(char*)> solve = [&](char* s) {
    const uint32_t len = strlen(s);
    if (len < 2)
      return s;

    // Remove leftmost same characters and recur for remaining string
    if (s[0] == s[1]) {
      last_removed = s[0];
      while (s[1] && s[0] == s[1])
        ++s;

      return solve(s+1);
    }

    // At this point, the first character is definitely different from its adjacent. Ignore first character and recursively
    // remove characters from remaining string
    char* rem_str = solve(s+1);

    // Check if the first character of the rem_str matches with the first character of the original string
    if (rem_str[0] && rem_str[0] == s[0]) {
      last_removed = s[0];
      return (rem_str+1); // Remove first character
    }

    // If remaining string becomes empty and last removed character is same as first character of original string.
    // This is needed for a string like "acbbcddc"
    if (rem_str[0] == '\0' && last_removed == s[0])
      return rem_str;

    // If the two first characters of str and rem_str don't match, append first character of str before the first character
    // of rem_str.
    --rem_str;
    rem_str[0] = s[0];
    return rem_str;
  };

  return solve(str);
}

int main(int argc, char** argv) {
  char str1[] = "geeksforgeeg";
  cout << "Before: " << str1 << ", After: " << rmAdjDups_recur(str1) << endl;
  char str2[] = "azxxxzy";
  cout << "Before: " << str2 << ", After: " << rmAdjDups_recur(str2) << endl;
  char str3[] = "caaabbbaac";
  cout << "Before: " << str3 << ", After: " << rmAdjDups_recur(str3) << endl;
  char str4[] = "gghhg";
  cout << "Before: " << str4 << ", After: " << rmAdjDups_recur(str4) << endl;
  char str5[] = "aaaacddddcappp";
  cout << "Before: " << str5 << ", After: " << rmAdjDups_recur(str5) << endl;
  char str6[] = "aaaaaaaaaa";
  cout << "Before: " << str6 << ", After: " << rmAdjDups_recur(str6) << endl;
  char str7[] = "qpaaaaadaaaaadprq";
  cout << "Before: " << str7 << ", After: " << rmAdjDups_recur(str7) << endl;
  char str8[] = "acaaabbbacdddd";
  cout << "Before: " << str8 << ", After: " << rmAdjDups_recur(str8) << endl;
  char str9[] = "acbbcddc";
  cout << "Before: " << str9 << ", After: " << rmAdjDups_recur(str9) << endl;

  return 0;
}
