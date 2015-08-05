#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
#include <cstring>
#include <map>
#include <functional>
#include "linked_lists/list_node.h"

using namespace std;

bool isPalindrome(const string& s) { // suppose no spaces
  const uint32_t len = s.length();
  if (len <= 1)
    return true; // need to confirm

  for (uint32_t i = 0, j = len-1; i < j; ++i, --j)
    if (s[i] != s[j])
      return false;

  return true;
};

/*
Given a string of lowercase ASCII characters, find all distinct continuous palindromic sub-strings of it.
 */
vector<string> distinctPalinSubstrs(const string& s) {
  const uint32_t len = s.length();
  if (!len)
    return {};

  set<string> ret;
  uint32_t curr_start = 0, curr_end = 0;

  while (curr_end < len) {
    ret.insert({s[curr_end]});
    string tmp = s.substr(curr_start, curr_end+1-curr_start);
    if (isPalindrome(tmp))
      ret.insert(tmp);

    if (++curr_end == len)
      curr_end = ++curr_start;
  }

  return vector<string>(ret.begin(), ret.end());
}

void distinctPalinSubStrs(string s) {
  const uint32_t len = s.length();
  if (!len)
    return;

  // Find all substring palindromes from the given input string insert 'guards' to iterate easily over s
  s = "@" + s + "#";
  // table for storing results (2 rows for odd- and even-length palindromes
  uint32_t R[2][len+1];

  for (uint32_t j = 0; j <= 1; ++j) {
    uint32_t rp = 0;   // length of 'palindrome radius'
    R[j][0] = 0;

    uint32_t i = 1;
    while (i < len+1) {
      while (s[i-rp-1] == s[i+j+rp]) // Attempt to expand palindrome centered at i
        ++rp; // Incrementing the length of palindromic radius as and when we find vaid palindrome

      // Assigning the found palindromic length to odd/even length array
      R[j][i] = rp;
      uint32_t k = 1;
      while (R[j][i-k] != rp-k && k < rp) {
        R[j][i+k] = min(R[j][i-k], rp-k);
        ++k;
      }

      rp = max((uint32_t)rp-k, (uint32_t)0);
      i += k;
    }
  }

  // remove 'guards'
  s = s.substr(1, len);

  // Put all obtained palindromes in a hash map to find only distinct palindromess
  map<string,uint32_t> m;
  m[string(1, s[0])] = 1;
  for (uint32_t i = 1; i < len+1; ++i) {
    for (uint8_t j = 0; j <= 1; ++j)
      for (uint32_t rp = R[j][i]; rp > 0; --rp)
        m[s.substr(i-rp-1, 2*rp+j)] = 1;
    m[string(1, s[i])] = 1;
  }

  //printing all distinct palindromes from hash map
  cout << "Below are " << m.size()-1 << " palindrome substrings";
  for (auto& i : m)
    cout << i.first << endl;
}

/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.
 */
bool isSentencePalindrome(const string& s) {
/*  for (int32_t i = 0, j = s.length()-1; i < j;) {
    if (isalnum(s[i]) && isalnum(s[j])) {
      if (tolower(s[i]) != tolower(s[j]))
        return false;
      ++i, --j;
    }
    if (i < j && !isalnum(s[i]))
      ++i;
    if (i < j && !isalnum(s[j]))
      --j;
  }

  return true;
}
*/
  const uint32_t len = s.length();
  if (!len) {
    return true;
  }

  function<bool(const char)> isValidChar = [](const char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
  };

  function<bool(char,char)> isSame = [](char s1, char s2) {
    if (s1 >= 'A' && s1 <= 'Z') {
      s1 = s1-'A'+'a';
    }
    if (s2 >= 'A' && s2 <= 'Z') {
      s2 = s2-'A'+'a';
    }
    return (s1 == s2);
  };

  uint32_t l = 0, r = len-1;
  while (l < r) {
    while (l < len && !isValidChar(s[l]))
      ++l;
    while (r > 0 && !isValidChar(s[r]))
      --r;

    if (l < r) {
      if (isSame(s[l], s[r])) {
        ++l;
        --r;
      } else
        return false;
    }
  }

  return true;
}

