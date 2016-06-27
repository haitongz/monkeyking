#include <iostream>

using namespace std;

/*
Write a function to find the longest common prefix string amongst an array of strings.
 */
string longestCommonPrefixStr(const string strs[], const uint n) {
  if (!n) {
    return "";
  }

  uint commonLen = strs[0].length();

  for (uint i = 1; i < n; ++i) {
    const uint iLen = strs[i].length();
    uint j = 0;
    for (; j < commonLen && strs[i-1][j] == strs[i][j] && j < iLen; ++j);

    commonLen = j;
  }

  return strs[0].substr(0, commonLen);
}

/*
Given 2 strings, return longest common substring length.
 */
uint longestCommonSubstrLen(const string& s1, const string& s2) {
  const uint len1 = s1.size();
  const uint len2 = s2.size();
  if (!len1 || !len2) {
    return 0;
  }

  uint dp[len1+1][len2+1];
  for (uint i = 0; i < len1+1; ++i) {
    for (uint j = 0; j < len2+1; ++j) {
      dp[i][j] = 0;
    }
  }

  uint ret = 0;

  for (uint i = 1; i < len1+1; ++i) {
    for (uint j = 1; j < len2+1; ++j) {
      if (s1[i-1] == s2[j-1]) { // grow in both strings
        dp[i][j] = dp[i-1][j-1]+1;
        ret = max(ret, dp[i][j]);
      } else {
        dp[i][j] = 0; // start over as there can't be any gaps in common substrings
      }
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  string strs[3] = {"abcd","abcde","abcdef"};
  cout << "Longest common prefix string: " << longestCommonPrefixStr(strs, 3) << endl;

  string s1 = "jisnldjife";
  string s2 = "isdklnige";
  cout << "Longest common substring length: " << longestCommonSubstrLen(s1, s2) << endl;

  return 0;
}
