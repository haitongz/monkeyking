/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:
 */
#include <iostream>
#include <sstream>

using namespace std;

#define N 256

string zigZagPrint(const string& str, const uint32_t rows) {
  char matrix[N][rows]; // suppose N is big enough...
  const uint32_t mid_row = rows/2;
  const char* c = str.c_str();
  bool zigzag = true;
  for (uint32_t i = 0; i < N; ++i) {
    for (uint32_t j = 0; j < rows; ++j) {
      if (zigzag) {
        if (*c) {
          matrix[i][j] = *c;
          ++c;
        } else {
          matrix[i][j] = '\0';
        }
      } else {
        if (j == mid_row && (*c)) {
          matrix[i][j] = *c;
          ++c;
        } else {
          matrix[i][j] = '\0';
        }
      }
    }
    zigzag = zigzag ? false : true;
  }

  ostringstream oss;
  for (uint32_t i = 0; i < rows; ++i) {
    for (uint32_t j = 0; j < N; ++j) {
      if (matrix[j][i]) {
        oss << matrix[j][i];
      }
    }
  }

  return oss.str();
}

int main() {
  const string str = "PAYPALISHIRING\0";
  cout << "Zigzag output: " << zigZagPrint(str, 3) << endl;
}