/*
Given a string S, you are allowed to convert it to a palindrome by adding 0 or more characters in front of it.
Find the length of the shortest palindrome that you can create from S by applying the above transformation.

Examples:
cca -> 1
aba -> 0
acb -> 2
abcb -> 3
abb -> 2
abcdefg -> 6
 */
int32_t shortestPrependingPalinLen(string& S) {
  const uint32_t len = S.length();
  if (!len)
    return -1;

  vector<uint32_t> p(2*len+1);
  S += '\0' + string(S.rbegin(), S.rend());

  p[0] = 0;
  for (uint32_t i = 1; i < 2*len+1; ++i) {
    uint32_t j = p[i-1];
    while (j > 0 && S[j] != S[i])
      j = p[j-1];

    if (S[i] == S[j])
      ++j;
    p[i] = j;
  }

  return len-p[2*len];
}

/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
 */
bool isIntPalindrome(int32_t x) {
  if (x < 0)
    return false;
  if (x < 10)
    return true;
  if (x%10 == 0 && x%10%10 == 0)
    return false;

  int32_t y = 0;
  while (x > y) {
    y = y*10 + x%10;
    x /= 10;
  }

  return (x == y || x == y/10);
}

bool isIntPalindrome2(int32_t x) {
  if (x < 0)
    return false;
  if (!x)
    return true;

  int32_t cp = x;
  function<bool(int32_t&)> solve = [&](int32_t& y) {
    x /= 10;
    bool ret = solve(y);

    if (ret && (cp%10 == y%10)) {
      y /= 10;
      return true;
    } else {
      return false;
    }
  };

  return solve(x);
}

bool isIntPalindrome3(const int32_t x) {
  if (x < 0)
    return false;

  int32_t a = x, b = 0;
  while (a > b) {
    b = b*10+a%10;
    a /= 10;
  }
  if (!a)
    return (x == b);
  return (a == b) || (a == b/10);
}

/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return
[
    ["aa","b"],
    ["a","a","b"]
]
 */
typedef vector<vector<string>> ResultT;
ResultT palinPartitions(const string& s) {
  const uint32_t len = s.length();
  if (len <= 1) { // special case for short strings
    return {{s}};
  }

  ResultT dp[len];
  dp[0] = {{s.substr(0,1)}}; //ResultT(1, vector<string>(1, s.substr(0, 1))); // start from first character, which is a palindrome

  for (uint32_t i = 1; i < len; ++i) {
    ResultT& res_ati = dp[i];

    // problem i is the case with the first i chars
    // dp(i) = sum(dp(j) + palidrome(s[j-i]))
    for (int32_t j = i; j >= 0; --j) {
      string j2i = s.substr(j, i-j+1);
      if (isPalindrome(j2i)) {
        if (!j) { // substr at i is palindrome
          vector<string> tmp(1, j2i);
          res_ati.push_back(tmp);
        } else {
          ResultT& prev_res = dp[j-1];
          for (uint32_t k = 0; k < prev_res.size(); ++k) { // append str_j2i to results of j-1
            vector<string> tmp = prev_res[k]; // copy
            tmp.push_back(j2i);
            res_ati.push_back(tmp);
          }
        }
      }
    }
  }

  return dp[len-1];
}

/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
 */
