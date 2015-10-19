/*
Given two words s1 and s2, find the minimum number of steps required to convert s1 to s2 (each operation is counted as 1 step).

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

Assume that the total number of operations is d. Pick letters from both strings: x1 and x2. If x1 = x2,
remove both and pick next letters.

If they are different, compare three operations:
a) insert a character, i.e., remove x2 from s2 since we will insert x2 to s1. Then pick letters from s1 and s2 again.
b) delete a character, i.e., remove x1 from s1.
c) replace a character, i.e., remove both x1 and x2.

All these cases we need one extra operation. So the algorithm is:
s1 = delete the first character of s1
s2 = delete the first character of s2
d(s1, s2) = d(s1, s2), if the first characters are the same.
d(s1, s2) = 1 + min(min(d(s1, s2), d(s1, s2)), d(s1, s2))
 */
#include <iostream>
//#include <vector>
//#include <limits>

using namespace std;

//static const uint32_t max_lmt = numeric_limits<uint32_t>::max();
/*
uint32_t editDistance(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length();
  const uint32_t len2 = s2.length();
  if (!len1 || !len2)
    return abs(int32_t(len2-len1));

  uint32_t dp[len1][len2];

  dp[0][0] = (s1[0] == s2[0]) ? 0 : 1;
  for (uint32_t i = 1; i < len1; ++i) {
    dp[i][0] = (s1[i] == s2[0]) ? i : dp[i-1][0]+1;
  }
  for (uint32_t j = 1; j < len2; ++j) {
    dp[0][j] = (s1[0] == s2[j]) ? j : dp[0][j-1]+1;
  }
  for (uint32_t i = 1; i < len1; ++i) {
    for (uint32_t j = 1; j < len2; ++j) {
      if (s1[i] == s2[j]) {
        dp[i][j] = dp[i-1][j-1];
      } else {
        dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
      }
    }
  }

  return dp[len1-1][len2-1];
}
*/
uint32_t minEditDistance(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length();
  const uint32_t len2 = s2.length();
  if (!len1 || !len2)
    return abs(int32_t(len2-len1));

  uint32_t dp[len1+1][len2+1];

  dp[0][0] = 1;
  for (uint32_t i = 1; i < len1+1; ++i) {
    dp[i][0] = (s1[i] == s2[0]) ? i : dp[i-1][0]+1;
  }
  for (uint32_t j = 1; j < len2+1; ++j) {
    dp[0][j] = (s1[0] == s2[j]) ? j : dp[0][j-1]+1;
  }
  for (uint32_t i = 1; i < len1+1; ++i) {
    for (uint32_t j = 1; j < len2+1; ++j) {
      if (s1[i] == s2[j]) {
        dp[i][j] = dp[i-1][j-1];
      } else {
        dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
      }
    }
  }

  return dp[len1][len2];
}
/*
uint32_t editDistance2(const string& s1, const string& s2) {
  const uint32_t m = s1.length();
  const uint32_t n = s2.length();
  if (!m || !n)
    return abs(int32_t(n-m));

  uint32_t dp[2][n+1];
  uint8_t idx = 0;

  for (uint32_t i = 0; i <= n; ++i)
    dp[!idx][i] = i;

  for (uint32_t i = 0; i < m; ++i) {
    dp[idx][0] = dp[!idx][0]+1;

    for (uint32_t j = 0; j < n; ++j) {
      if (s1[i] == s2[j]) {
        dp[idx][j+1] = dp[!idx][j];
      } else {
        dp[idx][j+1] = min(min(dp[!idx][j+1], dp[idx][j]), dp[!idx][j])+1;
      }
    }
    idx = !idx;
  }

  return dp[!idx][n];
}

uint32_t minEditDistance(const string& word1, const string& word2) {
  const uint32_t len1 = word1.length(), len2 = word2.length();
  vector<vector<uint32_t>> dp(len1+1, vector<uint32_t>(len2+1, max_lmt));

  for (uint32_t i = 0; i < len1+1; ++i)
    dp[i][0] = i;
  for (uint32_t i = 0; i < len2+1; ++i)
    dp[0][i] = i;

  for (uint32_t i = 1; i < len1+1; ++i) {
    for (uint32_t j = 1; j < len2+1; ++j) {
      dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
      dp[i][j] = min(dp[i][j], dp[i-1][j-1]+(word1[i-1] == word2[j-1] ? 0 : 1));
    }
  }

  return dp[len1][len2];
}
*/
int main(int argc, char** argv) {
  string s1 = "abc";
  string s2 = "def";

  //cout << "Need " << editDistance(s1, s2) << " steps to convert!" << endl;
 // cout << "Need " << editDistance2(s1, s2) << " steps to convert!" << endl;
 // cout << "Need " << editDistance3(s1, s2) << " steps to convert!" << endl;
  cout << "Need " << minEditDistance(s1, s2) << " steps to convert!" << endl;
}
