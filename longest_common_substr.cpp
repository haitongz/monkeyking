#include <iostream>
#include <vector>

using namespace std;

/*
Write a function to find the longest common prefix string amongst an array of strings.
 */
string longestCommonPrefixStr(const vector<string>& strs) {
  const uint32_t n = strs.size();
  if (!n)
    return "";

  uint32_t common_len = strs[0].length();

  for (uint32_t i = 1; i < n; ++i) {
    const uint32_t i_len = strs[i].length();
    uint32_t j;
    for (j = 0; j < common_len && j < i_len && strs[i-1][j] == strs[i][j]; ++j);
    common_len = j;
  }

  return strs[0].substr(0, common_len);
}

/*
Given 2 strings, return longest common substring length.
 */
uint32_t longestCommonSubstrLen(const string& s1, const string& s2) {
  const uint32_t len1 = s1.size();
  const uint32_t len2 = s2.size();
  if (!len1 || !len2)
    return 0;

  vector<vector<uint32_t>> dp(len1+1, vector<uint32_t>(len2+1, 0));
  uint32_t ret = 0;

  for (uint32_t i = 1; i < len1+1; ++i) {
    for (uint32_t j = 1; j < len2+1; ++j) {
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
  vector<string> strs = {"abcd","abcde","abcdef"};
  cout << "Longest common prefix string: " << longestCommonPrefixStr(strs) << endl;

  string s1 = "jisnldjife";
  string s2 = "isdklnige";
  cout << "Longest common substring length: " << longestCommonSubstrLen(s1, s2) << endl;

  return 0;
}