/*
uint32_t minCuts(const string& str) {
  const uint32_t len = str.length();
  if (len <= 1) { // special case for short strings
    return 0;
  }

  uint32_t dp[len+1];
  dp[0] = 0;
  for (uint32_t i = 1; i <= len; ++i)
    dp[i] = len-i; // (len-i) cuts at i, since single characters are palindrome

  bool ispalin_tbl[len][len];
  for (int32_t i = len-1; i >= 0; --i) {
    for (uint32_t j = i; j < len; ++j) {
      if (str[i] == str[j] && (j-i < 2 || ispalin_tbl[i+1][j-1])) {
        ispalin_tbl[i][j] = true;
        dp[i] = min(dp[i], dp[j+1]+1);
      }
    }
  }

  return dp[0]-1;
}
*/
void palinFlagTable(vector<vector<uint8_t> >& t, const string& s) {
  const uint32_t len = s.length(); // length is supposed to have been checked before calling this method
  t.resize(len);
  for (uint32_t i = 0; i < len; ++i)
    t[i] = vector<uint8_t>(len, 1);

  for (uint32_t i = 2; i <= len; ++i) {
    for (uint32_t j = 0, k = i-1; k < len; ++j, ++k) {
      t[j][k] = (t[j+1][k-1] && s[j] == s[k]);
    }
  }
}

uint32_t minCuts(const string& s) {
  const uint32_t len = s.length();
  if (len <= 1)
    return 0;

  vector<vector<uint8_t> > palin;
  palinFlagTable(palin, s);

  vector<int32_t> dp(len+1, numeric_limits<int32_t>::max());
  dp[0] = -1;

  for (uint32_t i = 0; i < len; ++i) {
    for (int32_t j = i; j >= 0; --j) {
      if (palin[j][i])
        dp[i+1] = min(dp[i+1], dp[j]+1);
    }
  }

  return (dp.back() == -1) ? 0 : dp.back();
}

/*
Each cow has an electronic ID tag that the system will read as the cows pass by a scanner. Each ID tag's contents are currently a single string with length M (1 <= M <= 2,000) characters drawn from an alphabet of N (1 <= N <= 26) different symbols (namely, the lower-case roman alphabet).
Cows, being the mischievous creatures they are, sometimes try to spoof the system by walking backwards. While a cow whose ID is "abcba" would read the same no matter which direction the she walks, a cow with the ID "abcb" can potentially register as two different IDs ("abcb" and "bcba").
FJ would like to change the cows's ID tags so they read the same no matter which direction the cow walks by. For example, "abcb" can be changed by adding "a" at the end to form "abcba" so that the ID is palindromic (reads the same forwards and backwards). Some other ways to change the ID to be palindromic are include adding the three letters "bcb" to the begining to yield the ID "bcbabcb" or removing the letter "a" to yield the ID "bcb". One can add or remove characters at any location in the string yielding a string longer or shorter than the original string.
Unfortunately as the ID tags are electronic, each character insertion or deletion has a cost (0 <= cost <= 10,000) which varies depending on exactly which character value to be added or deleted. Given the content of a cow's ID tag and the cost of inserting or deleting each of the alphabet's characters, find the minimum cost to change the ID tag so it satisfies FJ's requirements. An empty ID tag is considered to satisfy the requirements of reading the same forward and backward. Only letters with associated costs can be added to a string.
Input
Line 1: Two space-separated integers: N and M
Line 2: This line contains exactly M characters which constitute the initial ID string
Lines 3..N+2: Each line contains three space-separated entities: a character of the input alphabet and two integers which are respectively the cost of adding and deleting that character.
Output
Line 1: A single line with a single integer that is the minimum cost to change the given name tag.
Sample Input
3 4
abcb
a 1000 1100
b 350 700
c 200 800
Sample Output
900
Hint
If we insert an "a" on the end to get "abcba", the cost would be 1000. If we delete the "a" on the beginning to get "bcb", the cost would be 1100. If we insert "bcb" at the begining of the string, the cost would be 350+200+350=900, which is the minimum.
*/
const uint16_t MAX_M = 2001;
const uint8_t ALPHANO = 26;
uint32_t cost[ALPHANO];

