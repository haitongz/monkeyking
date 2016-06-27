#include <iostream>
#include <vector>
#include "../linked_lists/list_node.h"

using namespace std;

#define MAX_CHAR 256

/*
A string is composed of a shorter substring repeating n times. Minimum substring length is 2.
Check whether a string is such case.

For example,
"abcabcabc"  -> true
"bcdbcdbcde" -> false
"abcdabcd"   -> true
"xyz"        -> false
"aaaaaaaaaa" -> false

O(n) is required
 */
bool isRepeat(const string& s) {
  const uint len = s.length();
  if (!len)
    return false;

  vector<uint> prefix(len, 0);

  for (uint i = 1, j = 0; i < len; ++i) {
    while (j && s[i] != s[j])
      j = prefix[j-1];

    if (s[i] == s[j])
      ++j;

    prefix[i] = j;
  }

  int d = len-prefix[len-1], idx = d-1, curr_res = 0;
  if (d < 2)
    return false;

  bool ret = false;
  while (true) {
    if (idx == len-1)
      return ret;
    else if (idx >= len)
      return false;

    if (prefix[idx] != curr_res)
      return false;
    else {
      idx += d;
      curr_res += d;
    }

    ret = true;
  }

  return ret;
}

/*
Given a string, find the length of the longest substring without repeating characters.
For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3.
For "bbbbb" the longest substring is "b", with the length of 1.
 */
/*
uint longestUniqueSubstrLen(const string& s) {
  const uint len = s.length();
  if (!len)
    return 0;

  uint ret = 0;

  for (int i = len-1; i >= 0; --i) {
    for (uint j = i; j < len; ++j) {
      string i2j = s.substr(i, j-i+1);
      const uint sub_len = i2j.length();
      bool no_repeat = true;

      for (uint k = 0; k < sub_len; ++k) {
        for (uint l = k+1; l < sub_len; ++l) {
          if (i2j[k] == i2j[l]) {
            no_repeat = false;
            break;
          }
        }
        if (!no_repeat)
          break;
      }
      if (no_repeat) {
        ret = max(ret, sub_len);
      }
    }
  }

  return ret;
}
*/
uint longestUniqueSubstrLen(const string& s) { // O(n)
  const uint len = s.length();
  if (!len)
    return 0;

  int visited[MAX_CHAR];
  for (auto& i : visited)
    i = -1; /* -1 is used to indicate that character has not been visited yet. */
  visited[s[0]] = 0;

  uint curr_len = 1; // length of current substring
  uint ret = 1;

  for (uint i = 1; i < len; ++i) {
    int prev_idx = visited[s[i]];

    // If the current character is not present in the already processed substring or
    // it is not part of the current NRCS increment curr_len
    if (prev_idx == -1 || (i-curr_len > prev_idx/*this means not part of current NRCS*/))
      ++curr_len;
    else { /* If the current character is present in currently considered NRCS,
              then update NRCS to start from the next character of previous instance.
              Also, when we are changing the NRCS, we should also check whether length of
              the previous NRCS was greater than max_len or not.*/
      ret = max(curr_len, ret);
      curr_len = i-prev_idx;
    }

    visited[s[i]] = i; // update the index of current character
  }

  // Compare the length of last NRCS
  ret = max(curr_len, ret);
  return ret;
}

/*
Find first non-repeating character in a string. If all characters are repeating then reurn INT_MAX
 */
struct Data {
  uint index;
  uint count;
};

int firstNonRepeating(char* str) {
  Data d[MAX_CHAR];

  function<void(const char*)> scan = [&](const char* s) {
    if (!s)
      return;

    for (uint i = 0; *(s+i); ++i) {
      ++d[*(s+i)].count;

      // If it's first occurrence, then store the index
      if (d[*(s+i)].count == 1)
        d[*(s+i)].index = i;
    }

    return d;
  };

  scan(str);
  int ret = -1;

  for (uint i = 0; i < MAX_CHAR; ++i) {
    // If this character occurs only once and appears before the current result, then update the result
    if (d[i].count == 1 && result > d[i].index)
      result = d[i].index;
  }

  return ret;
}

/*
Given a stream of characters, find the first non-repeating character from stream.
You need to tell the first non-repeating character in O(1) time at any moment.
 */
void appendNode(DListNodeT<char>** head_ref, DListNodeT<char>** tail_ref, const char x) {
  DListNodeT<char>* tmp = new DListNodeT<char>(x);
  // temp->prev = temp->next = NULL;

  if (!(*head_ref)) {
    *head_ref = *tail_ref = tmp;
    return;
  }

  (*tail_ref)->next = tmp;
  tmp->prev = *tail_ref;
  *tail_ref = tmp;
}

// A utility function to remove a node 'temp' fromt DLL.
// Note that the function may change head and tail pointers, that is why pointers to these pointers are passed.
void removeNode(DListNodeT<char>** head_ref, DListNodeT<char>** tail_ref, DListNodeT<char>* tmp) {
  if (!head_ref || !(*head_ref))
    return;

  if (*head_ref == tmp)
    *head_ref = (*head_ref)->next;
  if (*tail_ref == tmp)
    *tail_ref = (*tail_ref)->prev;
  if (tmp->next)
    tmp->next->prev = tmp->prev;
  if (tmp->prev)
    tmp->prev->next = tmp->next;

  delete tmp;
}

void findFirstNonRepeating(istream& strm) {
  // inDLL[x] contains pointer to a DLL node if x is present in DLL. If x is not present, then inDLL[x] is NULL
  DListNodeT<char>* inDLL[MAX_CHAR];

  // repeated[x] is true if x is repeated two or more times.
  // If x is not seen so far or x is seen only once. then repeated[x] is false
  bool repeated[MAX_CHAR];

  // Initialize the above two arrays
  DListNodeT<char>* head = nullptr, *tail = nullptr;
  for (uint8_t i = 0; i < MAX_CHAR; ++i) {
    inDLL[i] = nullptr;
    repeated[i] = false;
  }

  char s[MAX_CHAR+1];
  strm = strm.get(s, MAX_CHAR);

  for (uint i = 0; s[i]; ++i) {
    char x = s[i];
    cout << "Reading " << x << " from stream \n";

    // We process this character only if it has not occurred or occurred only once.
    // repeated[x] is true if x is repeated twice or more.s
    if (!repeated[x]) {
      // If the character is not in DLL, then add this at the end of DLL.
      if (!inDLL[x]) {
        appendNode(&head, &tail, s[i]);
        inDLL[x] = tail;
      } else { // Otherwise remove this caharacter from DLL
        removeNode(&head, &tail, inDLL[x]);
        inDLL[x] = nullptr;
        repeated[x] = true;  // Also mark it as repeated
      }
    }

    // Print the current first non-repeating character from stream
    if (head)
      cout << "First non-repeating character so far is " << head->value << endl;
  }
}

int main(int argc, char** argv) {
  cout << (isRepeat("abcabcabc") ? "true" : "false") << endl;
//"bcdbcdbcde" -> false
//"abcdabcd"   -> true
//"xyz"        -> false
//"aaaaaaaaaa" -> false
  string s1 = "abcabcbb";
  string s2 = "bbbbb";
  cout << "Length of longest non repeating substring is " << longestNoRepeatSubstrLen(s1) << endl;
  cout << "Length of longest non repeating substring is " << longestNoRepeatSubstrLen(s2) << endl;


  return 0;
}
