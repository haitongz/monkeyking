/*
Compare two strings A and B, determine whether A contains all of the characters in B.
The characters in string A and B are all Upper Case letters.
 */
#include <iostream>
#include <map>

using namespace std;

bool compare(const string& A, const string& B) {
  map<char,int> m;
  for (const auto c : A) {
    ++m[c];
  }
  for (const auto c : B) {
    if (!m.count(c)) {
      return false;
    }
    --m[c];
  }
  for (const auto i : m) {
    if (i.second < 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {
  string A = "ABCD";
  string B = "ACD";
  cout << (compare(A, B) ? "True" : "False") << endl;

  B = "AABC";
  cout << (compare(A, B) ? "True" : "False") << endl;

  return 0;
}
