/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.
 */
#include <iostream>

using namespace std;

string countAndSay(const uint n) {
  if (n < 1)
    return "";

  string prev = "1";
  for (uint i = 2; i <= n; ++i) { // need to generate all previous numbers to get Nth
    char curr = prev[0];
    uint cnt = 1;
    string tmp;
    prev.push_back('#');
    const uint len = prev.length();

    for (uint j = 1; j < len; ++j) {
      if (prev[j] == curr) {
        ++cnt;
      } else {
        tmp += to_string(cnt);
        tmp.push_back(curr);
        curr = prev[j];
        cnt = 1;
      }
    }

    prev = tmp;
  }

  return prev;
}

int main(int argc, char** argv) {
  uint n = 10;
  for (uint i = 1; i < n+1; ++i)
    cout << countAndSay(i) << endl;

  return 0;
}
