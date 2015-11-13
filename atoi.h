#ifndef _ATOI_H_
#define _ATOI_H_

#include <limits>
#include <ctype.h>

using namespace std;

static const int32_t MAX_LMT = numeric_limits<int32_t>::max();
static const int32_t MIN_LMT = numeric_limits<int32_t>::min();

int64_t atoi(const char* s) {
  // skip the leading spaces
  while (*s == ' ') {
    ++s;
  }

  int8_t sign = 1;
  if (*s == '+') {
    ++s;
  else if (*s == '-') {
    sign = -1;
    ++s;
  }

  int64_t ret = 0;

  while (*s) {
    char c = *s;

    // only the first occurence of sign, before any digits, is legal
    if (!isdigit(c)) {
      return sign*ret;
    } else if (c-'0' >= 0 && c-'9' <= 0) {
      ret *= 10;
      ret += (c-'0');
      // detect overflow by "cheating" using long long
      if (ret*sign > MAX_LMT || ret*sign < MIN_LMT)
        return (sign == 1) ? MAX_LMT : MIN_LMT;
    }

    ++s;
  }

  ret *= sign;
  return ret;
}

template <typename CharT, typename IntegerT, uint32_t _size_>
struct AccumulateFastAtoi {
  __PENG_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return static_cast<IntegerT>(buffer[0]) * meta::pow<10,_size_-1>::value +
      AccumulateFastAtoi<CharT,IntegerT,_size_-1>::accumulate(buffer+1);
  }
};

template <typename CharT, typename IntegerT>
struct AccumulateFastAtoi<CharT,IntegerT,1> {
  __PENG_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return buffer[0];
  }
};

template <typename CharT, typename IntegerT>
struct AccumulateFastAtoi<CharT,IntegerT,0> {
  __PENG_NOCALL static IntegerT accumulate(const CharT* buffer) {
    return 0;
  }
};

