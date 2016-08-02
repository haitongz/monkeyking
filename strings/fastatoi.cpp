#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

#ifdef __SSE4_1__
  #include <smmintrin.h>
#endif

#ifdef __SSE4_2__
  #include <nmmintrin.h>
#else
 #include <string.h>
#endif

#define __DVDT_LIKELY(x) __builtin_expect((x), 1)
#define __DVDT_UNLIKELY(x) __builtin_expect((x), 0)
#define __DVDT_NOCALL __attribute__((always_inline,flatten))

#undef __DVDT_ASSERT
#undef __DVDT_MSG_ASSERT

#ifdef __DVDT_ASSERT_TYPE
# define __DVDT_MSG_ASSERT(x, y) do {                                   \
    if(__DVDT_UNLIKELY(!static_cast<bool>(x))) {                        \
      if (assert_on_flag) {                                             \
        __DVDT_NS::common::Assert::die(#x, y, __FILE__, __LINE__, __FUNCTION__); \
      } else                                                            \
        fprintf(stderr, "Assertion failed, ignored: %s %s %s %d %s\n", #x, y, __FILE__, __LINE__, __FUNCTION__); \
    } } while (0)
# define __DVDT_ASSERT(x) do {                                          \
    if(__DVDT_UNLIKELY(!static_cast<bool>(x))) {                        \
      if (assert_on_flag) {                                             \
        __DVDT_NS::common::Assert::die(#x, __FILE__, __LINE__, __FUNCTION__); \
      } else                                                            \
        fprintf(stderr, "Assertion failed, ignored: %s %s %d %s\n", #x, __FILE__, __LINE__, __FUNCTION__); \
   } } while (0)
# else
# define __DVDT_MSG_ASSERT(x, y)
# define __DVDT_ASSERT(x)
# endif

using namespace std;

#if 0
struct Impl {
  typedef const char CharT;

  template <typename IntegerT>
  __DVDT_NOCALL static void convert(IntegerT& dest, CharT* const src, uint32_t size) {
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    __DVDT_ASSERT(size <= 20);
#ifdef __DVDT_ASSERT_TYPE
    for (uint32_t i = 0; i < size; i++) {
      __DVDT_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif

    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);

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
  /*    if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else */ {
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
      for (; arr <= arrEnd ; arr += 4) { // Unroll 4x
        IntegerT t = accum;
        accum = t<<13 + t<<10 + t<<9 + t<<8 + t<<4; // *10000;
        t = static_cast<IntegerT>(arr[0]);
        accum += t*1000; //t<<9 + t<<8 + t<<7 + t<<6 + t<<5 + t<<3; // *1000
      /*  t = static_cast<IntegerT>(arr[1]);
        accum += t<<6 + t<<5 + t<<2; // *100
        t = static_cast<IntegerT>(arr[2]);
        accum += t<<3 + t<<1; // *10
        accum += static_cast<IntegerT>(arr[3]);

        accum *= 10000;
        accum += static_cast<IntegerT>(arr[0]) * 1000; */
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
      /*if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else */{
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
      exit(1); //__DVDT_ABORT("Too many characters");
      dest = 0;
    }
  }
};

#endif

struct Impl {
  typedef const char CharT;

  template <typename IntegerT>
  __DVDT_NOCALL static void convert(IntegerT& ret, CharT* const src, uint32_t size) {
    static_assert(sizeof(CharT) <= 4, "Unsupported char type");
    __DVDT_ASSERT(size <= 20);
#ifdef __DVDT_ASSERT_TYPE
    for (uint32_t i = 0; i < size; i++) {
      __DVDT_ASSERT(src[i] == ' ' || (src[i] >= '0' && src[i] <= '9'));
    }
#endif

    static const uint32_t _digits_per_xmm_ = sizeof(__m128i) / sizeof(CharT);

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
          accum = (accum<<1) + (accum<<3);
          arr++;
        case 3:
          accum += static_cast<IntegerT>(*arr);
          accum = (accum<<1) + (accum<<3);
          arr++;
        case 2:
          accum += static_cast<IntegerT>(*arr);
          accum = (accum<<1) + (accum<<3);
          arr++;
        case 1:
          accum += static_cast<IntegerT>(*arr);
        default:
          break;
      }
      ret = accum;
    } else if (size <= _digits_per_xmm_) {
      __m128i x;
 /*     if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else */ {
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
      for (; arr <= arrEnd; arr += 4) { // Unroll 4x
        IntegerT t = accum;
        accum = (t<<13) + (t<<10) + (t<<9) + (t<<8) + (t<<4); // *10000;
        t = static_cast<IntegerT>(arr[0]);
        accum += (t<<9) + (t<<8) + (t<<7) + (t<<6) + (t<<5) + (t<<3); // *1000
        t = static_cast<IntegerT>(arr[1]);
        accum += (t<<6) + (t<<5) + (t<<2); // *100
        t = static_cast<IntegerT>(arr[2]);
        accum += (t<<3) + (t<<1); // *10
        accum += static_cast<IntegerT>(arr[3]);
      }
      switch (remain) {
        case 3:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr);
          arr++;
        case 2:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr);
          arr++;
        case 1:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr);
        default:
          break;
      }
      ret = accum;
    } else if (size <= 20 / sizeof(CharT)) {
      __m128i x;
     /* if (_load_align_) {
        x = _mm_load_si128(reinterpret_cast<const __m128i*>(src));
      } else */ {
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
        IntegerT t = accum;
        accum = (t<<13) + (t<<10) + (t<<9) + (t<<8) + (t<<4); // *10000;
        t = static_cast<IntegerT>(arr[0]);
        accum += (t<<9) + (t<<8) + (t<<7) + (t<<6) + (t<<5) + (t<<3); // *1000
        t = static_cast<IntegerT>(arr[1]);
        accum += (t<<6) + (t<<5) + (t<<2); // *100
        t = static_cast<IntegerT>(arr[2]);
        accum += (t<<3) + (t<<1); // *10
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
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 3:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 2:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr2);
          arr2++;
        case 1:
          accum = (accum<<1) + (accum<<3);
          accum += static_cast<IntegerT>(*arr2);
        default:
          break;
      }
      ret = accum;
    } else {
      // __DVDT_ABORT("Too many characters");
      exit(1);
      ret = 0;
    }
  }
};

