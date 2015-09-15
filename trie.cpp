#include <iostream>
#include <vector>
#include "trie.h"

using namespace std;

int main(int argc, char** argv) {
  vector<string> dict = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
  Trie t;
  for (auto& i : dict)
    t.add(i);

  string key = "the";
  if (t.search(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;

  t.deleteKey(key);
  cout << "Deleted key '" << key << "'..." << endl;
  if (t.search(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;

  key = "these";
  if (t.search(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;
  key = "their";
  if (t.search(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;
  key = "t**ir";
  if (t.wildcardSearch(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;
  key = "thaw";
  if (t.search(key))
    cout << "'" << key << "' found!" << endl;
  else
    cout << "'" << key << "' not found!" << endl;

  return 0;
}
