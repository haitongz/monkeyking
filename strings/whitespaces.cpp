#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <functional>

using namespace std;

void removeAllSpaces(char* s) {
  if (!s) {
    return;
  }

  const uint len = strlen(s);
  if (!len) {
    return;
  }

  // To keep track of non-space character count
  uint count = 0;

  for (uint32_t i = 0; s[i]; ++i) {
    if (s[i] != ' ') {
      s[count++] = s[i]; // here count is incremented
    }
  }

  s[count] = '\0';
}

void replaceSpaces(char** s) {
  if (!s || !*s) {
    return;
  }

  const uint len = strlen(*s);
  int idx = -1;
  int oldEnd = len-1;
  int newEnd = oldEnd;

  while (++idx < len) { // Compute the end of new string
    if (isspace(*(*s+idx))) {
      newEnd += 2;
    }
  }

  char* newS = (char*)malloc(newEnd+1);
  newS[newEnd+1] = '\0';
  while (--idx >= 0) {
    if (isspace(*(*s+oldEnd))) { // replace space with "%20"
      newS[newEnd--] = '0';
      newS[newEnd--] = '2';
      newS[newEnd--] = '%';
    } else {
      newS[newEnd--] = *(*s+oldEnd);
    }

    --oldEnd;
  }

 // free(*s);
  *s = newS;
}

/*
Given a string you need to print all possible strings that can be made by placing spaces (zero or one) in between them.
 */
vector<string> newStrings(const string& s) { // O(n*(2^n))
  const uint len = s.length();
  if (!len)
    return {};

  // Buffer to hold the string containing spaces
  char buf[2*len];
  buf[0] = s[0]; // Copy the first character as it is, since it will be always at first position
  vector<string> ret;

  function<void(const uint,const uint)> solve =
    [&](const uint sIdx, const uint newIdx) {
    if (sIdx == len) {
      buf[newIdx] = '\0';
      ret.push_back(buf);
      return;
    }

    // Either put the character
    buf[newIdx] = s[sIdx];
    solve(sIdx+1, newIdx+1);

    // Or put a space followed by next character
    buf[newIdx] = ' ';
    buf[newIdx+1] = s[sIdx];
    solve(sIdx+1, newIdx+2);
  };

  solve(1, 1);
  return ret;
}

int main(int argc, char** argv) {
  string s = "    John    Smith sucks   ";
  char* c = const_cast<char*>(s.c_str());
  replaceSpaces(&c);
  cout << "Replaced white spaces with %20: " << c << endl;

  s = "  John    Smith sucks";
  c = const_cast<char*>(s.c_str());
  removeAllSpaces(c);
  cout << "Removed all white spaces: " << c << endl;

  s = "ABCD";
  vector<string> res = newStrings(s);
  cout << "New strings:" << endl;
  for (auto& i : res)
    cout << i << endl;

  return 0;
}
