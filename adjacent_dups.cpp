#include <iostream>
#include <functional>
#include <cstring>

using namespace std;

/*
Given a string, recursively remove adjacent duplicate characters from string. The output string should not have any
adjacent duplicates.

O(n):
1) Start from the leftmost character and remove duplicates at left corner if there are any.
2) The first character must be different from its adjacent now. Recur for string of length n-1 (string without first character).
3) Let the string obtained after reducing right substring of length n-1 be rem_str. There are three possible cases
  a) If first character of rem_str matches with the first character of original string, remove the first character from rem_str.
  b) Else if the last removed character in recursive calls is same as the first character of the original string. Ignore the
     first character of original string and return rem_str.
  c) Else, preppend the first character of the original string at the beginning of rem_str.
4) Return rem_str.
 */
const char* removeAdjDups_recur(char* str) {
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

    // At this point, the first character is definitely different from its adjacent. Ignore first character and recursively remove characters from remaining string
    char* rem_str = solve(s+1);

    // Check if the first character of the rem_string matches with the first character of the original string
    if (rem_str[0] && rem_str[0] == s[0]) {
      last_removed = s[0];
      return (rem_str+1); // Remove first character
    }

    // If remaining string becomes empty and last removed character is same as first character of original string.  This is needed for a string like "acbbcddc"
    if (rem_str[0] == '\0' && last_removed == s[0])
      return rem_str;

    // If the two first characters of str and rem_str don't match, append first character of str before the first character of rem_str.
    --rem_str;
    rem_str[0] = s[0];
    return rem_str;
  };

  return solve(str);
}

/*
Given a string and a positive integer d. Some characters may be repeated in the given string. Rearrange characters of the
given string such that the same characters become d distance away from each other. Note that there can be many possible
rearrangements, the output should be one of the possible rearrangements. If no such arrangement is possible, that should
also be reported.
Expected time complexity is O(n) where n is length of input string.
 */
string rearrange(string& s, const uint32_t d) {
  const uint32_t len = s.length();
  if (!len || len <= d)
    return "";

  // Create an array to store all characters and their frequencies in str[]
  charFreq freq[MAX] = {{0, 0}};
  uint32_t m = 0; // To store count of distinct characters in str[]

  // Traverse the input string and store frequencies of all characters in freq[] array.
  for (uint32_t i = 0; i < n; ++i) {
    char x = str[i];

    // If this character has occurred first time, increment m
    if (freq[x].c == 0)
      freq[x].c = x, m++;

    (freq[x].f)++;
    str[i] = '\0';  // This change is used later
  }

  // Build a max heap of all characters
  buildHeap(freq, MAX);

  // Now one by one extract all distinct characters from max heap and put them back in str[] with the d distance constraint
  for (uint32_t i = 0; i < m; ++i) {
    charFreq x = extractMax(freq, MAX-i);

    // Find the first available position in str[]
    int p = i;
    while (str[p] != '\0')
      ++p;

    // Fill x.c at p, p+d, p+2d, .. p+(f-1)d
    for (uint32_t k = 0; k < x.f; ++k) {
      // If the index goes beyond size, then string cannot be rearranged.
      if (p+d*k >= n) {
        cout << "Cannot be rearranged";
        exit(0);
      }
      str[p+d*k] = x.c;
    }
  }
}

int main(int argc, char** argv) {
  char str1[] = "geeksforgeeg";
  cout << removeAdjDups_recur(str1) << endl;
  char str2[] = "azxxxzy";
  cout << removeAdjDups_recur(str2) << endl;
  char str3[] = "caaabbbaac";
  cout << removeAdjDups_recur(str3) << endl;
  char str4[] = "gghhg";
  cout << removeAdjDups_recur(str4) << endl;
  char str5[] = "aaaacddddcappp";
  cout << removeAdjDups_recur(str5) << endl;
  char str6[] = "aaaaaaaaaa";
  cout << removeAdjDups_recur(str6) << endl;
  char str7[] = "qpaaaaadaaaaadprq";
  cout << removeAdjDups_recur(str7) << endl;
  char str8[] = "acaaabbbacdddd";
  cout << removeAdjDups_recur(str8) << endl;
  char str9[] = "acbbcddc";
  cout << removeAdjDups_recur(str9) << endl;

  return 0;
}
