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

/*
Given two numbers represented as strings, return multiplication of the numbers as a string.
Note: The numbers can be arbitrarily large and are non-negative.
 */
string multiplyStrs(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2)
    return "";

  string ret(len1+len2, '0');

  for (int32_t i = len1-1, d = ret.length()-1; i >= 0; --i, --d) {
    uint8_t carry = 0;
    int32_t k = d;
    for (int32_t j = len2-1; j >= 0; --j, --k) {
      uint8_t a = s1[i]-'0';
      uint8_t b = s2[j]-'0';
      a = a*b+carry+(ret[k]-'0');
      carry = a/10;
      ret[k] = a%10+'0';
    }

    while (carry) {
      uint32_t sum = carry+(ret[k]-'0');
      carry = sum/10;
      ret[k--] = sum%10+'0';
    }
  }

  // remove prepending 0s
  while (ret.size() > 1 && ret[0] == '0')
    ret.erase(ret.begin());

  return ret;
}

string multiplyStrs_2(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2)
    return "";

  const string& short_str = len1 < len2 ? s1 : s2;
  const uint32_t s_len = short_str.length();
  const string& long_str = len1 < len2 ? s2 : s1;
  const uint32_t l_len = long_str.length();

  string ret(len1+len2, '0');

  for (int32_t i = s_len-1, l = len1+len2-1; i >= 0; --i, --l) {
    uint8_t carry = 0;
    int32_t k = l;
    for (int32_t j = l_len-1; j >= 0; --j, --k) {
      uint8_t a = short_str[i]-'0';
      const uint8_t b = long_str[j]-'0';
      a = a*b+carry+(ret[k]-'0');
      carry = a/10;
      ret[k] = a%10+'0';
    }

    while (carry) {
      uint32_t sum = carry+(ret[k]-'0');
      carry = sum/10;
      ret[k--] = sum%10+'0';
    }
  }

  // remove prepending 0s
  while (ret.size() > 1 && ret[0] == '0')
    ret.erase(ret.begin());

  return ret;
}

int main(int argc, char** argv) {
  string bin1 = "1", bin2 = "11";
  cout << "Add 2 binary strings " << bin1 << " and " << bin2 << ", result is: " << add2Binstrs(bin1, bin2) << endl;
  
  string str1 = "1000"; //3579432"
  string str2 = "200000"; //94582745";
  cout << str1 << " X " << str2 << " = " << multiplyStrs(str1, str2) << endl;
  cout << str1 << " X " << str2 << " = " << multiplyStrs_2(str1, str2) << endl;
}
