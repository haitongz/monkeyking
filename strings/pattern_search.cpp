/*
Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[])
that prints all occurrences of pat[] in txt[]. You may assume that n > m.
 */
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

/*
The best case occurs when the first character of the pattern is not present in text at all.

txt[]  = "AABCCAADDEE"
pat[] = "FAA"
The number of comparisons in best case is O(n).

The worst case of Naive Pattern Searching occurs in following scenarios.
1) When all characters of the text and pattern are same.
txt[] = "AAAAAAAAAAAAAAAAAA"
pat[] = "AAAAA".

2) Worst case also occurs when only the last character is different.
txt[] = "AAAAAAAAAAAAAAAAAB"
pat[] = "AAAAB"

Number of comparisons in worst case is O(m*(n-m+1)).
 */
vector<uint> naive(const string& txt, const string& patt) {
  const uint N = txt.length(), M = patt.length();
  if (!N || !M || N < M)
    return {};

  vector<uint> ret;

  for (uint i = 0; i < N;) {
    while (txt[i] != patt[0])
      ++i;

    ret.push_back(i); // backtracking

    uint j = 0;
    for (; j < M;) {
      if (txt[i++] != patt[j]) {
        break;
      } else {
        ++j;
      }
    }

    if (j < M)
      ret.pop_back();
  }

  return ret;
}

/*
Consider a situation where all characters of pattern are different.
 */
vector<uint> naive2(const string& txt, const string& patt) {
  const uint M = patt.length(), N = txt.length();
  if (!N || !M || N < M)
    return {};

  vector<uint> ret;
  uint i = 0;

  while (i < N-M+1) {
    uint j = 0;
    for (; j < M; ++j)
      if (txt[i+j] != patt[j])
        break;

    if (j == M) { // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
      ret.push_back(i);
      i += M;
    } else if (!j) {
      i += 1;
    } else {
      i += j; // slide the pattern by j
    }
  }

  return ret;
}

vector<uint> KMP(const string& txt, const string& patt) {
  const uint N = txt.length(), M = patt.length();
  if (!N || !M || N < M)
    return {};

  uint lps[M]; // 'lps' indicates longest proper prefix which is also suffix
  lps[0] = 0; // lps[0] is always 0

  function<void(void)> computeLPS = [&]() {
    uint len = 0;  // length of the previous longest prefix suffix
    uint i = 1;

    while (i < M) {
      if (patt[i] == patt[len]) {
        lps[i++] = ++len; // lps[i] = the longest proper prefix of pat[0..i] which is also a suffix of pat[0..i]
      } else { // (pat[i] != pat[len])
        if (len) {
          len = lps[len-1]; // This is tricky. Consider the example AAACAAAA and i = 7.
                            // Also, note that we do not increment i here
        } else { // (len == 0)
          lps[i++] = 0;
        }
      }
    }
  };

  computeLPS();

  vector<uint> ret;
  uint i = 0, j = 0;
  while (i < N) {
    if (patt[j] == txt[i]) {
      ++j;
      ++i;
    }

    if (j == M) {
      ret.push_back(i-j);
      j = lps[j-1];
    } else if (i < N && patt[j] != txt[i]) { // mismatch after j matches
      if (j) // Do not match lps[0..lps[j-1]] characters, they will match anyway
        j = lps[j-1];
      else
        i = i+1;
    }
  }

  return ret;
}

#define ALPHA_NUM 256

