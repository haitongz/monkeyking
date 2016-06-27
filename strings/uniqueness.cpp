#include <iostream>

using namespace std;

bool isUnique1(const std::string& s) {
  bool a[256];
  bzero(a, sizeof(bool)*sizeof(a));

  uint len = s.length();
  for (uint i = 0; i < len; ++i) {
    int c = (int)s[i];
    if (a[c])
      return false;
    a[c] = true;
  }

  return true;
}

bool isUnique2(const std::string& s) {
  int a[8];
  bzero(a, sizeof(a)*sizeof(int));

  const uint len = s.length();
  for (uint i = 0; i < len; ++i) {
    int v = (int)s[i];
    int idx = v/32, shift = v%32;
    if (a[idx] & (1<<shift))
      return false;
    a[idx] |= (1<<shift);
  }

  return true;
}

bool isUnique3(const std::string& s) {
  int check = 0;
  const uint len = s.length();

  for (uint i = 0; i < len; ++i) {
    int v = (int)(s[i]-'a');
    if (check & (1<<v))
      return false;
    check |= (1<<v);
  }

  return true;
}

bool isUnique4(const char* str) {
  if (!str) { // A null string should be unique??
    return true;
  }

  int index = -1;
  char mask[32];
  bzero(mask, 32*sizeof(char)); // clear all the masks to 0

  // Scan the string and check whether it is unique
  while (str[++index] != '\0') {
    if ((mask[str[index]/8] & (1<<(str[index]%8))) != 0)
      return false;
    else
      mask[str[index]/8] |= 1<<(str[index]%8);
  }

  return true;
}

int main(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    std::cerr << "Illegal Argument!" << std::endl;
    return -1;
  }

  std::string str(argv[1]);
  std::cout << "String has " << (isUnique1(str) ? "no " : "") << "duplicate characters!" << std::endl;
 // std::cout << "String has " << (isUnique2(str) ? "no " : "") << "duplicate characters!" << std::endl;
  std::cout << "String has " << (isUnique3(str) ? "no " : "") << "duplicate characters!" << std::endl;
  std::cout << "String has " << (isUnique4(str.c_str()) ? "no " : "") << "duplicate characters!" << std::endl;
}
