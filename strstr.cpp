#include <iostream>
#include <set>
#include <functional>
#include <algorithm>
#include <cstring> // for strlen

using namespace std;

/*
Implement strstr(). Returns a pointer to the first occurrence of needle in haystack,
or null if needle is not part of haystack.
 */
const char* strstr(const char* haystack, const char* needle) {
  if (!haystack || !needle)
    return nullptr;

  const uint32_t h_len = strlen(haystack);
  const uint32_t n_len = strlen(needle);
  if (!n_len)
    return haystack;
  if (!h_len)
    return nullptr;

  // stop the loop when the rest of the haystack is smaller than the needle
  const char* stop_test = haystack;
  const char* tmp = needle;
  while (*++tmp) {
    ++stop_test;
  }

  const char* tmph = haystack;
  const char* res = nullptr;

  while (*stop_test) {
    tmp = needle;

    // num of steps to advance
    uint32_t step = 1;
    if (*haystack == *tmp) {
      res = haystack;
      while (*tmp) {
        if (*tmp != *haystack)
          break;

        // no need to go back too far if cannot match the first letter
        if (*haystack != *needle)
          ++step;
        ++tmp;
        ++haystack;
      }
    }

    if (!*tmp)
      return res; // found it

    tmph += step;
    haystack = tmph;
    stop_test += step;
  }

  return nullptr;
}

/*
 Boyer-Moore
  */
const char* bm_strstr(const char* haysack, const char* needle) {
  const uint32_t n = strlen(needle);
  if (!n)
    return haysack;

  uint32_t len = strlen(haysack);
  int32_t tbl[256];
  for (auto& i : tbl)
    i = -1;
  for (uint32_t i = 0; i < n; ++i)
    tbl[needle[i]] = i;

  for (int32_t h_idx = n-1, n_idx = n-1; h_idx < len;) {
    for (; n_idx >= 0 && haysack[h_idx] == needle[n_idx]; --h_idx, --n_idx);
    if (n_idx < 0)
      return haysack+h_idx+1;

    char c = haysack[h_idx];
    if (tbl[c] < n_idx)
      h_idx += n-tbl[c]-1;
    else
      h_idx += n-n_idx;

    n_idx = n-1;
  }

  return nullptr;
}

#define MAX_CHARS 100000

const char* KMP(const char* haystack, const char* needle) {
  if (!haystack || !needle)
    return nullptr;

  const uint32_t h_len = strlen(haystack);
  const uint32_t n_len = strlen(needle);
  if (!n_len)
    return haystack;
  if (!h_len)
    return nullptr;

  int32_t pattern[MAX_CHARS];
  pattern[0] = -1;
  int32_t i = -1;

  for (uint32_t j = 1; j < n_len; ++j) {
    while (i > -1 && needle[i+1] != needle[j])
      i = pattern[i];

    if (needle[i+1] == needle[j])
      ++i;
    pattern[j] = i;
  }

  i = -1;
  for (uint32_t j = 0; j < h_len; ++j, ++haystack) {
    while (i > -1 && needle[i+1] != *haystack)
      i = pattern[i];

    if (needle[i+1] == *haystack)
      ++i;
    if (i == n_len-1)
      return haystack-i;
  }

  return nullptr;
}

template <uint128_t _needle_, uint32_t _needle_size_>
static inline const char* strstr(const char* buffer) {
#ifdef __SSE4_2__
  static_assert(_needle_size_ <= sizeof(__m128i), "Needle size is too big");
  static const uint128_t _value_ = _needle_;
  static const __m128i needle = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&_value_));
  for (__m128i haystack = _mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer));;) {
    int x = _mm_cmpistri(needle, haystack, _SIDD_SBYTE_OPS | _SIDD_CMP_EQUAL_ORDERED | _SIDD_LEAST_SIGNIFICANT);
    bool c = _mm_cmpistrc(needle, haystack,
      _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ORDERED | _SIDD_LEAST_SIGNIFICANT);
    bool z = _mm_cmpistrc(needle, haystack,
      _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ORDERED | _SIDD_LEAST_SIGNIFICANT);
    if (__PENG_LIKELY(c)) {
      __PENG_ASSERT(x != 16);
      if (__PENG_LIKELY(sizeof(__m128i) - _needle_size_ >= x)) {
        buffer += x;
        return buffer;
      } else {
        buffer += x;
        haystack = _mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer));
      }
    }
    if (__PENG_UNLIKELY(z)) {
      break;
    }
    buffer += sizeof(__m128i) - _needle_size_ + 1;
    haystack = _mm_loadu_si128(reinterpret_cast<const __m128i*>(buffer));
  }
  return NULL;
