/*
There are six kinds of gifts. One piece of first kind has value 1,..., 6 has value 6. Given different numbers of gifts, how to give'em to two people so that they get equal value?
 */
#include <iostream>
#include <cstring> // for bzero

using namespace std;

#define MAX 50000

uint32_t count[7], value[7], total, mid;
uint32_t dp[MAX];

void comprletePack(const uint32_t weight, const uint32_t value) {
  for (uint32_t i = weight; i <= mid; ++i) {
    dp[i] = max(dp[i], dp[i-weight]+value);
  }
}

void onezeroPack(const uint32_t weight, const uint32_t value) {
  for (uint32_t i = mid; i >= weight; --i) {
    dp[i] = max(dp[i], dp[i-weight]+value);
  }
}

int main(int argc, char** argv) {
  uint32_t i, cnt = 0;
  for (i = 1; i < 7; ++i)
    value[i] = i;

  while (cin>>count[1]>>count[2]>>count[3]>>count[4]>>count[5]>>count[6] && (count[1]||count[2]||count[3]||count[4]||count[5]||count[6])) {
    ++cnt;
    bzero(dp, MAX);

    cout << "Collection #" << cnt << ":" << endl;
    total = 0;
    for (i = 1; i < 7; ++i) {
      total += value[i]*count[i];
    }

    if (total%2) {
      cout << "Can't be divided." << endl;
      continue;
    } else {
      mid = total/2;
      for (i = 1; i < 7; ++i) {
        if (count[i] > 0) {
          if (count[i]*value[i] >= mid) {
            comprletePack(value[i], value[i]);
            continue;
          }
          uint32_t k = 1;
          while (k < count[i]) {
            onezeroPack(value[i]*k, value[i]*k);
            count[i] -= k;
            k <<= 1;
          }
          onezeroPack(value[i]*count[i], value[i]*count[i]);
        }
        if (dp[mid] == mid)
          cout << "Can be divided." << endl;
        else
          cout << "Can't be divided." << endl;
      }
    }
  }

  return 0;
}
