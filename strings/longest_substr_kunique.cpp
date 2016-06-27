/*
Find longest substr with k unique chars in it
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

string longestSubstrWithKUniques(const string& s, const uint k) { // sliding window
  if (!k) {
    return "";
  }

  const uint len = s.length();
  if (len < k) {
    return "";
  }

  uint count[26];
  uint uniqueCharNo = 0;
  // Traverse the string, Fills the associative array count[] and count number of unique characters
  for (uint i = 0; i < len; ++i) {
    uint idx = s[i]-'a';
    if (count[idx]++) {
      ++uniqueCharNo;
    }
  }

  // If there are not enough unique characters, show an error message.
  if (uniqueCharNo < k) {
    cout << "Not enough unique characters";
    return "";
  }

  // Initialize associative array count[] with zero
  for (auto& i : count) {
    i = 0;
  }

  ++count[s[0]-'a'];  // put the first character
  uniqueCharNo = 1;
  // Otherwise take a window with first element in it. start and end variables.
  uint start = 0, end = 0;
  // Also initialize values for result longest window
  uint winSize = 1, winStart = 0;

  for (uint i = 1; i < len; ++i) {
    uint idx = s[i]-'a';
    if (!count[idx]++) { // Add the character 's[i]' to current window: if number of unique chars is still less than k, we just got a longer substring.
      ++uniqueCharNo;
    }
    ++end;

    // If number of unique chars already exceeds k there's no need to go
    // further as it can only have more unique chars. We shall remove from left
    // because removing from right doesn't make a substring.
    while (k < uniqueCharNo) {
      idx = s[start++]-'a';
      if (!--count[idx]) { // Remove from left
        --uniqueCharNo;
      }
    }

    if (end-start+1 > winSize) { // Update the max window size if required
      winSize = end-start+1;
      winStart = start;
    }
  }

  return s.substr(winStart, winSize);
}

int main(int argc, char** argv) {
  string s = "aabacbebebe";
  const uint k = 3;
  string res = longestSubstrWithKUniques(s, k);
  cout << "Max sustring is : " << res << endl;

  s = "aaaaaabccccccddd";
  res = longestSubstrWithKUniques(s, k);
  cout << "Max sustring is : " << res << endl;

  return 0;
}
