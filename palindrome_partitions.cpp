#include <iostream>

using namespace std;

bool checkPalindrome(const string& s) { // suppose no spaces
  for (int i = 0, j = s.length()-1; i < j; ++i, --j) { // this covers cases when len = 0 or 1
    if (s[i] != s[j]) {
      return false;
    }
  }

  return true;
}

/*
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
 */
/*
uint minCuts(const string& str) {
  const uint len = str.length();
  if (len <= 1) { // special case for short strings
    return 0;
  }

  uint dp[len+1];
  dp[0] = 0;
  for (uint i = 1; i <= len; ++i)
    dp[i] = len-i; // (len-i) cuts at i, since single characters are palindrome

  bool ispalin_tbl[len][len];
  for (int i = len-1; i >= 0; --i) {
    for (uint j = i; j < len; ++j) {
      if (str[i] == str[j] && (j-i < 2 || ispalin_tbl[i+1][j-1])) {
        ispalin_tbl[i][j] = true;
        dp[i] = min(dp[i], dp[j+1]+1);
      }
    }
  }

  return dp[0]-1;
}
*/
void palinFlagTable(vector<vector<uint8_t>>& t, const string& s) {
  const uint len = s.length(); // length is supposed to have been checked before calling this method
  t.resize(len);
  for (uint i = 0; i < len; ++i)
    t[i] = vector<uint8_t>(len, 1);

  for (uint i = 2; i <= len; ++i) {
    for (uint j = 0, k = i-1; k < len; ++j, ++k) {
      t[j][k] = (t[j+1][k-1] && s[j] == s[k]);
    }
  }
}

uint minCuts(const string& s) {
  const uint len = s.length();
  if (len <= 1)
    return 0;

  vector<vector<uint>> palin;
  palinFlagTable(palin, s);

  vector<int> dp(len+1, MAX_LMT);
  dp[0] = -1;

  for (uint i = 0; i < len; ++i) {
    for (int j = i; j >= 0; --j) {
      if (palin[j][i])
        dp[i+1] = min(dp[i+1], dp[j]+1);
    }
  }

  return (dp.back() == -1) ? 0 : dp.back();
}

/*
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

Given s = "aab",
Return
[
    ["aa","b"],
    ["a","a","b"]
]
 */
typedef vector<vector<string>> ResultT;
ResultT palinPartitions(const string& s) {
  const uint len = s.length();
  if (len <= 1) { // special case for short strings
    return {{s}};
  }

  ResultT dp[len];
  dp[0] = {{s.substr(0,1)}}; //ResultT(1, vector<string>(1, s.substr(0, 1))); // start from first character, which is a palindrome

  for (uint i = 1; i < len; ++i) {
    ResultT& res_ati = dp[i];

    // problem i is the case with the first i chars
    // dp(i) = sum(dp(j) + palidrome(s[j-i]))
    for (int j = i; j >= 0; --j) {
      string j2i = s.substr(j, i-j+1);
      if (checkPalindrome(j2i)) {
        if (!j) { // substr at i is palindrome
          vector<string> tmp(1, j2i);
          res_ati.push_back(tmp);
        } else {
          ResultT& prev_res = dp[j-1];
          for (uint k = 0; k < prev_res.size(); ++k) { // append str_j2i to results of j-1
            vector<string> tmp = prev_res[k]; // copy
            tmp.push_back(j2i);
            res_ati.push_back(tmp);
          }
        }
      }
    }
  }

  return dp[len-1];
}

/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000,
and there exists one unique longest palindromic substring.
 */
