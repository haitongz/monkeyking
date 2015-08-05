/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".
 */
#include <iostream>

using namespace std;

string simplifyPath(const string& path) {
  const uint32_t len = path.length();
  if (!len)
    return "";

  string res("/");

  for (uint32_t i = 1; i < len; ++i) {
    string tmp;
    for (; i < len && path[i] != '/'; ++i)
      tmp.push_back(path[i]);

    if (tmp == "..") {
      if (res.length() > 1)
        res.pop_back();
      while (res.length() > 1 && res.back() != '/')
        res.pop_back();
    } else if (!tmp.empty() && tmp != ".") {
      res.append(tmp+"/");
    }
  }

  if (res.length() > 1)
    res.pop_back();

  return res;
}

int main(int argc, char** argv) {
  string path = "/home/";
  cout << simplifyPath(path) << endl;
  path = "/a/./b/../../c/";
  cout << simplifyPath(path) << endl;

  return 0;
}