uint32_t minCost(const string& tag, const uint32_t M) {
  uint32_t palin[2][MAX_M]; // palin[id][i]: id array represents current d characters min cost; !id array represents d-1 characters min cost, before calculation it represents d-2 characters min cost
  memset(palin[0], 0, sizeof(uint32_t)*(M+1)); // initialize
  memset(palin[1], 0, sizeof(uint32_t)*(M+1)); // initialize

  uint8_t idx = 0;
  for (uint32_t i = 2; i <= M; ++i) {
    idx = !idx;
    for (uint32_t j = 0, k = i-1; k < M; ++j, ++k) {
      if (tag[j] == tag[k]) {
        palin[idx][j] = palin[idx][j+1];
      } else {
        const uint32_t c1 = palin[!idx][j+1] + cost[tag[j]-'a'];
        const uint32_t c2 = palin[!idx][j] + cost[tag[k]-'a'];
        palin[idx][j] = min(c1, c2);
      }
    }
  }

  return palin[idx][0];
}

/*
We are given a string word. We will choose one of its anagrams uniformly at random. Return the probability that the chosen anagram will be a palindrome.

NOTES
-The returned value must have an absolute or a relative error of less than 1e-9.

CONSTRAINTS
-word will contain between 1 and 50 characters, inclusive.
-Each character of word will be a lowercase English letter ('a'-'z').

EXAMPLES
0)
"haha"
Returns: 0.3333333333333333

Each of the six anagrams of "haha" will be selected with probability 1/6.
Two of them are palindromes: "ahha" and "haah".
Hence, the probability of selecting a palindrome is 2/6.

1)
"xxxxy"
Returns: 0.2

2)
"xxxx"
Returns: 1.0

This word only has one anagram: "xxxx". That is a palindrome.

3)
"abcde"
Returns: 0.0

Regardless of how we rearrange the letters of "abcde", we will never get a palindrome.

4)
"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhff"
Returns: 0.025641025641025637
 */
double tbl[51];

double anagramIsPalinProbability(const string& w) {
  const uint32_t n = w.size();
  double numerator = tbl[n/2], denominator = tbl[n];
  uint32_t odd = 0;

  for (char ch = 'a'; ch <= 'z'; ch++) {
    uint32_t t = count(w.begin(), w.end(), ch);
    if (t%2 == 1)
      ++odd;

    numerator /= tbl[t/2];
    denominator /= tbl[t];
  }

  // if odd is bigger than one or even number, no palindrome
  if ((odd > 1) || (odd != n%2))
    return 0.0;

  return numerator/denominator;
}

/*
Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
 */
/*
uint32_t test2Sides(const string& s, int32_t low, uint32_t high) {
  const uint32_t n = s.length();
  uint32_t res = 0;

  if (low == high) {
    --low;
    ++high;
    res = 1;
  }

  while (low >= 0 && high < n && s[low] == s[high]) {
    res += 2;
    --low;
    ++high;
  }

  return res;
}

string longestPalinSubstr(const string& s) {
  uint32_t start = 0;
  uint32_t max_len = 1;

  for (uint32_t j = 1; j < s.length(); ++j) {
    uint32_t t = test2Sides(s, j, j);
    if (t > max_len) {
      start = j-t/2;
      max_len = t;
    }
    t = test2Sides(s, j-1, j);
    if (t > max_len) {
      start = j-t/2;
      max_len = t;
    }
  }

  return s.substr(start, max_len);
}
*/
string longestPalinSubstr_dp(string& s) { // O(n^2)
  const uint32_t n = s.length();
  uint32_t begin = 0;
  uint32_t max_len = 1;

  bool table[n][n];
  for (auto& i : table)
    for (auto& j : i)
      j = false;
  for (uint32_t i = 0; i < n; ++i)
    table[i][i] = true;

  for (uint32_t i = 0; i < n-1; ++i) {
    if (s[i] == s[i+1]) {
      table[i][i+1] = true;
      begin = i;
      max_len = 2;
    }
  }
  for (uint32_t len = 3; len <= n; ++len) {
    for (uint32_t i = 0; i < n-len+1; ++i) {
      uint32_t j = i+len-1;
      if (s[i] == s[j] && table[i+1][j-1]) {
        table[i][j] = true;
        begin = i;
        max_len = len;
      }
    }
  }

  return s.substr(begin, max_len);
}