/*
uint test2Sides(const string& s, int low, uint high) {
  const uint n = s.length();
  uint res = 0;

  if (low == high) {
    --low;
    ++high;
    res = 1;
  }

  while (low >= 0 && high < n && s[low] == s[high]) {
    res += 2;
    --low;
    ++high;
  }

  return res;
}

string longestPalinSubstr(const string& s) {
  uint start = 0;
  uint max_len = 1;

  for (uint j = 1; j < s.length(); ++j) {
    uint t = test2Sides(s, j, j);
    if (t > max_len) {
      start = j-t/2;
      max_len = t;
    }
    t = test2Sides(s, j-1, j);
    if (t > max_len) {
      start = j-t/2;
      max_len = t;
    }
  }

  return s.substr(start, max_len);
}
*/
string longestPalinSubstr_dp(string& s) { // O(n^2)
  const uint n = s.length();
  uint begin = 0;
  uint max_len = 1;

  bool table[n][n];
  for (auto& i : table)
    for (auto& j : i)
      j = false;
  for (uint i = 0; i < n; ++i)
    table[i][i] = true;

  for (uint i = 0; i < n-1; ++i) {
    if (s[i] == s[i+1]) {
      table[i][i+1] = true;
      begin = i;
      max_len = 2;
    }
  }
  for (uint len = 3; len <= n; ++len) {
    for (uint i = 0; i < n-len+1; ++i) {
      uint j = i+len-1;
      if (s[i] == s[j] && table[i+1][j-1]) {
        table[i][j] = true;
        begin = i;
        max_len = len;
      }
    }
  }

  return s.substr(begin, max_len);
}

string longestPalinSubstr_Manacher(const string& s) { // O(n)
  uint len = s.length();
  if (!len)
    return "";

  len = 2*len+1; // position count
  uint lps[len]; // LPS
  lps[0] = 0;
  lps[1] = 1;

  uint C = 1; // center position
  uint R = 2; // center right position
  uint iMirror; // current left position
  uint maxLPSLen = 0;
  uint maxLPSCenterPos = 0;
  int start = -1;
  int diff = -1;

  for (uint i = 2; i < len; ++i) {
   iMirror = 2*C-i; // get currentLeftPos iMirror for currentRightPosition i
   lps[i] = 0;
   diff = R-i;

   //If currentRightPosition i is within centerRightPosition R
   if (diff > 0)
     lps[i] = min(lps[iMirror], (uint)diff);

   //Attempt to expand palindrome centered at currentRightPosition i. Here for
   //odd positions, we compare characters and if match then increment LPS
   //Length by ONE. If even position, we just increment LPS by ONE without any
   //character comparison.
   while (((i+lps[i]) < len && (i-lps[i]) > 0) &&
          (!((i+lps[i]+1)%2) || (s[(i+lps[i]+1)/2] == s[(i-lps[i]-1)/2]))) {
     ++lps[i];
   }

   if (lps[i] > maxLPSLen) {
     maxLPSLen = lps[i];
     maxLPSCenterPos = i;
   }

   // If palindrome centered at currentRightPosition i, expand beyond centerRightPosition R,
   // adjust centerPosition C based on expanded palindrome.
   if (i+lps[i] > R) {
     C = i;
     R = i+lps[i];
   }
        //Uncomment it to print LPS Length array
        //printf("%d ", L[i]);
  }
    //printf("\n");

  start = (maxLPSCenterPos-maxLPSLen)/2;
  return s.substr(start, maxLPSLen);
//  cout << "LPS of string is " << text << " : ";
//  for (uint i = start; i < start+maxLPSLen; ++i)
  //  cout << text[i];
 // cout << endl;
}

int main(int argc, char** argv) {
  str = "aab";
  vector<vector<string>> res = palinPartitions(str);

  cout << "Palindrome partitions:" << endl;
  for (const auto& i : res) { //uint i = 0; i < res.size(); ++i) {
    for (const auto& j : i) { //uint j = 0; j < res[i].size(); ++j) {
      cout << j << ",";
    }
    cout << endl;
  }

 // cout << "Longest palindrome substring: " << longestPalinSubstr(str) << endl;
  cout << "Longest palindrome substring: " << longestPalinSubstr_dp(str) << endl;
  cout << "Longest palindrome substring: " << longestPalinSubstr_Manacher(str) << endl;

  uint cuts = minCuts(str);
  cout << "Min cuts: " << cuts << endl;

  return 0;
}
