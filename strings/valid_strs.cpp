/*
String can only have A or B or C. If any consective three letters are different, the string is invalid.
For example, ABBBCA is invalid while ACCBCCA is valid.

Given legnth n, find out how many valid strings are there.
 */
#include <iostream>
#include <vector>

using namespace std;

uint validStrs(const uint n) {
  if (n < 3)
    return 0;

  uint lastSame = 3;
  uint lastDiff = 0;

  for (uint i = 1; i < n; ++i) {
    auto newSame = lastSame+lastDiff;
    lastDiff = lastSame*2+lastDiff;
    lastSame = newSame;
  }

  return lastSame+lastDiff;
}

int main(int argc, char** argv) {
  const uint n = 3;
  cout << "There are " << validStrs(n) << " valid strings with length " << n << endl;

  return 0;
}