#else
#error "SSE4 is required"
  __PENG_ABORT("Not supported");
#endif
}

/*
int strstr_rollinghash(char* haystack, char* needle) {
  if (!needle || !*needle)
    return 0;
  if (!haystack || !*haystack)
    return -1;

  const uint32_t len0 = strlen(haystack), len1 = strlen(needle);
  auto calc_hash = [](char* s, const uint32_t len) {
    uint64_t base = 1, res = 0;
    for (uint32_t i = 0; i < len; ++i) {
      res += (s[i]-'a'+1) * base;
      base *= 29;
    }
    return res;
  };

  uint64_t hash0 = calc_hash(haystack, len1), hash1 = calc_hash(needle, len1);
  uint64_t base = pow(29, len1-1);

  for (uint32_t i = len1; i <= len0; ++i) {
    if (hash0 == hash1)
      return i-len1;

    hash0 = hash0/29 + (haystack[i]-'a'+1)*base;
  }

  return -1;
}
*/

/*
A permutation, also called an arrangement number or order,
is a rearrangement of the elements of an ordered list S into a one-to-one correspondence with S itself.
A string of length n has n! permutations.
 */
set<string> permutations_recur(const string& s) {
  if (s.length() <= 1)
    return {s};

  set<string> ret;

  function<void(const string&,const string&)> solve = // DFS
    [&](const string& prefix, const string& curr_s) {
    const uint32_t len = curr_s.length();
    if (!len) {
      ret.insert(prefix);
      return;
    }

    for (uint32_t i = 0; i < len; ++i) {
      char c = curr_s[i];
      string left = curr_s.substr(0, i);
      string right = curr_s.substr(i+1, len-i-1);
      solve(prefix+c, left+right);
    }
  };

  solve("", s);
  return ret;
}

/*
Given a string of length n, print all permutation of the given string.
Repetition of characters is allowed. Print these permutations in lexicographically sorted order.
 */
vector<string> lexicographicPermu(string s) {
  const uint32_t len = s.length();
  if (!len)
    return {};

  // Sort the input string so that we get all output strings in lexicographically sorted order
  sort(s.begin(), s.end());

  // Create a temp array that will be used by allLexicographicRecur()
  char mem[len+1];
  mem[len] = '\0';
  vector<string> ret;

  function<void(const uint32_t)> solve =
    [&](const uint32_t index) {
    if (index == len) {
      ret.push_back(mem);
      return;
    }

    // One by one fix all characters at the given index and recur for the subsequent indexes
    for (uint32_t i = 0; i < len; ++i) {
      // Fix the ith character at index and if this is not the last index then recursively call for higher indexes
      mem[index] = s[i];
      solve(index+1);
    }
  };

  solve(0);
  return ret;
}

/*
Implement function strstrp(string a, string b) returns index where any permutation of b is a substring of a.
e.g.
strstrp("hello", "ell") returns 0
strstrp("hello", "lle") returns 1
strstrp("hello", "wor") returns -1
 */
int32_t strstrp(const string& a, const string& b) {
  const uint32_t a_len = a.length(), b_len = b.length();
  if (!a_len || !b_len)
    return -1;

  int32_t max_idx = -1;

  for (uint32_t i = 0; i < b_len; ++i) {
    string substr = b.substr(0, i+1);
    set<string> permus = permutations_recur(substr);

    bool allSub = true;

    for (auto& s : permus) {
      const char* p = KMP(a.c_str(), s.c_str());
      if (!p) {
        allSub = false;
        break;
      }
    }

    if (allSub) {
      max_idx = max(max_idx, (int32_t)i);
    }
  }

  return max_idx;
}

int main(int argc, char** argv) {
  string haystack = "kasfmcvowerllvplkejr1234098mvzp[qptlmfadf";
  string needle = "ad";
  cout << KMP(haystack.c_str(), needle.c_str()) << endl;
  cout << strstr(haystack.c_str(), needle.c_str()) << endl;
  cout << bm_strstr(haystack.c_str(), needle.c_str()) << endl;

  set<string> res = permutations_recur("ell");
  for (auto& i : res)
    cout << i << " ";
  cout << endl;
/*
  res = permutations_recur1("ell");
  for (auto& i : res)
    cout << i << " ";
  cout << endl;
*/
  string s = "ABC";
  vector<string> res2 = lexicographicPermu(s);
  for (auto& i : res2)
    cout << i << " ";
  cout << endl;

  cout << "strstrp: " << strstrp("hello", "ell") << endl;
  cout << "strstrp: " << strstrp("hello", "lle") << endl;
  cout << "strstrp: " << strstrp("hello", "wor") << endl;
  return 0;
}
