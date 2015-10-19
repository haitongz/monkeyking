/*
A magic number is defined as a number which can be expressed as a power of 5 or sum of unique powers of 5.
First few magic numbers are 5, 25, 30(5 + 25), 125, 130(125 + 5), ...

Write a function to find the n¿th Magic number.
 */
#include <iostream>

using namespace std;

uint32_t nthMagicNum(const uint32_t n) {
  if (!n)
    throw exception();

  queue<uint32_t> q = {5};
  while (q.size() <= n) {
  }
}
