/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.
You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters. Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right. For the last line of text, it should be left justified and no extra space is inserted between words.

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

vector<string> justify(const vector<string>& words, const uint32_t L) {
  const uint32_t n = words.size();
  if (!n || !L)
    return {};

  vector<string> res;

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
        res.push_back(s);
        return res;
      }
      if (j-i == 1) {
        res.push_back(words[i++]);
        res.back().append(L-res.back().length(), ' ');
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
      res.push_back(s);
  }

  return res;
}

vector<string> fullJustify(const vector<string>& words, const uint32_t L) {
  const uint32_t n = words.size();
  if (!n)
    return {};

  uint32_t len = 0, nums = 0, first = 0;
  bool lastline = false;
  vector<string> res;

  auto justify = [&]() {
    string str;
    if (lastline || nums == 1) {
      for (uint32_t i = first; i < first+nums; ++i) {
        str += words[i];
        if (i < first+nums-1)
          str += " ";
      }

      str += string(L-str.size(), ' ');
      res.push_back(str);
      return;
    }

    int spaces = L-len;
    int fix = spaces / (nums-1);
    int spare = spaces % (nums-1);

    for (uint32_t i = first; i < first+nums; ++i) {
      str += words[i];
      if (i < first+nums-1) {
        str += string(fix, ' ');
        if (spare-- > 0)
          str += " ";
      }
    }

    res.push_back(str);
  };

  for (uint32_t i = 0; i <= n; ++i) {
    if (i < n && len+words[i].length() <= L-nums) {
      len += words[i].length();
      ++nums;
    } else {
      if (i == n)
        lastline = true;

      justify();
      nums = 1;
      if (!lastline)
        len = words[i].length();
      first = i;
    }
  }

  return res;
}

int main(int argc, char** argv) {
  vector<string> v;
  v.push_back("This");
  v.push_back("is");
  v.push_back("an");
  v.push_back("example");
  v.push_back("of");
  v.push_back("text");
  v.push_back("justification.");

  vector<string> words = justify(v, 16);
  for (auto& i : words) {
    cout << "'" << i << "'" << endl;
  }
}