template <typename CharT, uint32_t _size_, bool _load_align_ = false>
struct FastAtoi {
  template <typename IntegerT>
  __PENG_NOCALL static void parse(IntegerT& dest, CharT* const src) {
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    static_assert(_size_ <= 20, "Integer is too big");
    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);
    static_assert(_size_ <= _digits_per_xmm_, "Too many digits, max is 16 for char");
#ifdef __PENG_ASSERT_TYPE
    for (uint32_t i = 0; i < _size_; i++) {
      __PENG_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif
    if (_size_ == 1) {
      dest = src[0] & 0xf;
    } else if (_size_ == 2) {
      dest = (src[0] & 0xf) * 10 + (src[1] & 0xf);
    } else if (_size_ <= 4) {
      if (_size_ * sizeof(CharT) <= 4) {
        uint32_t x = *reinterpret_cast<const uint32_t*>(src);
        static const uint32_t _filter_ = 0x0f0f0f0f;
        x &= _filter_;
        dest = AccumulateFastAtoi<CharT,IntegerT,_size_>::accumulate(reinterpret_cast<const CharT*>(&x));
      } else {
        if (_size_ == 2) {
          dest = (src[0] & 0xf) * 10 + (src[1] & 0xf);
        } else if (_size_ == 3) {
          dest = (src[0] & 0xf) * 100 + (src[1] & 0xf) * 10 + (src[2] & 0xf);
        } else if (_size_ == 4) {
          dest = (src[0] & 0xf) * 1000 + (src[1] & 0xf) * 100 + (src[2] & 0xf) * 10 +
            (src[3] & 0xf);
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
      dest = AccumulateFastAtoi<CharT,IntegerT,_size_>::accumulate(reinterpret_cast<const CharT*>(&x));
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
      dest = AccumulateFastAtoi<CharT,IntegerT,_size_>::accumulate(reinterpret_cast<const CharT*>(&x));
    }
  }
};

template <typename CharT, bool _load_align_ = false>
struct DynamicFastAtoi {
  template <typename IntegerT>
  __PENG_NOCALL static void parse(IntegerT& dest, CharT* const src, uint32_t size) {
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    __PENG_ASSERT(size <= 20);
#ifdef __PENG_ASSERT_TYPE
    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);
    __PENG_ASSERT(size <= _digits_per_xmm_);
    for (uint32_t i = 0; i < size; i++) {
      __PENG_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif
    if (__PENG_LIKELY(size <= sizeof(uint32_t) / sizeof(CharT))) {
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
      __PENG_ASSERT(size < 127);

      uint32_t i = 0;
      switch (static_cast<uint32_t>(size)) {
      case 4:
        accum += static_cast<IntegerT>(arr[i]);
        accum *= 10;
        i++;
      case 3:
        accum += static_cast<IntegerT>(arr[i]);
        accum *= 10;
        i++;
      case 2:
        accum += static_cast<IntegerT>(arr[i]);
        accum *= 10;
        i++;
      case 1:
        accum += static_cast<IntegerT>(arr[i]);
      default:
        break;
      }
      dest = accum;
      /*
      } else if (size <= sizeof(uint64_t) / sizeof(CharT)) {
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
      const CharT* arr = reinterpret_cast<const CharT*>(&x);
      IntegerT accum = 0;
      __PENG_ASSERT(size < 127);
      if (sizeof(CharT) > 2) {
      uint32_t i = 0;
      switch (size) {
      case 2:
      accum += static_cast<IntegerT>(arr[i]);
      accum *= 10;
      i++;
      case 1:
      accum += static_cast<IntegerT>(arr[i]);
      default:
      break;
      }
      } else {
      int32_t i = 0;
      if (sizeof(CharT) > 1) {
      switch (static_cast<int32_t>(size - i)) {
      case 4:
      accum += static_cast<IntegerT>(arr[i]);
      accum *= 10;
      i++;
      case 3:
      accum += static_cast<IntegerT>(arr[i]);
      accum *= 10;
      i++;
      case 2:
      accum += static_cast<IntegerT>(arr[i]);
      accum *= 10;
      i++;
      case 1:
      accum += static_cast<IntegerT>(arr[i]);
      default:
      break;
      }
      } else {
      __PENG_ASSERT(size >= 4);
      accum += static_cast<IntegerT>(arr[i]) * 1000;
      accum += static_cast<IntegerT>(arr[i + 1]) * 100;
      accum += static_cast<IntegerT>(arr[i + 2]) * 10;
      accum += static_cast<IntegerT>(arr[i + 3]);
      i += 4;
      switch (static_cast<int32_t>(size - i)) {
      case 4:
      accum *= 10;
      accum += static_cast<IntegerT>(arr[i]);
      i++;
      case 3:
      accum *= 10;
      accum += static_cast<IntegerT>(arr[i]);
      i++;
      case 2:
      accum *= 10;
      accum += static_cast<IntegerT>(arr[i]);
      i++;
      case 1:
      accum *= 10;
      accum += static_cast<IntegerT>(arr[i]);
      default:
      break;
      }
      }
      }
      dest = accum;
      */
    } else {
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
      __PENG_ASSERT(size < 127);

      // Unroll 4x
      int32_t i = 0;
      for (; i <= static_cast<int32_t>(size)-4; i += 4) {
        accum *= 10000;
        accum += static_cast<IntegerT>(arr[i]) * 1000;
        accum += static_cast<IntegerT>(arr[i+1]) * 100;
        accum += static_cast<IntegerT>(arr[i+2]) * 10;
        accum += static_cast<IntegerT>(arr[i+3]);
      }
      switch (static_cast<int32_t>(size-i)) {
      case 3:
        accum *= 10;
        accum += static_cast<IntegerT>(arr[i]);
        i++;
      case 2:
        accum *= 10;
        accum += static_cast<IntegerT>(arr[i]);
        i++;
      case 1:
        accum *= 10;
        accum += static_cast<IntegerT>(arr[i]);
      default:
        break;
      }
      dest = accum;
    }
  }
};

#endif // _ATOI_H_
