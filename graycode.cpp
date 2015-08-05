/*
The gray code is a binary numeral system where two successive values differ in only one bit. Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

Given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2

Note:
For a given n, a gray code sequence is not uniquely defined.
 */
#include <iostream>
#include <vector>

using namespace std;

// Refer to http://en.wikipedia.org/wiki/Gray_code
vector<int32_t> grayCode(const uint32_t n) {
  vector<int32_t> res;
  if (!n) {
    res.push_back(0);
    return res;
  }

  vector<int32_t> tmp = grayCode(n-1);
  res = tmp;
  for (int32_t i = tmp.size()-1; i >= 0; --i) {
    res.push_back(tmp[i] | (1 << (n-1)));
  }

  return res;
}

vector<int32_t> grayCode2(const uint32_t n) {
  vector<int32_t> res;
  res.push_back(0);

  for (uint32_t i = 0; i < n; ++i) {
    uint32_t highestBit = 1<<i;
    const uint32_t len = res.size();
    for (int32_t j = len-1; j >= 0; --j) {
      res.push_back(highestBit+res[j]);
    }
  }

  return res;
}

int main(int argc, char** argv) {
  vector<int32_t> res = grayCode(3);
  for (uint32_t i = 0; i < res.size(); ++i)
    cout << res[i] << ",";
  cout << endl;

  res = grayCode2(3);
  for (uint32_t i = 0; i < res.size(); ++i)
    cout << res[i] << ",";
  cout << endl;

  return 0;
}