string longestPalinSubstr_Manacher(const string& s) { // O(n)
  uint32_t len = s.length();
  if (!len)
    return "";

  len = 2*len+1; // position count
  uint32_t lps[len]; // LPS
  lps[0] = 0;
  lps[1] = 1;

  uint32_t C = 1; // center position
  uint32_t R = 2; // center right position
  uint32_t iMirror; // current left position
  uint32_t maxLPSLen = 0;
  uint32_t maxLPSCenterPos = 0;
  int32_t start = -1;
  int32_t diff = -1;

  for (uint32_t i = 2; i < len; ++i) {
   iMirror = 2*C-i; // get currentLeftPos iMirror for currentRightPosition i
   lps[i] = 0;
   diff = R-i;

   //If currentRightPosition i is within centerRightPosition R
   if (diff > 0)
     lps[i] = min(lps[iMirror], (uint32_t)diff);

   //Attempt to expand palindrome centered at currentRightPosition i. Here for
   //odd positions, we compare characters and if match then increment LPS
   //Length by ONE. If even position, we just increment LPS by ONE without any
   //character comparison.
   while (((i+lps[i]) < len && (i-lps[i]) > 0) &&
          (!((i+lps[i]+1)%2) || (s[(i+lps[i]+1)/2] == s[(i-lps[i]-1)/2]))) {
     ++lps[i];
   }

   if (lps[i] > maxLPSLen) {
     maxLPSLen = lps[i];
     maxLPSCenterPos = i;
   }

   // If palindrome centered at currentRightPosition i, expand beyond centerRightPosition R, adjust centerPosition C based on expanded palindrome.
   if (i+lps[i] > R) {
     C = i;
     R = i+lps[i];
   }
        //Uncomment it to print LPS Length array
        //printf("%d ", L[i]);
  }
    //printf("\n");

  start = (maxLPSCenterPos-maxLPSLen)/2;
  return s.substr(start, maxLPSLen);
//  cout << "LPS of string is " << text << " : ";
//  for (uint32_t i = start; i < start+maxLPSLen; ++i)
  //  cout << text[i];
 // cout << endl;
}

/*
Given a stream of characters (characters are received one by one), write a function that prints 'Yes' if a character makes the complete string palindrome, else prints 'No'.

1) The first character is always a palindrome, so print yes for first character.

2) Initialize reverse of first half as "a" and second half as "b". Let the hash value of first half reverse be 'firstr' and that of second half be 'second'.

3) Iterate through string starting from second character, do following for every character str[i], i.e., i varies from 1 to n-1.
     a) If 'firstr' and 'second' are same, then character by character check the substring ending with current character and print "Yes" if palindrome. Note that if hash values match, then strings need not be same. For example, hash values of "ab" and "ba" are same, but strings are different. That is why we check complete string after hash.
     b) Update 'firstr' and 'second' for next iteration. If 'i' is even, then add next character to the beginning of 'firstr' and end of second half and update hash values. If 'i' is odd, then keep 'firstr' as it is, remove leading character from second and append a next character at end.
 */
#define D 256 // D is the number of characters in input alphabet
#define Q 103 // Q is a prime number used for evaluating Rabin Karp's Rolling hash

