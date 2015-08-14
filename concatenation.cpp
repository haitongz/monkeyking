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
#include <map>

using namespace std;

vector<uint32_t> substrs(const string& S, const vector<string>& L) {
  const uint32_t n = L.size(), s_len = S.length(), wd = L[0].length();
  if (!n || !s_len || !wd || s_len < wd*n)
    return {};

  map<string,uint32_t> tbl;
  for (const auto& s : L)
    ++tbl[s];

  const uint32_t biggest_idx = s_len-wd*n;
  vector<uint32_t> ret;

  for (uint32_t i = 0; i < biggest_idx+1; ++i) { // biggest possible index
    map<string,uint32_t> recs;

    for (uint32_t j = 0; j < n; ++j) {
      auto s = S.substr(i+j*wd, wd);
      if (!tbl[s])
        break;
      if (++recs[s] > tbl[s]) // cannot appear more
        break;
      if (j == n-1)
        ret.push_back(i);
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  string S = "barfoothefoobarman";
  vector<string> L;
  L.push_back("foo");
  L.push_back("bar");

  vector<uint32_t> res = substrs(S, L);
  for (auto i : res)
    cout << i << " ";
  cout << endl;
}
