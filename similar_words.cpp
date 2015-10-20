/*
Given a word list, and a target word. Find all words in list that have edit distance no bigger than k.

Say dictionary has ["cs", "ct", "cby"], target word is "cat" and k=1
          c a t
      [ 0 1 2 3 ] <- prev_dist
-> c  [ 1 0 1 2 ] <- cur_dist
   cb [ 2 1 1 2 ]
   cs [ 2 1 1 2 ]
   ct [ 2 1 1 1 ]

Last value in each row is the edit distance to target word. if it's no bigger than k add this word to result.

Note: when cb is scanned, edit distance is already 2 and has same length as 'cat'.
This means all subtrees of this node can't have smaller edit distances, we can return immediately without checking "cby".
Trie approach can save lots of time when dictionary is huge.
 */
#include <iostream>
#include <vector>
#include <functional>
#include "../trie/trie.h"

using namespace std;

vector<string> similarWords(const string& s, const uint32_t threshold, Trie& t) {
  const uint32_t len = s.length();
  if (!len || !threshold)
    return {};

  vector<string> res;
  string to_ext = "";

  function<void(Trie::Node*,vector<uint32_t>&)> backtrack =
    [&](Trie::Node* nd, vector<uint32_t>& prev_dist) {
    if (nd->end() && prev_dist.back() <= threshold)
      res.push_back(to_ext);

    for (uint8_t i = 0; i < 26; ++i) {
      if (!nd->children[i])
        continue;

      vector<uint32_t> curr_dist = prev_dist;
      ++curr_dist[0];

      char letter = 'a'+i;
      bool go = curr_dist[0] <= threshold;

      for (uint32_t j = 1; j <= len; ++j) {
        uint32_t ins_cost = curr_dist[j-1]+1;
        uint32_t del_cost = prev_dist[j]+1;
        uint32_t rep_cost = 0;

        if (s[j-1] != letter)
          rep_cost = prev_dist[j-1]+1;
        else
          rep_cost = prev_dist[j-1];

        curr_dist[j] = min(min(ins_cost, del_cost), rep_cost);
        if (curr_dist[j] <= threshold)
          go = true;
      }

      if (go) {
        to_ext.push_back(letter);
        backtrack(nd->children[i], curr_dist);
        to_ext.pop_back();
      }
    }
  };

  vector<uint32_t> dist(s.size()+1);
//     iota(dist.begin(), dist.end(), 0); // TODO: what is this line?
  backtrack(t.root, dist);
  return res;
}

int main(int argc, char** argv) {
  const vector<string> dict = {"cs", "ct", "cby"};
  Trie t;
  for (auto& i : dict)
    t.add(i);

  vector<string> res = similarWords("cat", 1, t);
  cout << "All similar words:" << endl;
  for (auto& i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
