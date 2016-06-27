#pragma once

#include <limits>
#include <ctype.h>

using namespace std;

namespace {
  const int SIGNED_MAX = numeric_limits<int>::has_infinity ?
                         numeric_limits<int>::infinity() : numeric_limits<int>::max();

  const int SIGNED_MIN = numeric_limits<int>::has_infinity ?
                         -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();
}

/*
Implement function atoi to convert a string to an integer.

If no valid conversion could be performed, a zero value is returned.

If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */
int myatoi(const char* s) {
  if (!s || !strlen(s)) {
    throw exception();
  }

  // skip the leading spaces
  while (*s == ' ') {
    ++s;
  }

  int sign = 1;
  if (*s == '+') {
    ++s;
  } else if (*s == '-') {
    sign = -1;
    ++s;
  }

  long long ret = 0;

  while (*s) {
    char c = *s;
    if (!isdigit(c)) { // only the first occurence of sign, before any digits, is legal
      return ret; //throw exception();
    } else if (c-'0' >= 0 && c-'9' <= 0) {
      // detect overflow by "cheating" using long long
      if (ret*sign >= SIGNED_MAX) {
        return SIGNED_MAX;
      } else if (ret*sign <= SIGNED_MIN) {
        return SIGNED_MIN;
      } else {
        ret *= 10;
        ret += (c-'0');
      }
    }

    ++s;
  }

  ret *= sign;
  return (int)ret;
}

int myatoi2(char* s) { //, int n = 0) {
  if (!s) {
    return SIGNED_MIN;
  }

  while (isspace(*s)) {
    ++s;
  }

  int sign = (*s == '+' || *s == '-') ? ((*s++ == '+') ? 1 : -1) : 1;

  uint ret = 0;
  while (*s && isdigit(*s)) {
    ret = ret<<1 + ret<<3 + (*s++ - '0');
  }

  return sign*ret;
}

template <typename CharT, typename IntegerT, uint32_t _size_>
struct AccumulateFastAtoi {
  __DVDT_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return static_cast<IntegerT>(buffer[0])*meta::pow<10,_size_-1>::value +
                                 AccumulateFastAtoi<CharT,IntegerT,_size_-1>::accumulate(buffer+1);
  }
};

template <typename CharT, typename IntegerT>
struct AccumulateFastAtoi<CharT,IntegerT,1> {
  __DVDT_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return buffer[0];
  }
};

template <typename CharT, typename IntegerT>
struct AccumulateFastAtoi<CharT,IntegerT,0> {
  __DVDT_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return 0;
  }
};

template <typename CharT, uint32_t _size_, bool _load_align_ = false>
struct FastAtoi {
  template <typename IntegerT>
  __DVDT_NOCALL static void parse(IntegerT& dest, CharT* const src) {
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    static_assert(_size_ <= 20, "Integer is too big");
    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);
    static_assert(_size_ <= _digits_per_xmm_ * 2, "Too many digits, max is 32 for char");
#ifdef __DVDT_ASSERT_TYPE
    for (uint32_t i = 0; i < _size_; i++) {
      if (src[i] != ' ' && !(src[i] >= '0' && src[i] <= '9')) {
        std::cerr << "Bad number: " << std::string(src, _size_) << std::endl;
      }
      __DVDT_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif
    if (_size_ == 0) {
      dest = 0;
      __DVDT_ABORT("Bad FastAtoi");
    } else if (_size_ == 1) {
      dest = src[0] & 0xf;
    } else if (_size_ == 2) {
      dest = (src[0] & 0xf) * 10 + (src[1] & 0xf);
    } else if (_size_ <= 4) {
      if (_size_ * sizeof(CharT) <= 4) {
        uint32_t x = *reinterpret_cast<const uint32_t*>(src);
        static const uint32_t _filter_ = 0x0f0f0f0f;
        x &= _filter_;
        dest = AccumulateFastAtoi<CharT, IntegerT, _size_>::accumulate(reinterpret_cast<const CharT*>(&x));
      } else {
        if (_size_ == 2) {
          dest = (src[0] & 0xf) * 10 + (src[1] & 0xf);
        } else if (_size_ == 3) {
          dest = (src[0] & 0xf) * 100 + (src[1] & 0xf) * 10 + (src[2] & 0xf);
        } else if (_size_ == 4) {
          dest = (src[0] & 0xf) * 1000 + (src[1] & 0xf) * 100 + (src[2] & 0xf) * 10 + (src[3] & 0xf);
        }
      }
    } else if (_size_ * sizeof(CharT) <= 8) {
      uint64_t x = *reinterpret_cast<const uint64_t*>(src);
      if (sizeof(CharT) == 1) {
        static const uint64_t _filter_ = 0x0f0f0f0f0f0f0f0f;
        x &= _filter_;
      } else if (sizeof(CharT) == 2) {
        static const uint64_t _filter_ = 0x000f000f000f000f;
        x &= _filter_;
      } else if (sizeof(CharT) == 4) {
        static const uint64_t _filter_ = 0x0000000f0000000f;
        x &= _filter_;
      }

      dest = AccumulateFastAtoi<CharT, IntegerT, _size_>::accumulate(reinterpret_cast<const CharT*>(&x));
    } else if (_size_ * sizeof(CharT) <= 16) {
      __m128i x;
      if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else {
        x = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src));
      }
      if (sizeof(CharT) == 1) {
        static const __m128i _filter_ = _mm_set1_epi8(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 2) {
        static const __m128i _filter_ = _mm_set1_epi16(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 4) {
        static const __m128i _filter_ = _mm_set1_epi32(0xf);
        x = _mm_and_si128(x, _filter_);
      }

      dest = AccumulateFastAtoi<CharT, IntegerT, _size_>::accumulate(reinterpret_cast<const CharT*>(&x));
    } else {
      IntegerT x;
      FastAtoi<CharT,meta::max<int32_t,_size_-16,0>::value, _load_align_>::parse(x, src);
      IntegerT y;
      FastAtoi<CharT,16,_load_align_>::parse(y, src + meta::max<int32_t, _size_ - 16, 0>::value);
      dest = x * static_cast<IntegerT>(1e16) + y;
    }
  }
};