// template <typename CharT>
struct FastAtoi { // use a class here so that convert can always be inlined. otherwise static method gives you a warning that it might not always inline...
  template <typename IntegerT>
  __DVDT_NOCALL static IntegerT atoi(const char* const src, uint8_t size) {
    IntegerT ret;

    if (std::is_unsigned<IntegerT>::value) {
      Impl::convert<IntegerT>(ret, src, size);
    } else {
      if (src[0] == '-') {
        Impl::convert<IntegerT>(ret, src+1, size-1);
        ret = -ret;
      } else {
        Impl::convert<IntegerT>(ret, src, size);
      }
    }

    return ret;
  }
};

struct rdtscp_t {
  uint32_t m_cpuid;
  uint64_t m_cycles;
};

inline static rdtscp_t rdtscp() {
  rdtscp_t ret;
  register uint32_t low, high;
  __asm__ __volatile__(
    "rdtscp "
    : "=a" (low), "=d" (high), "=c" (ret.m_cpuid) : :);
  ret.m_cycles = high; ret.m_cycles <<= 32; ret.m_cycles += low;

  return ret;
}

int main(int argc, char** argv) {
  const char* s1 = "133333333";
  uint64_t start, end;

  char* s2 = strdup(s1);
  uint64_t total = 0;
  for (uint l = 0; l < 10000; ++l) {
    start = rdtscp().m_cycles;
    uint32_t j = FastAtoi::atoi<uint32_t>(s2, 9);
    end = rdtscp().m_cycles;
    total += end-start;
   // cout << "Got number: " << j << endl;
  }

  cout << "Avg clock cycles: " << (total/10000) << endl;

  total = 0;
  sleep(2);

  for (uint l = 0; l < 10000; ++l) {
    start = rdtscp().m_cycles;
    int i = atoi(s1);
    end = rdtscp().m_cycles;
    total += end-start;
   // cout << "Got number: " << i << endl;
  }

  cout << "Avg clock cycles: " << (total/10000) << endl;

  return 0;
}
