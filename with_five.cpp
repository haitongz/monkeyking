/*
Write a function to ouput all numbers with 5 in it. func(60) output is 5,15,25,35,45,50,51,52,53,54,55,56,57,58,59
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include "../strings/itoa.h"

using namespace std;

vector<uint32_t> numsWith5(const uint32_t n) {
  if (n < 5)
    return {};

  char s[32];
  itoa(n, s);
  const string number(s);
  const uint32_t len = number.length();
  string to_ext = "";
  vector<uint32_t> ret;

  function<void(const uint32_t,const bool)> solve = // backtracking
    [&](const uint32_t idx, const bool there_is_5) {
    if (idx == len) {
      ret.push_back(atoi(to_ext.c_str()));
      return;
    } else if (idx < len-1 || there_is_5) {
      for (uint8_t i = 0; i < 10; ++i) {
        char buf[2]; // notice: use extra byte for '\0'
        itoa(i, buf);
        to_ext += string(buf);
        string new_num = number.substr(0, idx+1);
        if (atoi(to_ext.c_str()) <= atoi(new_num.c_str())) {
          solve(idx+1, (i == 5) ? true : there_is_5);
        }
        to_ext.pop_back();
      }
    } else { // second last digit, idx == len-1 && !there_is_5
      to_ext += '5';
      const uint32_t new_num = atoi(to_ext.c_str());
      if (new_num < n) // need to be less than n
        ret.push_back(new_num);
      to_ext.pop_back();
    }
  };

  solve(0, false);
  return ret;
}

int main(int argc, char** argv) {
  const uint32_t n = 1000;
  vector<uint32_t> res = numsWith5(n);
  for (auto i : res)
    cout << i << " ";
  cout << endl;

  return 0;
}
