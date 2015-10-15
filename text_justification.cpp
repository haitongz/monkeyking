/*
Given an array of words and a length L, format the text such that each line has exactly L characters and
is fully (left and right) justified. You should pack your words in a greedy approach: pack as many words
as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.
Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide
evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right. For the last
line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
  "This    is    an",
  "example  of text",
  "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.
 */
#include <iostream>
#include <vector>

using namespace std;

vector<string> justify_iter(const string words[], const uint32_t n, const uint32_t L) {
  if (!n || !L)
    return {};

  vector<string> ret;

  for (uint32_t i = 0; i < n;) {
    uint32_t i_len = words[i].length();

    uint32_t j = i+1;
    for (; j < n && i_len+words[j].length() < L; ++j)
      i_len += words[j].length()+1;
      if (j == n) {
        string s(words[i]);
        for (++i; i < j; ++i)
          s += " "+words[i];
        while (s.length() < L)
          s.push_back(' ');

        ret.push_back(s);
        return ret;
      }
      if (j-i == 1) {
        ret.push_back(words[i++]);
        ret.back().append(L-ret.back().length(), ' ');
        continue;
      }

      int32_t a = (L-i_len)/(j-i-1)+1;
      int32_t b = (L-i_len)%(j-i-1);
      string s(words[i]);
      for (++i; i < j; ++i, --b) {
        s.append(a, ' ');
        if (b > 0)
          s.push_back(' ');
        s.append(words[i]);
      }
      ret.push_back(s);
  }

  return ret;
}

vector<string> justify_recur(const string words[], const uint32_t n, const uint32_t L) {
  if (!n || !L)
    return {};

  uint32_t curr_len = 0, word_no = 0, first = 0;
  bool lastline = false;
  vector<string> ret;

  auto solve/*justify*/ = [&]() {
    string s;
    if (lastline || word_no == 1) {
      for (uint32_t i = first; i < first+word_no; ++i) {
        s += words[i];
        if (i < first+word_no-1)
          s += " ";
      }

      s += string(L-s.size(), ' ');
      ret.push_back(s);
      return;
    }

    uint32_t spaces = L-curr_len;
    uint32_t fix = spaces/(word_no-1);
    uint32_t spare = spaces%(word_no-1);

    for (uint32_t i = first; i < first+word_no; ++i) {
      s += words[i];
      if (i < first+word_no-1) {
        s += string(fix, ' ');
        if (spare-- > 0)
          s += " ";
      }
    }

    ret.push_back(s);
  };

  for (uint32_t i = 0; i < n+1; ++i) {
    if (i < n && curr_len+words[i].length() < L-word_no+1) {
      curr_len += words[i].length();
      ++word_no;
    } else {
      if (i == n)
        lastline = true;

      solve();
      word_no = 1;
      if (!lastline)
        curr_len = words[i].length();
      first = i;
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  string words[] = {"This", "is", "an", "example", "of", "text", "justification."};
  vector<string> res = justify_iter(words, 7, 16);
  for (const auto& i : res)
    cout << "'" << i << "'" << endl;

  res = justify_recur(words, 7, 16);
  for (const auto& i : res)
    cout << "'" << i << "'" << endl;

  return 0;
}