vector<uint> RobinKarp(const string& txt, const string& patt, const uint q) { // q : a prime number
  const uint M = patt.length(), N = txt.length();
  if (!N || !M || N < M)
    return {};

  uint p = 0;  // hash value for pattern
  int t = 0; // hash value for txt
  uint h = 1;

  // The value of h would be "pow(d, M-1)%q"
  for (uint i = 0; i < M-1; ++i)
    h = (h*ALPHA_NUM)%q;

  // Calculate the hash value of pattern and first window of text
  for (uint i = 0; i < M; ++i) {
    p = (ALPHA_NUM*p + patt[i])%q;
    t = (ALPHA_NUM*t + txt[i])%q;
  }

  vector<uint> ret;
  // Slide the pattern over text one by one
  for (uint i = 0; i < N-M+1; ++i) {
    // Check the hash values of current window of text and pattern.
    // If the hash values match then only check for characters on by one
    if (p == t) {
      uint j = 0;
      for (; j < M; ++j) {
        if (txt[i+j] != patt[j])
          break;
      }
      if (j == M) { // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
        ret.push_back(i);
      }
    }

    // Calculate hash value for next window of text: Remove leading digit, add trailing digit
    if (i < N-M) {
      t = (ALPHA_NUM*(t-txt[i]*h)+txt[i+M])%q;
      // We might get negative value of t, converting it to positive
      if (t < 0)
        t = t+q;
    }
  }

  return ret;
}

/*
Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function search(char pat[], char txt[])
that prints all occurrences of pat[] and its permutations (or anagrams) in txt[]. You may assume that n > m.
Expected time complexity is O(n).
 */

/*
We can achieve O(n) time complexity under the assumption that alphabet size is fixed which is typically true
as we have maximum 256 possible characters in ASCII. The idea is to use two count arrays:

1) The first count array store frequencies of characters in pattern.
2) The second count array stores frequencies of characters in current window of text.

Time complexity to compare two count arrays is O(1) as the number of elements in them are fixed
(independent of pattern and text sizes):
1) Store counts of frequencies of pattern in first count array countP[].
Also store counts of frequencies of characters in first window of text in array countTW[].
2) Now run a loop from i = M to N-1. Do following in loop.
..a) If the two count arrays are identical, we found an occurrence.
..b) Increment count of current character of text in countTW[]
..c) Decrement count of first character in previous window in countWT[]
3) The last window is not checked by above loop, so explicitly check it.
 */
vector<uint> searchPermu(const string& txt, const string& patt) {
  const uint M = patt.length(), N = txt.length();
  if (!N || !M || N < M)
    return {};

  char countP[ALPHA_NUM] = {0};
  char countTW[ALPHA_NUM] = {0};

  for (uint i = 0; i < M; ++i) {
    ++(countP[patt[i]]);
    ++(countTW[txt[i]]);
  }

  function<bool(void)> compare = [&]() {
    for (uint i = 0; i < ALPHA_NUM; ++i)
      if (countP[i] != countTW[i])
        return false;

    return true;
  };

  vector<uint> ret;

  for (uint i = M; i < N; ++i) {
    // Compare counts of current window of text with counts of pattern[]
    if (compare())
      ret.push_back(i-M);

    // Add current character to current window
    ++countTW[txt[i]];
    // Remove the first character of previous window
    --countTW[txt[i-M]];
  }

  // Check for the last window in text
  if (compare())
    ret.push_back(N-M);

  return ret;
}

int main(int argc, char** argv) {
  string txt = "AABAACAADAABAAABAA";
  string patt = "AABA";

  vector<uint> res = naive(txt, patt);
  for (auto i : res) {
    cout << txt[i] << " ";
  }
  cout << endl;

  res = KMP(txt, patt);
  for (auto i : res) {
    cout << txt[i] << " ";
  }
  cout << endl;

  res = RobinKarp(txt, patt, 101);
  for (auto i : res) {
    cout << txt[i] << " ";
  }
  cout << endl;

  txt = "ABCEABCDABCEABCD";
  patt = "ABCD";
  res = naive2(txt, patt);
  for (auto i : res) {
    cout << txt[i] << " ";
  }
  cout << endl;

  txt = "BACDGABCDA";
  res = searchPermu(txt, patt);
  for (auto i : res) {
    cout << txt[i] << " ";
  }
  cout << endl;

  return 0;
}
