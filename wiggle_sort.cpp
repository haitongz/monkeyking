/*
Sort an array so that a1 <= a2 >= a3 <= a4 >=...
*/
#include <iostream>
#include <vector>

using namespace std;

void wiggleSort(vector<int32_t>& a){
  const uint32_t n = a.size();
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
}

int main(int argc, char** argv) {
  vector<int32_t> a = {23, -10, 293, 95, 93, -84, -100, 94, -32};
  wiggleSort(a);
  for (uint32_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ",";
  }
  cout << endl;
  return 0;
}
