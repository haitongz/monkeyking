/*
Given a string S and a string T, count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
S = "rabbbit", T = "rabbit"
Return 3.
 */
#include <iostream>
#include <vector>

using namespace std;

uint32_t distinctSubseqsNum(const string& S, const string& T) {
  if (S == T)
    return 1;
  const uint32_t s_len = S.length(), t_len = T.length();
  if (s_len <= t_len)
    return 0;

  uint32_t dp[s_len+1][t_len+1];

  for (uint32_t i = 0; i < s_len+1; ++i)
    for (uint32_t j = 0; j < t_len+1; ++j)
      dp[i][j] = j ? 0 : 1; // when T is empty, only one way from S to T: remove all chars.
                            // otherwise initialize to zero

/* Define the computation structure to be dp[i][j] indicating the number of solutions for S[0...i-1] and T[0...j-1]. i/j in dp represents #chars in the substring. It's easier if we include 0 in the structure to accommodate the case when there's no chars(empty string) considered. In order to expand this structure, when updating dp[i][j] we have two options:

dp[i][j] = dp[i-1][j]. No matter what current char of S is we simply don't use it. We will only use chars [0,...i-2] from S no matter how many solutions there are to cover T[0...j-1]
But if current char of S is same to current of T (S[i-1]==T[j-1]) then we have another choice: we can use all the solutions of dp[i-1][j-1] to increment the solution dp[i][j]. Therefore dp[i][j] += dp[i-1][j-1]
 */
  for (uint32_t i = 1; i < s_len+1; ++i) {
    for (uint32_t j = 1; j < t_len+1; ++j) {
      // since it starts from 1, current char is (i-1, j-1)
      dp[i][j] = dp[i-1][j]; // by removing S[i]
      if (S[i-1] == T[j-1])
        dp[i][j] += dp[i-1][j-1];
    }
  }

  return dp[s_len][t_len];
}

uint32_t distinctSubseqsNum2(const string& S, const string& T) {
  if (S == T)
    return 1;
  const uint32_t s_len = S.length(), t_len = T.length();
  if (s_len < t_len)
    return 0;

  vector<uint32_t> dp(t_len+1, 0);
  dp[0] = 1;

  for (uint32_t i = 0; i < s_len; ++i) {
    for (int32_t j = min(i, t_len); j >= 0; --j) {
      if (T[j] == S[i])
        dp[j+1] += dp[j]; // reverse way
    }
  }

  return dp[t_len];
}

int main(int argc, char** argv) {
  string S = "rabbbit";
  string T = "rabbit";
  cout << "Number of distict subsequences is " << distinctSubseqsNum(S, T) << endl;
  cout << "Number of distict subsequences is " << distinctSubseqsNum2(S, T) << endl;
}