void streamPalindrome(char s[]) {
  // Length of input string
  uint32_t N = strlen(s);

  // A single character is always a palindrome
  cout << s[0] << " Yes" << endl;

  // Return if string has only one character
  if (N == 1)
    return;

  // Initialize first half reverse and second half for as firstr and second characters
  uint32_t firstr = s[0] % Q;
  uint32_t second = s[1] % Q;
  uint32_t hash = 1;

  // Now check for palindromes from second character onward
  for (uint32_t i = 1; i < N; ++i) {
    // If the hash values of 'firstr' and 'second' match, then only check individual characters
    if (firstr == second) {
      uint32_t j = 0;
      for (; j < i/2; ++j) { /* Check if s[0...i] is palindrome using simple character by character match */
        if (s[j] != s[i-j])
          break;
      }

      cout << s[i] << (j == i/2 ? " Yes" : " No") << endl;
    } else
      cout << s[i] << " No" << endl;

    // Calculate hash values for next iteration. Don't calculate hash for next characters if this is the last character of string
    if (i != N-1) {
      if (!i%2) { // If i is even (next i is odd)
        hash = (hash*D)%Q; // Add next character after first half at beginning of 'firstr'
        firstr = (firstr+hash*s[i/2])%Q;

        // Add next character after second half at the end of second half.
        second = (second*D+s[i+1])%Q;
      } else { // If next i is odd (next i is even) then we need not to change firstr, we need to remove first character of second and append a character to it.
        second = (D*(second+Q-s[(i+1)/2]*hash)%Q + s[i+1])%Q;
      }
    }
  }
}

int main(int argc, char** argv) {
  string str = "A man, a plan, a canal: Panama";
  cout << "'" << str << "' is" << (isSentencePalindrome(str) ? " " : " not ") << "palindrome!" << endl;
  str = "race a car";
  cout << "'" << str << "' is" << (isSentencePalindrome(str) ? " " : " not ") << "palindrome!" << endl;

  int32_t n = 123321;
  cout << "Number " << n << " is" << (isIntPalindrome(n) ? " " : " not ") << "palindrome!" << endl;
 // cout << "'" << n << "' is" << (isIntPalindrome2(n) ? " " : " not ") << "palindrome!" << endl;
  cout << "Number " << n << " is" << (isIntPalindrome3(n) ? " " : " not ") << "palindrome!" << endl;
/*
  ListNodeT<char>* head = NULL;
  str = "abacaba";
  for (uint32_t i = 0; i != str.size(); ++i) {
    push<char>(&head, str[i]);
  }
  print(head);
  cout << "List " << (isListPalindrome_iter(head) ? "is palindrome!" : "is not palindrome!") << endl;
  cout << "List " << (isListPalindrome_recur(head) ? "is palindrome!" : "is not palindrome!") << endl;
*/
  str = "aab";
  vector<vector<string>> res = palinPartitions(str);

  cout << "Palindrome partitions:" << endl;
  for (auto& i : res) { //uint32_t i = 0; i < res.size(); ++i) {
    for (auto j : i) { //uint32_t j = 0; j < res[i].size(); ++j) {
      cout << j << ",";
    }
    cout << endl;
  }

 // cout << "Longest palindrome substring: " << longestPalinSubstr(str) << endl;
  cout << "Longest palindrome substring: " << longestPalinSubstr_dp(str) << endl;
  cout << "Longest palindrome substring: " << longestPalinSubstr_Manacher(str) << endl;

  uint32_t cuts = minCuts(str);
  cout << "Min cuts: " << cuts << endl;

  str = "abaaa";
  vector<string> res2 = distinctPalinSubstrs(str);
  for (auto& i : res2)
    cout << i << " ";
  cout << endl;

  tbl[0] = 1.0;
  for (uint8_t i = 1; i < 51; ++i)
    tbl[i] = i*tbl[i-1];
  str = "haha";
  cout << anagramIsPalinProbability(str) << endl;

  char tag[MAX_M]; // tag string
  uint32_t N, M, add_cost, del_cost;
  while (scanf("%d %d", &N, &M) != EOF) {
    getchar();
    gets(tag);
    fill(cost, cost+ALPHANO, 0);

    for (uint32_t i = 0; i < N; ++i) {
      char ch = getchar();
      scanf("%d %d", &add_cost, &del_cost);
      cost[ch-'a'] = min(add_cost, del_cost); // only records min cost
      getchar(); // take care of '\n'
    }

    cout << minCost(tag, M) << endl;
  }

  return 0;
}
