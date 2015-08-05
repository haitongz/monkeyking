/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.
 */
#include <iostream>
#include "../strings/itoa.h"

using namespace std;

string countAndSay(const uint32_t n) {
  if (n < 1)
    return "";

  string prev = "1";
  for (uint32_t i = 2; i <= n; ++i) { // need to generate all previous numbers to get Nth
    char curr = prev[0];
    uint16_t cntr = 1;
    string tmp;
    prev.push_back('#');
    const uint32_t len = prev.length();

    for (uint32_t j = 1; j < len; ++j) {
      if (prev[j] == curr) {
        ++cntr;
      } else {
        char buf[10];
        itoa(buf, cntr, 10);
        tmp += string(buf);
        tmp.push_back(curr);
        curr = prev[j];
        cntr = 1;
      }
    }

    prev = tmp;
  }

  return prev;
}

int main(int argc, char** argv) {
  uint32_t n = 10;
  for (uint32_t i = 1; i < n+1; ++i)
    cout << countAndSay(i) << endl;
}
