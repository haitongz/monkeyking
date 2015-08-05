/*
Given a non-negative number represented as an array of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list.
*/
#include <iostream>
#include <vector>

using namespace std;
/*
vector<uint8_t> plusOne(vector<uint8_t> digits) {
  const uint32_t size = digits.size();
  int32_t i = size-1;
  bool prepend_one = false;

  while (i >= 0) {
    uint8_t digit = digits[i];
    if (digit < 9) {
      ++digits[i];
      break;
    } else {
      digits[i] = 0;
      if (i-1 < 0) {
        prepend_one = true;
        break;
      } else {
        --i;
      }
    }
  }

  if (prepend_one) {
    vector<uint8_t> ret;
    ret.push_back(1);
    for (uint32_t i = 0; i < size; ++i) {
      ret.push_back(digits[i]);
    }

    return ret;
  } else {
    return digits;
  }
}
*/
vector<uint8_t> plusOne(const uint8_t digits[], const uint32_t n) {
  vector<uint8_t> res;
  if (!n)
    return res;

  int32_t i = n-1;
  for (; i >= 0 && digits[i] == 9; --i)
    res[i] = 0;

  if (i >= 0)
    res[i]++;
  else
    res.insert(digits[0], 1);

  return res;
}

/*
#define M 200

void FlipZeros(int32_t mtx[M][N]) {
  set<uint32_t> rows, cols;

  for (uint32_t i = 0; i < M; ++i) {
    for (uint32_t j = 0; j < N; ++j) {
      if (!mtx[i][j]) {
        rows.insert(i);
        cols.insert(j);
      }
    }
  }

  for (set<uint32_t>::const_iterator it = rows.begin(); it != rows.end(); ++it) {
    for (uint32_t j = 0; j < N; ++j)
      mtx[*it][j] = 0;
  }

  for (set<uint32_t>::const_iterator it = cols.begin(); it != cols.end(); ++it) {
    for (uint32_t i = 0; j < M; ++i)
      mtx[i][*it] = 0;
  }
}
*/
int main(int argc, char** argv) {
  uint8_t a[] = {9,9,9,9};
  vector<uint8_t> res = plusOne(a, 4);

  for (uint8_t i = 0; i < res.size(); ++i)
    cout << res[i];
  cout << endl;
  return 0;
}
