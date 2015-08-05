/*
String can only have A or B or C. If any consective three letters are different, the string is invalid.
For example, ABBBCA is invalid while ACCBCCA is valid.

Given legnth n, find out how many valid strings are there.
 */
#include <iostream>
#include <vector>

using namespace std;

uint32_t validStrs(const uint32_t n) {
  if (n < 3)
    return 0;

  uint32_t last_same = 3;
  uint32_t last_diff = 0;

  for (uint32_t i = 1; i < n; ++i) {
    auto new_same = last_same+last_diff;
    last_diff = last_same*2+last_diff;
    last_same = new_same;
  }

  return last_same+last_diff;
}

int main(int argc, char** argv) {
  const uint32_t n = 3;
  cout << "There are " << validStrs(n) << " valid strings with length " << n << endl;

  return 0;
}
