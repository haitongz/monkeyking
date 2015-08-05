/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":
    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
 */
#include <iostream>
#include <functional>

using namespace std;

bool isScrambled(const string& str1, const string& str2) {
  function<bool(const string&,const string&)> solve =
    [&](const string& s1, const string& s2) {
    if (s1 == s2)
      return true;

    const uint32_t len1 = s1.length();
    const uint32_t len2 = s2.length();
    if (len1 != len2)
      return false;
    if (len1 < 4)
      return true;

    int32_t cntr[26] = {0};

    for (uint32_t i = 0; i < len1; ++i)
      ++cntr[s1[i]-'a'];
    for (uint32_t i = 0; i < len2; ++i)
      --cntr[s2[i]-'a'];
    for (uint8_t i = 0; i < 26; ++i)
      if (cntr[i] != 0)
        return false;

    for (uint32_t i = 1; i < len1; ++i) {
      if ((solve(s1.substr(0, i), s2.substr(0, i)) && solve(s1.substr(i), s2.substr(i))) ||
          (solve(s1.substr(0, i), s2.substr(len2-i)) && solve(s1.substr(i), s2.substr(0, len2-i))))
        return true;
    }

    return false;
  };

  return solve(str1, str2);
}

int main(int argc, char** argv) {
  string s1 = "rgtae";
  string s2 = "great";

  cout << "'" << s1 << "' is" << (isScrambled(s1, s2) ? " " : " not ") << "scrambled string of '" << s2 << "'" << endl;
}
