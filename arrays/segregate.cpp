#include <iostream>
#include <vector>

using namespace std;

/*
Given an array A[], write a function that segregates even and odd numbers.
The functions should put all even numbers first, and then odd numbers.

Input = {12, 34, 45, 9, 8, 90, 3}
Output = {12, 34, 8, 90, 45, 9, 3}
 */
void segregate(vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return;

  uint32_t low = 0;
  int32_t high = n-1;

  while (low < high) {
    while (a[low]%2 == 0 && low < high)
      ++low;
    while (a[high]%2 != 0 && low < high)
      --high;

    if (low < high)
      swap(a[low++], a[high--]);
  }
}

/*
Given an array of positive integers.
All numbers occur even number of times except one number which occurs odd number of times.
Find the number in O(n) time & constant space.
 */
uint32_t oddOccurNum(const vector<uint32_t>& a) {
  const uint32_t n = a.size();
  uint32_t ret = 0;

  for (uint32_t i = 0; i < n; ++i)
    ret ^= a[i];

  return ret;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {12, 34, 45, 9, 8, 90, 3};
  segregate(a);
  for (uint32_t i = 0; i < a.size(); ++i)
    cout << a[i] << ",";
  cout << endl;

  return 0;
}
