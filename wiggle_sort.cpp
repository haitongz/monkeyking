/*
Sort an array so that a1 <= a2 >= a3 <= a4 >=...
 */
#include <iostream>

using namespace std;

void wiggleSort(int32_t a[], const uint32_t n) {
  if (!n)
    return;

  bool flag = true;
  int32_t curr = a[0];

  for (uint32_t i = 0; i < n-1; ++i) {
    if ((flag && curr > a[i+1]) || (!flag && curr < a[i+1])) {
      a[i] = a[i+1];
    } else {
      a[i] = curr;
      curr = a[i+1];
    }
    flag = !flag;
  }

  a[n-1] = curr;

  for (uint32_t i = 0; i < n; ++i)
    cout << a[i] << ",";
  cout << endl;
}

int main(int argc, char** argv) {
  int32_t a[10] = {23, -10, 293, 95, 93, -84, -100, 94, -32};
  wiggleSort(a, 10);

  return 0;
}
