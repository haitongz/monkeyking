/*
Given an array of integers, every element appears twice except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
#include <iostream>

int32_t singleNumberI(const int32_t A[], const uint32_t n) {
  int32_t res = 0;
  for (uint32_t i = 0; i < n; ++i)
    res ^= A[i];
  return res;
}

/*
Single Number II
Given an array of integers, every element appears three times except for one. Find that single one.
Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
int32_t singleNumberII_36(const int32_t A[], const uint32_t n) {
  int32_t res = 0;

  for (uint8_t i = 0; i < 32; ++i) {
    uint32_t c = 0, d = 1<<i;
    for (uint32_t j = 0; j < n; ++j)
      if (A[j]&d)
        ++c;

    if (c%3)
      res |= d;
  }

  return res;
}

int main(int argc, char** argv) {
}
