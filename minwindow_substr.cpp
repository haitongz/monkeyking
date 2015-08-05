/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the emtpy string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
 */
#include <iostream>
#include <limits>
#include <unordered_map>
#include <functional>

using namespace std;

static const uint32_t MAX_LIMIT = numeric_limits<uint32_t>::max();

string minWindowSubstr(const string& S, const string& T) {
  const uint32_t s_len = S.length();
  const uint32_t t_len = T.length();
  if (!s_len || !t_len || s_len < t_len)
    return "";
  if (s_len == t_len)
    return (S != T) ? "" : S;

  uint32_t t_charcnt[256] = {0};
  uint32_t s_charcnt[256] = {0};

  for (uint32_t i = 0; i < t_len; ++i)
    ++t_charcnt[T[i]]; // value can go over 1 if there are duplicates

  uint32_t s_idx = 0;
  while (s_idx < s_len && !t_charcnt[S[s_idx]])
    ++s_idx; // search first index in S that has a char in T
  if (s_idx == s_len) // can't find any in S
    return "";

  function<uint32_t(uint32_t,const uint32_t)> unwind =
    [&](uint32_t idx, const uint32_t end) {
    --s_charcnt[S[idx++]];
    for (; idx < end && (!t_charcnt[S[idx]] || t_charcnt[S[idx]] < s_charcnt[S[idx]]); ++idx) {
      if (t_charcnt[S[idx]])
        --s_charcnt[S[idx]];
    }

    return idx;
  };

  uint32_t start = 0, min_len = MAX_LIMIT;
  uint32_t match_num = 0;

  for (uint32_t i = s_idx; i < s_len; ++i) { // start from first index in S that has a char in T
    char c = S[i];
    if (t_charcnt[c]) { // this char is in T
      if (++s_charcnt[c] <= t_charcnt[c]) { // there could be multiple of this char in T
        if (++match_num == t_len) { // range between s_idx and i has all chars in T; need to check its length
          if (min_len > i-s_idx+1) { // save result
            start = s_idx;
            min_len = i-s_idx+1;
          }
          --match_num;
          s_idx = unwind(s_idx, i);
        }
      } else if (c == S[s_idx]) { // handle repeated
        s_idx = unwind(s_idx, i);
      }
    }
  }

  return (min_len == MAX_LIMIT) ? "" : S.substr(start, min_len); // when T.length() > S.length()
}

string minWindow2(const string& S, const string& T) {
  const uint32_t s_len = S.length(), t_len = T.length();
  if (!s_len || !t_len)
    return "";

  uint32_t need[1 << (sizeof(char)* 8)] = {0};
  for (char t : T)
    ++need[t];

  unordered_map<char,uint32_t> recs;
  uint32_t min_left = 0, min_val = s_len+1, left = 0, rec_size = 0;

  for (uint32_t i = 0; i < s_len; ++i) {
    if (!need[S[i]])
      continue;

    if (++recs[S[i]] <= need[S[i]])
      ++rec_size;

    if (rec_size == t_len) {
      while (!need[S[left]] || recs[S[left]] > need[S[left]]) {
        if (recs[S[left]] > need[S[left]])
          --recs[S[left]];
        ++left;
      }

      auto len = i-left+1;
      if (len < min_val) {
        min_val = len;
        min_left = left;
      }
    }
  }

  if (min_val > s_len)
    return "";
  else
    return S.substr(min_left, min_val);
}

int main(int argc, char** argv) {
  string S = "ADOBECODEBANC";
  string T = "ABC";
  cout << minWindowSubstr(S, T) << endl;
  T = "XYZ";
  cout << minWindowSubstr(S, T) << endl;

  cout << minWindow2(S, T) << endl;
  return 0;
}
