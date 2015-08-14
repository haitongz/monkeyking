#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
 */
bool isInterleaving_recur(const string& s1, const string& s2, const string& s3) {
  const uint32_t len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
  if (len1+len2 != len3)
    return false;

  function<bool(const uint32_t,const uint32_t,const uint32_t)> solve =
    [&](const uint32_t idx1, const uint32_t idx2, const uint32_t idx3) {
    if (idx1 == len1 && idx2 == len2 && idx3 == len3)
      return true;
    else if (idx3 == len3) // If C is empty and any of the two strings is not empty
      return false;

    // If any of the above mentioned two possibilities is true, then return true, otherwise false
    return (s3[idx3] == s1[idx1] && solve(idx1+1, idx2, idx3+1)) ||
           (s3[idx3] == s2[idx2] && solve(idx1, idx2+1, idx3+1));
  };

  return solve(0, 0, 0);
}

bool isInterleaving_dp(const string& s1, const string& s2, const string& s3) {
  const uint32_t len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
  if (len1+len2 != len3)
    return false;

  bool dp[len1+1][len2+1];
  for (auto& i : dp)
    for (auto& j : i)
      j = false;
  dp[0][0] = true;

  for (uint32_t i = 1; i < len2+1; ++i) {
    if (dp[0][i-1] && s2[i-1] == s3[i-1]) // when s1 is empty
      dp[0][i] = true;
    else
      break;
  }

  for (uint32_t i = 1; i < len1+1; ++i) {
    if (dp[i-1][0] && s1[i-1] == s3[i-1]) // when s2 is empty
      dp[i][0] = true;

    for (uint32_t j = 1; j < len2+1; ++j) {
      if (dp[i][j-1] && s2[j-1] == s3[i+j-1])
        dp[i][j] = true;
      else if (dp[i-1][j] && s1[i-1] == s3[i+j-1])
        dp[i][j] = true;
      else
        dp[i][j] = false;
    }
  }

  return dp[len1][len2];
}

/*
Given two strings str1 and str2, write a function that prints all interleavings of the given two strings. You may assume that all characters in both strings are different.
 */
vector<string> interleavings(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 && !len2)
    return {};
  else if (!len1)
    return {s2};
  else if (!len2)
    return {s1};

  vector<string> ret;

  function<void(const uint32_t,const uint32_t,const string&)> solve =
    [&](const uint32_t idx1, const uint32_t idx2, const string& to_ext) {
    if (idx1 == len1) {
      ret.push_back(to_ext+s2.substr(idx2, len2-idx2+1));
      return;
    } else if (idx2 == len2) {
      ret.push_back(to_ext+s1.substr(idx1, len1-idx1+1));
      return;
    } else { // cannot use backtrack here since we want all paths, not retrieving.
      // need to do both possible ways
      solve(idx1+1, idx2, to_ext+s1[idx1]);
      solve(idx1, idx2+1, to_ext+s2[idx2]);
    }
  };

  solve(0, 0, "");
  return ret;
}

int main(int argc, char** argv) {
  string s1 = "aabcc";
  string s2 = "dbbca";

  string s3 = "aadbbcbcac";
  cout << (isInterleaving_recur(s1, s2, s3) ? "true" : "false") << endl;
  cout << (isInterleaving_dp(s1, s2, s3) ? "true" : "false") << endl;
  s3 = "aadbbbaccc";
  cout << (isInterleaving_recur(s1, s2, s3) ? "true" : "false") << endl;
  cout << (isInterleaving_dp(s1, s2, s3) ? "true" : "false") << endl;

  s1 = "AB";
  s2 = "CD";
  vector<string> res = interleavings(s1, s2);
  for (auto& i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
