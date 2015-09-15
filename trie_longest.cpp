/*
Given a string and a dictionary, find longest string in dictionary that's composed of all chars in the string.

For example, dictionary has "abcde, abc, abbbc, abbbccca, abbbcccabbcx" and string is string = "abc",
return "abbbccca"

Another: given Set set, List chars, return Set which has longest be covered by the List
e.g. dgg cat naioe lot.
1st case: dcnlggatio -> return [dgg,cat,lot]
2st case: dcnlggatioe -> return [naioe]
 */
#include <iostream>
#include <functional>
#include <vector>
#include "trie.h"

using namespace std;

string longestWithAllChars(const string& s, Trie& t) {
  const uint32_t len = s.length();
  if (!len)
    return "";

  bool lookup[256] = {false};
  for (auto c : s)
    lookup[c] = true;

  string ret;

  function<void(Trie::Node*,const string&)> solve = // DFS
    [&](Trie::Node* nd, const string& curr) {
    if (!nd)
      return;

    if (nd->end()) {
      if (curr.length() > ret.length())
        ret = curr;
    }

    for (uint8_t i = 0; i < 26; ++i) {
      if (!nd->children[i] || !lookup[nd->children[i]->value])
        continue;

      string new_str = curr+nd->children[i]->value;
      solve(nd->children[i], new_str);
    }
  };

  solve(t.root, "");
  return ret;
}

int main(int argc, char** argv) {
  vector<string> dict = {"abcde", "abc", "abbbc", "abbbccca", "abbbcccabbcx"};
  string s = "abc";
  Trie t;
  for (auto& i : dict)
    t.add(i);

  cout << longestWithAllChars(s, t) << endl;

  return 0;
}
