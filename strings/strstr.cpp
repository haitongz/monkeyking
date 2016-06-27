#include <iostream>
//#include <set>
#include <vector>
#include <functional>
#include <cstring> // for strlen

using namespace std;

/*
Implement strstr(): return index of the first occurrence of needle in haystack,
or null if needle is not part of haystack.
 */
int strstr_bf(const char* haystack, const char* needle) {
  if (!needle || !haystack) {
    return -1;
  } else if (!*needle) {
    return 0;
  }

  uint hLen = strlen(haystack);
  uint nLen = strlen(needle);

  for (uint i = 0; i < hLen-nLen+1; ++i) {
    for (uint j = 0; j < nLen+1; ++j) {
      auto p1 = haystack+i+j;
      auto p2 = needle+j;
      if (!*p2) {
	return i;
      }
      if (*p1 != *p2) {
	break;
      }
    }
  }

  return -1;
}

int strstr_kmp(const char* haystack, const char* needle) {
  if (!needle || !haystack) {
    return -1;
  } else if (!*needle) {
    return 0;
  }

  uint hLen = strlen(haystack);
  uint nLen = strlen(needle);
  vector<int> match(nLen, -1);

  function<void()> preprocess = [&]() {
    int i = -1;

    for (uint j = 1; j < nLen; ++j) {
      while (i >= 0 && needle[j] != needle[i+1]) {
	i = match[i];
      }

      if (needle[j] == needle[i+1]) {
	++i;
      }

      match[j] = i;
    }
  };

  preprocess();

  int i = -1;
  for (uint j = 0; j < hLen; ++j) {
    while (i >= 0 && haystack[j] != needle[i+1]) {
      i = match[i];
    }

    if (haystack[j] == needle[i+1]) {
      ++i;
    }

    if (i == nLen-1) {
      return (j-nLen+1);
    }
  }

  return -1;
}

/*
template <uint128_t _needle_, uint _needle_size_>
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

// Boyer-Moore
const char* bm_strstr(const char* haysack, const char* needle) {
  const uint n = strlen(needle);
  if (!n)
    return haysack;

  uint len = strlen(haysack);
  int tbl[256];
  for (auto& i : tbl)
    i = -1;
  for (uint i = 0; i < n; ++i)
    tbl[needle[i]] = i;

  for (int hIdx = n-1, nIdx = n-1; hIdx < len;) {
    for (; nIdx >= 0 && haysack[hIdx] == needle[nIdx]; --hIdx, --nIdx);
    if (nIdx < 0)
      return haysack+hIdx+1;

    char c = haysack[hIdx];
    if (tbl[c] < nIdx)
      hIdx += n-tbl[c]-1;
    else
      hIdx += n-nIdx;

    nIdx = n-1;
  }

  return nullptr;
}

int strstr_rollinghash(char* haystack, char* needle) {
  if (!needle || !*needle)
    return 0;
  if (!haystack || !*haystack)
    return -1;

  const uint len0 = strlen(haystack), len1 = strlen(needle);
  auto calc_hash = [](char* s, const uint len) {
    uint64_t base = 1, res = 0;
    for (uint i = 0; i < len; ++i) {
      res += (s[i]-'a'+1) * base;
      base *= 29;
    }
    return res;
  };

  uint64_t hash0 = calc_hash(haystack, len1), hash1 = calc_hash(needle, len1);
  uint64_t base = pow(29, len1-1);

  for (uint i = len1; i <= len0; ++i) {
    if (hash0 == hash1)
      return i-len1;

    hash0 = hash0/29 + (haystack[i]-'a'+1)*base;
  }

  return -1;
}
 */

int main(int argc, char** argv) {
  string haystack = "kasfmcvowerllvplkejr1234098mvzp[qptlmfadf";
  string needle = "ad";
  cout << string(haystack.c_str() + strstr_bf(haystack.c_str(), needle.c_str())) << endl;
  cout << string(haystack.c_str() + strstr_kmp(haystack.c_str(), needle.c_str())) << endl;
  return 0;
}
