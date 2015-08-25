/*
Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".
 */
#include <iostream>
#include <set>

using namespace std;

bool wordbreak(const string& s, const set<string>& dict) {
  const uint32_t len = s.length();
  if (len < 2) {
    return dict.count(s) ? true : false;
  }

  bool dp[len+1];
  dp[0] = true;

  for (uint32_t i = 0; i < len; ++i) {
    for (int32_t j = i, k = 1; j > -1; ++k, --j) {
      string j_sub = s.substr(j, k);
      if (dp[j] && dict.count(j_sub)) {
        dp[i+1] = true;
        break;
      }
    }
  }

  return dp[len];
}

int main(int argc, char** argv) {
  set<string> dict;
  dict.insert("leet");
  dict.insert("code");

  cout << "String 'leetcode' can " << (wordbreak("leetcode", dict) ? "" : "not ") << "be segmented!" << endl;

  return 0;
}
