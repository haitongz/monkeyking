/*
Given two binary strings, return their sum (also a binary string).
For example,
a = "11"
b = "1"
Return "100".
 */
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

string add2Binstrs(const string& bin1, const string& bin2) {
  const uint32_t len1 = bin1.length(), len2 = bin2.length();
  if (!len1 || !len2)
    return "";

  function<bool(const char)> isValid = [](const char c) {
    return (c == '1' || c == '0');
  };

  uint8_t carry = 0;
  string ret;

  for (int32_t i = len1-1, j = len2-1;
       (i >= 0 && isValid(bin1[i])) || (j >= 0 && isValid(bin2[j]));
       --i, --j) {
    uint8_t n1 = i >= 0 ? bin1[i]-'0' : 0;
    uint8_t n2 = j >= 0 ? bin2[j]-'0' : 0;
    uint8_t sum = n1+n2+carry;
    carry = sum/2;
    sum %= 2;
    ret.push_back(sum+'0');
  }

  if (carry)
    ret.push_back(carry+'0');

  reverse(ret.begin(), ret.end());
  return ret;
}

int main(int argc, char** argv) {
  string bin1 = "1", bin2 = "11";
  cout << "Add 2 binary strings " << bin1 << " and " << bin2 << ", result is: " << add2Binstrs(bin1, bin2) << endl;
}
