#include <iostream>
#include <sstream>

using namespace std;

string compress(const string& str) {
  const uint32_t len = str.length();
  if (!len)
    return "";

  string res;
  char curr = str[0];
  uint32_t cntr = 1, idx = 1;

  while (idx <= len) {
    if (idx < len && str[idx] == curr) {
      ++cntr;
    } else {
      res.push_back(curr);
      ostringstream oss;
      oss << cntr;
      res += oss.str();

      if (idx < len)
        curr = str[idx];

      cntr = 1;
    }

    ++idx;
  }

  return (res.length() < len) ? res : str;
}

int main(int argc, char** argv) {
  string str = "vcvzzcvzcvdsfadfffffer-234343434343";
  cout << "Compressed string is: " << compress(str) << endl;
}