template <typename CharT, bool _load_align_ = false>
struct DynamicFastAtoi {
  template <typename IntegerT>
  __DVDT_NOCALL static void parse(IntegerT& dest, CharT* const src, uint32_t size) {
    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    __DVDT_ASSERT(size <= 20);
#ifdef __DVDT_ASSERT_TYPE
    for (uint32_t i = 0; i < size; i++) {
      __DVDT_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif
    if (__DVDT_LIKELY(size <= sizeof(uint32_t) / sizeof(CharT))) {
      uint32_t x = *reinterpret_cast<const uint32_t*>(src);
      if (sizeof(CharT) == 1) {
        static const uint32_t _filter_ = 0x0f0f0f0f;
        x &= _filter_;
      } else if (sizeof(CharT) == 2) {
        static const uint32_t _filter_ = 0x000f000f;
        x &= _filter_;
      } else if (sizeof(CharT) == 4) {
        static const uint32_t _filter_ = 0x0000000f;
        x &= _filter_;
      }
      const CharT* arr = reinterpret_cast<const CharT*>(&x);
      IntegerT accum = 0;
      __DVDT_ASSERT(size < 127);
      switch (static_cast<uint32_t>(size)) {
        case 4:
          accum += static_cast<IntegerT>(*arr);
          accum *= 10;
          arr++;
        case 3:
          accum += static_cast<IntegerT>(*arr);
          accum *= 10;
          arr++;
        case 2:
          accum += static_cast<IntegerT>(*arr);
          accum *= 10;
          arr++;
        case 1:
          accum += static_cast<IntegerT>(*arr);
        default:
          break;
      }
      dest = accum;
    } else if (size <= _digits_per_xmm_) {
      __m128i x;
      if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else {
        x = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src));
      }
      if (sizeof(CharT) == 1) {
        static const __m128i _filter_ = _mm_set1_epi8(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 2) {
        static const __m128i _filter_ = _mm_set1_epi16(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 4) {
        static const __m128i _filter_ = _mm_set1_epi32(0xf);
        x = _mm_and_si128(x, _filter_);
      }
      const CharT* arr = reinterpret_cast<const CharT*>(&x);
      IntegerT accum = 0;
      __DVDT_ASSERT(size < 127);
      const CharT* arrEnd = arr + size - 4;
      uint32_t remain = size & 3;
                              // Unroll 4x
      for (; arr <= arrEnd ; arr += 4) {
        accum *= 10000;
        accum += static_cast<IntegerT>(arr[0]) * 1000;
        accum += static_cast<IntegerT>(arr[1]) * 100;
        accum += static_cast<IntegerT>(arr[2]) * 10;
        accum += static_cast<IntegerT>(arr[3]);
      }
      switch (remain) {
        case 3:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr);
          arr++;
        case 2:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr);
          arr++;
        case 1:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr);
        default:
          break;
      }
      dest = accum;
    } else if (size <= 20 / sizeof(CharT)) {
      __m128i x;
      if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else {
        x = _mm_loadu_si128(reinterpret_cast<const __m128i*>(src));
      }
      if (sizeof(CharT) == 1) {
        static const __m128i _filter_ = _mm_set1_epi8(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 2) {
        static const __m128i _filter_ = _mm_set1_epi16(0xf);
        x = _mm_and_si128(x, _filter_);
      } else if (sizeof(CharT) == 4) {
        static const __m128i _filter_ = _mm_set1_epi32(0xf);
        x = _mm_and_si128(x, _filter_);
      }
      const CharT* arr = reinterpret_cast<const CharT*>(&x);
      IntegerT accum = 0;
      __DVDT_ASSERT(size < 127);
      const CharT* arrEnd = arr + (16 / sizeof(CharT));
      for (; arr < arrEnd ; arr += 4) { // Unroll 4x
        accum *= 10000;
        accum += static_cast<IntegerT>(arr[0]) * 1000;
        accum += static_cast<IntegerT>(arr[1]) * 100;
        accum += static_cast<IntegerT>(arr[2]) * 10;
        accum += static_cast<IntegerT>(arr[3]);
      }
      uint32_t x2 = *reinterpret_cast<const uint32_t*>(src + (16 / sizeof(CharT)));
      if (sizeof(CharT) == 1) {
        static const uint32_t _filter_ = 0x0f0f0f0f;
        x2 &= _filter_;
      } else if (sizeof(CharT) == 2) {
        static const uint32_t _filter_ = 0x000f000f;
        x2 &= _filter_;
      } else if (sizeof(CharT) == 4) {
        static const uint32_t _filter_ = 0x0000000f;
        x2 &= _filter_;
      }
      const CharT* arr2 = reinterpret_cast<const CharT*>(&x2);
      switch (static_cast<uint32_t>(size - 16)) {
        case 4:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 3:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 2:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 1:
          accum *= 10;
          accum += static_cast<IntegerT>(*arr2);
        default:
          break;
      }
      dest = accum;
    } else {
      __DVDT_ABORT("Too many characters");
      dest = 0;
    }
  }
};
