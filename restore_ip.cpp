/*
Given a string containing only numofparts, restore it by returning all possible valid IP address combinations.For example:
Given "25525511135",return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

bool isLegal(const string& s) {
  if (s.empty() || s.length() > 3 || (s.length() != 1 && s[0] == '0'))
    return false;

  return (atoi(s.c_str()) < 256);
}

vector<string> restoreIPAddresses(const string& s) {
  const uint32_t len = s.length();
  if (len < 4) // something like 1111
    return {};

  vector<string> res;
  string to_ext;

  function<void(const uint32_t,const uint32_t)> backtrack =
    [&](const uint32_t numofparts, const uint32_t idx) {
    if (numofparts == 4) {
      string t = s.substr(idx); // substring from index to the end
      if (isLegal(t))
        res.push_back(to_ext+"."+t);
      return;
    }

    for (uint32_t sub_len = 1; sub_len <= 3 && idx+sub_len < len; ++sub_len) {
      string t = s.substr(idx, sub_len);
      if (!isLegal(t))
        return;
      if (numofparts != 1)
        to_ext.append(".");
      to_ext.append(t);

      backtrack(numofparts+1, idx+sub_len);

      // clean up
      while (!to_ext.empty() && to_ext[to_ext.length()-1] != '.')
        to_ext = to_ext.substr(0, to_ext.length()-1); // remove last char
      if (!to_ext.empty())
        to_ext = to_ext.substr(0, to_ext.length()-1); // remove last char
    }
  };

  backtrack(1, 0);
  return res;
}

int main(int argc, char** argv) {
  vector<string> ips = restoreIPAddresses(string("25525511135"));
  for (uint32_t i = 0; i < ips.size(); ++i) {
    cout << "[" << ips[i] << "], ";
  }
  cout << endl;
}
