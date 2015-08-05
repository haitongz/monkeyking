/*
Find longest substr with k unique chars in it
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

string longestSubstrWithKUniques(const string& s, const uint32_t k) { // sliding window
  if (!k)
    return "";
  const uint32_t len = s.length();
  if (len < k)
    return "";

  uint32_t count[26];
  uint32_t total_uniq = 0;
  // Traverse the string, Fills the associative array count[] and count number of unique characters
  for (uint32_t i = 0; i < len; ++i) {
    uint8_t idx = s[i]-'a';
    if (count[idx]++)
      ++total_uniq;
  }

  // If there are not enough unique characters, show an error message.
  if (total_uniq < k) {
    cout << "Not enough unique characters";
    return "";
  }

  // Initialize associative array count[] with zero
  for (auto& i : count)
    i = 0;

  ++count[s[0]-'a'];  // put the first character
  uint32_t curr_uniq = 1;
  // Otherwise take a window with first element in it. start and end variables.
  uint32_t curr_start = 0, curr_end = 0;
  // Also initialize values for result longest window
  uint32_t maxwindow_size = 1, maxwindow_start = 0;

  for (uint32_t i = 1; i < len; ++i) {
    uint8_t idx = s[i]-'a';
    if (!count[idx]++) // Add the character 's[i]' to current window: if number of unique chars is still less than k, we just got a longer substring.
      ++curr_uniq;
    ++curr_end;

    // If number of unique chars already exceeds k there's no need to go
    // further as it can only have more unique chars. We shall remove from left
    // because removing from right doesn't make a substring.
    while (k < curr_uniq) {
      idx = s[curr_start++]-'a';
      if (!--count[idx]) // Remove from left
        --curr_uniq;
    }

    if (curr_end-curr_start+1 > maxwindow_size) { // Update the max window size if required
      maxwindow_size = curr_end-curr_start+1;
      maxwindow_start = curr_start;
    }
  }

  return s.substr(maxwindow_start, maxwindow_size);
}

int main(int argc, char** argv) {
  string s = "aabacbebebe";
  const uint32_t k = 3;
  string res = longestSubstrWithKUniques(s, k);
  cout << "Max sustring is : " << res << endl;

  s = "aaaaaabccccccddd";
  res = longestSubstrWithKUniques(s, k);
  cout << "Max sustring is : " << res << endl;

  return 0;
}
