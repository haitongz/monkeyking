/*
You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.
For example, given:
S: "barfoothefoobarman"
L: ["foo", "bar"]
You should return the indices: [0,9].
(order does not matter).
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<uint32_t> substrs(const string& S, const vector<string>& L) {
  const uint32_t n = L.size(), s_len = S.length(), wd = L[0].length();
  if (!n || !s_len || !wd || s_len < wd*n)
    return {};

  unordered_map<string,uint32_t> tbl;
  for (auto& str : L)
    ++tbl[str];

  vector<uint32_t> res;
  const uint32_t biggest_idx = s_len-wd*n;

  for (uint32_t i = 0; i <= biggest_idx; ++i) { // biggest possible index
    unordered_map<string,uint32_t> recs;

    for (uint32_t j = 0; j < n; ++j) {
      auto str = S.substr(i+j*wd, wd);
      if (!tbl[str])
        break;
      if (++recs[str] > tbl[str]) // cannot appear more
        break;
      if (j == n-1)
        res.push_back(i);
    }
  }

  return res;
}

int main(int argc, char** argv) {
  string S = "barfoothefoobarman";
  vector<string> L;
  L.push_back("foo");
  L.push_back("bar");

  vector<uint32_t> res = substrs(S, L);
  cout << "[";
  for (auto i : res)
    cout << i << " ";
  cout << "]" << endl;
}
