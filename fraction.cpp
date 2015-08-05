/*
Write a function which, given two integers (a numerator and a denominator), prints the decimal representation of the rational number "numerator/denominator".
Since all rational numbers end with a repeating section, print the repeating section of digits inside parentheses.
Example:
1 , 3 = 0.(3)
2 , 4 = 0.5
22, 7 = 3.(142857)
 */
#include <iostream>
#include <map>
#include "../strings/itoa.h"

using namespace std;

string fraction2Decimal(const int32_t n, const int32_t d) {
  if (!d)
    return "";
  if (!n)
    return "0";

  int32_t num = n, den = d;
  string res = (num*den < 0) ? "-" : "";

  num = abs(num);
  den = abs(den);
  char buf[10];
  res += itoa(num/den, buf, 10);

  num %= den;
  if (!num)
    return res;

  res.push_back('.');
  map<int32_t,uint32_t> rems;

  while (num && !rems.count(num)) {
    rems[num] = res.size();
    num *= 10;
    res += string(itoa(num/den, buf, 10));
    num %= den;
  }

  if (num) {
    res.insert(res.begin()+rems[num], '(');
    res += ")";
  }

  return res;
}

int main(int argc, char** argv) {
  int32_t n = 1, d = 3;
  cout << fraction2Decimal(n, d) << endl;

  n = 2;
  d = 4;
  cout << fraction2Decimal(n, d) << endl;

  n = 22;
  d = 7;
  cout << fraction2Decimal(n, d) << endl;

  return 0;
}
