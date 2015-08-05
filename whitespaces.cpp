#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <functional>

using namespace std;

void removeAllSpaces(char* s) {
  if (!s)
    return;
  const uint32_t len = strlen(s);
  if (!len)
    return;

  // To keep track of non-space character count
  uint32_t count = 0;

  for (uint32_t i = 0; s[i]; ++i)
    if (s[i] != ' ')
      s[count++] = s[i]; // here count is incremented

  s[count] = '\0';
}

void replaceSpaces(char** s) {
  if (!s || !*s)
    return;

  const uint32_t len = strlen(*s);
  int32_t index = -1;
  int32_t old_end = len-1;
  int32_t new_end = old_end;

  while (++index < len) { // Compute the end of new string
    if (isspace(*(*s+index))) {
      new_end += 2;
    }
  }

  char* new_s = (char*)malloc(new_end+1);
  new_s[new_end+1] = '\0';
  while (--index >= 0) {
    if (isspace(*(*s+old_end))) { // replace space with "%20"
      new_s[new_end--] = '0';
      new_s[new_end--] = '2';
      new_s[new_end--] = '%';
    } else {
      new_s[new_end--] = *(*s+old_end);
    }

    --old_end;
  }

 // free(*s);
  *s = new_s;
}

/*
Given a string you need to print all possible strings that can be made by placing spaces (zero or one) in between them.
 */
vector<string> newStrings(const string& s) { // O(n*(2^n))
  const uint32_t len = s.length();
  if (!len)
    return {};

  // Buffer to hold the string containing spaces
  char buf[2*len];
  buf[0] = s[0]; // Copy the first character as it is, since it will be always at first position
  vector<string> ret;

  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t idx1, const uint32_t idx2) {
    if (idx1 == len) {
      buf[idx2] = '\0';
      ret.push_back(buf);
      return;
    }

    // Either put the character
    buf[idx2] = s[idx1];
    solve(idx1+1, idx2+1);

    // Or put a space followed by next character
    buf[idx2] = ' ';
    buf[idx2+1] = s[idx1];
    solve(idx1+1, idx2+2);
  };

  solve(1, 1);
  return ret;
}

int main(int argc, char** argv) {
  char* s = "    John    Smith sucks   ";
  replaceSpaces(&s);
  cout << "Consolidated string is: " << s << endl;

  char* s1 = "John    Smith sucks";
  replaceSpaces(&s1);
  cout << "Consolidated string is: " << s1 << endl;

  char* s2 = "John";
  replaceSpaces(&s2);
  cout << "Consolidated string is: " << s2 << endl;

  string s3 = "ABCD";
  vector<string> res = newStrings(s3);
  cout << "New strings:" << endl;
  for (auto& i : res)
    cout << i << endl;

  return 0;
}
