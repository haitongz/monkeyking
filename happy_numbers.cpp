/*
A happy number is defined by the following process. Starting with any positive integer,
replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1
(where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy numbers,
while those that do not end in 1 are unhappy numbers (or sad numbers).

For example, 7 is a happy number, as 72=49, 42+92=16+81=97, 92+72=81+49=130, 12+32+02=1+9+0=10, and 12+02=1+0=1.
But 17 is not a happy number, as 12+72=1+49=50, 52+02=25+0=25, 22+52=4+25=29, 22+92=4+81=85, 82+52=64+25=89, 82+92=64+81=145,
12+42+52=1+16+25=42, 42+22=16+4=20, 22+02=4+0=4, 42=16, 12+62=1+36=37, 32+72=9+49=58, and 52+82=25+64=89, which forms a loop.

Write a function to identify the happy numbers less than a given limit.
 */
#include <iostream>
#include <bitset>

using namespace std;

bool isHappy(int32_t x) {
  bitset<100000> founds;

  do {
    founds.set(x);
    int32_t num = 0;

    while (x) {
      int32_t d = x%10;
      num += d*d;
      x /= 10;
    }
    x = num;
  } while (x != 1 && !founds.test(x));

  return (x == 1) ? true : false;
}

int main(int argc, char** argv) {
  int32_t x = 7;
  cout << x << " is " << (isHappy(x) ? "" : "not ") << "a happy number!" << endl;
  x = 17;
  cout << x << " is " << (isHappy(x) ? "" : "not ") << "a happy number!" << endl;

  return 0;
}
