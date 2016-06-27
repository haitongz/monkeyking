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
#include <map>
#include <functional>

using namespace std;

namespace {
  const uint MAX_LMT = numeric_limits<uint>::max();
}

string minWindowSubstr(const string& S, const string& T) {
  const uint sLen = S.length();
  const uint tLen = T.length();
  if (!sLen || !tLen || sLen < tLen) {
    return "";
  }

  if (sLen == tLen) {
    return (S != T) ? "" : S;
  }

  uint tCharcnt[256] = {0};
  uint sCharcnt[256] = {0};

  for (uint i = 0; i < tLen; ++i) {
    ++tCharcnt[T[i]]; // value can go over 1 if there are duplicates
  }

  uint sIdx = 0;
  while (sIdx < sLen && !tCharcnt[S[sIdx]]) {
    ++sIdx; // search first index in S that has a char in T
  }

  if (sIdx == sLen) { // can't find any in S
    return "";
  }

  function<uint(uint,const uint)> unwind =
    [&](uint idx, const uint end) {
    --sCharcnt[S[idx++]];
    for (; idx < end && (!tCharcnt[S[idx]] || tCharcnt[S[idx]] < sCharcnt[S[idx]]); ++idx) {
      if (tCharcnt[S[idx]])
        --sCharcnt[S[idx]];
    }

    return idx;
  };

  uint start = 0, minLen = MAX_LMT;
  uint matchNo = 0;

  for (uint i = sIdx; i < sLen; ++i) { // start from first index in S that has a char in T
    char c = S[i];
    if (tCharcnt[c]) { // this char is in T
      if (++sCharcnt[c] <= tCharcnt[c]) { // there could be multiple of this char in T
        if (++matchNo == tLen) { // range between s_idx and i has all chars in T; need to check its length
          if (minLen > i-sIdx+1) { // save result
            start = sIdx;
            minLen = i-sIdx+1;
          }
          --matchNo;
          sIdx = unwind(sIdx, i);
        }
      } else if (c == S[sIdx]) { // handle repeated
        sIdx = unwind(sIdx, i);
      }
    }
  }

  return (minLen == MAX_LMT) ? "" : S.substr(start, minLen); // when T.length() > S.length()
}

string minWindow2(const string& S, const string& T) {
  const uint sLen = S.length(), tLen = T.length();
  if (!sLen || !tLen) {
    return "";
  }

  uint need[1 << (sizeof(char)* 8)] = {0};
  for (char t : T) {
    ++need[t];
  }

  map<char,uint> mem;
  uint minLeft = 0, minVal = sLen+1, left = 0, size = 0;

  for (uint i = 0; i < sLen; ++i) {
    if (!need[S[i]]) {
      continue;
    }

    if (++mem[S[i]] <= need[S[i]]) {
      ++size;
    }

    if (size == tLen) {
      while (!need[S[left]] || mem[S[left]] > need[S[left]]) {
        if (mem[S[left]] > need[S[left]])
          --mem[S[left]];
        ++left;
      }

      auto len = i-left+1;
      if (len < minVal) {
        minVal = len;
        minLeft = left;
      }
    }
  }

  if (minVal > sLen) {
    return "";
  } else {
    return S.substr(minLeft, minVal);
  }
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
