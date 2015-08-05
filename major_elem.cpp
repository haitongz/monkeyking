/*
Majority Element: A majority element in an array A[] of size n is an element that appears more than n/2 times (and hence there is at most one such element).

Write a function which takes an array and emits the majority element (if it exists), otherwise prints NONE
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
Moore's voting algorithm: cancel out each occurrence of an element e with all the other elements that are different from e then e will exist till end if it is a majority element.
Time complexity: O(n)
Auxiliary space: O(1)
 */
int32_t majorityElement(const vector<int32_t>& a) {
  const uint32_t n = a.size();
  if (!n)
    return {};

  function<int32_t()> voting = [&]() {
    uint32_t maj_idx = 0, count = 1;
    for (uint32_t i = 1; i < n; ++i) {
      if (a[maj_idx] == a[i])
        ++count;
      else
        --count;

      if (!count) {
        maj_idx = i;
        count = 1;
      }
    }

    return a[maj_idx];
  };

  int32_t cand = voting();
  uint32_t count = 0;

  for (uint32_t i = 0; i < n; ++i)
    if (a[i] == cand)
      ++count;

  return (count > n/2) ? cand : -1;
}

int main(int argc, char** argv) {
  vector<int32_t> a = {1, 3, 3, 1, 2};
  int32_t e = majorityElement(a);
  if (e != -1)
    cout << e << endl;

  return 0;
}
