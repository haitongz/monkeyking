/*
Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.
 */
#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define MAX_N 3999

string intToRoman(uint32_t n) {
  if (n > MAX_N)
    return "";

  vector<string> tb = {"IV","XL","CD","M"};

  string ret;
  uint8_t idx = 0;

  while (n) {
    auto dig = n%10;
    n /= 10;

    string curr;
    if (dig < 4) {
      for(uint8_t i = 0; i < dig; ++i)
        curr += tb[idx][0];
    } else if (dig == 4) {
      curr += tb[idx][0];
      curr += tb[idx][1];
    } else if (dig < 9) {
      curr += tb[idx][1];
      for (uint8_t i = 0; i < dig-5; ++i)
        curr += tb[idx][0];
    } else if (dig == 9) {
      curr += tb[idx][0];
      curr += tb[idx+1][0];
    }

    ret = curr + ret;
    ++idx;
  }

  return ret;
}

uint16_t romanToInt(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    throw exception();

  map<char,uint16_t> tb = {{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
  int32_t value = 0;
  int32_t last = 0;

  for (int32_t i = len-1; i >= 0; --i) {
    auto curr = tb[s[i]];
    if (curr >= last) {
      value += curr;
    } else {
      value -= curr;
    }

    last = curr;
  }

  return value;
}

int main(int argc, char** argv) {
  const uint16_t n = 3999;
  cout << intToRoman(n) << endl;
  string s = "IVCDM";
  cout << romanToInt(s) << endl;
}
