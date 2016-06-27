/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".
 */
#include <iostream>
#include <algorithm>

using namespace std;

/*
void reverse(char* begin, char* end) {
  char aux = '\0';
  while (end > begin)
    aux = *end, *end-- = *begin, *begin++ = aux;
}

void ReverseWords(char* s) {
  char* p1 = s, *p2 = s;
  uint32_t spaceNo = 0;
  State state = OUT;

  for (; *p1; ++p1) {
    if (isspace(*p1)) {
      if (state == IN)
        state = OUT;
      ++spaceNo;
    } else {
      if (state == OUT) {
        state = IN;
        Reverse(p2, p1-spaceNo-1);
        p2 = p1;
        spaceNo = 0;
      }
    }
  }

  Reverse(p2, p1-spaceNo-1); // reverse last word in sentence, also takes care of when there's just one word
}

void ReverseWordOrder(char* s) {
  if (!*s)
    return;

  const uint32_t length = strlen(s);
  Reverse(s, s+length-1);
  ReverseWords(s);
}
*/
string reverseWords(const string& s) {
  const uint len = s.length();
  if (!len)
    return "";

  string ret;

  for (int i = len-1; i >= 0;) {
    while (i >= 0 && s[i] == ' ')
      --i;
    if (i < 0)
      break;
    if (!ret.empty())
      ret.push_back(' ');

    string tmp;
    while (i >= 0 && s[i] != ' ')
      tmp.push_back(s[i--]);

    reverse(tmp.begin(), tmp.end());
    ret.append(tmp);
  }

  return ret;
}

int main(int argc, char** argv) {
  string str = "the sky is blue";
  cout << reverseWords(str) << endl;
  str = "   ";
  cout << reverseWords(str) << endl;
  str = "@ @";
  cout << reverseWords(str) << endl;

  return 0;
}
