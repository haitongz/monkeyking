/*
Given a string 'str' of digits, find length of the longest substring of 'str',
such that the length of the substring is 2k digits and sum of left k digits is equal to the sum of right k digits.

Input: str = "123123"
Output: 6
The complete string is of even length and sum of first and second half digits is same

Input: str = "1538023"
Output: 4
The longest substring with same first and second half sum is "5380"
 */
#include <iostream>

using namespace std;

uint findLength(const string& str) {
  const uint len = str.length();
  if (!len) {
    return 0;
  }

  uint ret = 0;

  // Consider all possible midpoints one by one
  for (uint i = 0; i <= len-2; ++i) {
    /* For current midpoint 'i', keep expanding substring on both sides, if sum
    ** of both sides becomes equal update ret */
    int l = i, r = i+1;

    /* initialize left and right sum */
    uint lsum = 0, rsum = 0;

    /* move on both sides till indexes go out of bounds */
    while (r < len && l >= 0) {
      lsum += str[l]-'0';
      rsum += str[r]-'0';
      if (lsum == rsum) {
        ret = max(ret, (uint)r-l+1);
      }
      --l;
      ++r;
    }
  }

  return ret;
}

int main(int argc, char** argv) {
  string str = "123123";
  cout << "Length of the substring is " << findLength(str) << endl;

  return 0;
}
