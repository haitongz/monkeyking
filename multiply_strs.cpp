/*
Given two numbers represented as strings, return multiplication of the numbers as a string.
Note: The numbers can be arbitrarily large and are non-negative.
 */
#include <iostream>

using namespace std;

string multiplyStrs(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2)
    return "";

  string res(len1+len2, '0');

  for (int32_t i = len1-1, d = res.length()-1; i >= 0; --i, --d) {
    uint8_t carry = 0;
    int32_t k = d;
    for (int32_t j = len2-1; j >= 0; --j, --k) {
      uint8_t a = s1[i]-'0';
      uint8_t b = s2[j]-'0';
      a = a*b+carry+(res[k]-'0');
      carry = a/10;
      res[k] = a%10+'0';
    }

    while (carry) {
      uint32_t sum = carry+(res[k]-'0');
      carry = sum/10;
      res[k--] = sum%10+'0';
    }
  }

  // remove prepending 0s
  while (res.size() > 1 && res[0] == '0')
    res.erase(res.begin());

  return res;
}

string multiplyStrs2(const string& s1, const string& s2) {
  const uint32_t len1 = s1.length(), len2 = s2.length();
  if (!len1 || !len2)
    return "";

  const string& short_str = len1 < len2 ? s1 : s2;
  const uint32_t s_len = short_str.length();
  const string& long_str = len1 < len2 ? s2 : s1;
  const uint32_t l_len = long_str.length();

  string res(len1+len2, '0');

  for (int32_t i = s_len-1, l = len1+len2-1; i >= 0; --i, --l) {
    uint8_t carry = 0;
    int32_t k = l;
    for (int32_t j = l_len-1; j >= 0; --j, --k) {
      uint8_t a = short_str[i]-'0';
      const uint8_t b = long_str[j]-'0';
      a = a*b+carry+(res[k]-'0');
      carry = a/10;
      res[k] = a%10+'0';
    }

    while (carry) {
      uint32_t sum = carry+(res[k]-'0');
      carry = sum/10;
      res[k--] = sum%10+'0';
    }
  }

  // remove prepending 0s
  while (res.size() > 1 && res[0] == '0')
    res.erase(res.begin());

  return res;
}

int main(int argc, char** argv) {
  string str1 = "1000"; //3579432"
  string str2 = "200000"; //94582745";
  cout << str1 << " X " << str2 << " = " << multiplyStrs(str1, str2) << endl;
  cout << str1 << " X " << str2 << " = " << multiplyStrs2(str1, str2) << endl;
}
