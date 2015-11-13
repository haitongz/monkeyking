#ifndef _ITOA_H_
#define _ITOA_H_

#include <type_traits>

char* itoa(int32_t value, char* buffer, const uint8_t base = 10) {
  if (base < 2 || base > 36) {
    *buffer = '\0';
    return buffer;
  }

  char* ptr = buffer;
  char* cp = ptr;
  int32_t tmp_v;

  do {
    tmp_v = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35+(tmp_v-value*base)];
  } while (value);

  if (tmp_v < 0) // apply negative sign
    *ptr++ = '-';
  *ptr-- = '\0';

  while (cp < ptr) {
    char tmp = *ptr;
    *ptr-- = *cp;
    *cp++ = tmp;
  }

  return buffer;
}

namespace meta {

template <uint64_t _base_, uint8_t _n_>
struct pow {
  static const uint64_t value = _base_ * pow<_base_,_n_-1>::value;
};

template <uint64_t _base_>
struct pow<_base_,1> {
  static const uint64_t value = _base_;
};

template <uint64_t _base_>
struct pow<_base_,0> {
  static const uint64_t value = 1;
};

template <uint8_t _n_>
struct pow<2,_n_> {
  static const uint64_t value = static_cast<uint64_t>(1) << _n_;
};

template <>
struct pow<2,1> {
  static const uint64_t value = static_cast<uint64_t>(1) << 1;
};

template <>
struct pow<2,0> {
  static const uint64_t value = static_cast<uint64_t>(1);
};

}

/*inline static */
void itoa(uint32_t x, char* buffer, const uint8_t dig) {
  // TODO: optimize
  // static_assert(dig >= 0 && dig <= 10);
  uint32_t d;
  switch (dig) {
  case 10:
    d = x / meta::pow<10,9>::value;
    x = x % meta::pow<10,9>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 9:
    d = x / meta::pow<10,8>::value;
    x = x % meta::pow<10,8>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 8:
    d = x / meta::pow<10,7>::value;
    x = x % meta::pow<10,7>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 7:
    d = x / meta::pow<10,6>::value;
    x = x % meta::pow<10,6>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 6:
    d = x / meta::pow<10,5>::value;
    x = x % meta::pow<10,5>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 5:
    d = x / meta::pow<10,4>::value;
    x = x % meta::pow<10,4>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 4:
    d = x / meta::pow<10,3>::value;
    x = x % meta::pow<10,3>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 3:
    d = x / meta::pow<10,2>::value;
    x = x % meta::pow<10,2>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 2:
    d = x / meta::pow<10,1>::value;
    x = x % meta::pow<10,1>::value;
    *buffer = static_cast<char>('0'+d);
    ++buffer;
  case 1:
    *buffer = static_cast<char>('0'+x);
  case 0:
    break;
  }
}

template <uint32_t _digits_>
struct FastItoa {
  static void itoa(char* buffer, uint32_t x) {
    uint32_t d = x / meta::pow<10,_digits_-1>::value;
    uint32_t r = x % meta::pow<10,_digits_-1>::value;
    *buffer = static_cast<char>('0'+d);
    FastItoa<_digits_-1>::itoa(buffer+1, r);
  }
};

template <>
struct FastItoa<1> {
  static void itoa(char* buffer, uint32_t x) {
    *buffer = static_cast<char>('0'+x);
  }
};

template <>
struct FastItoa<0> {
  static void itoa(char* buffer, uint32_t x) {
  }
};

template <uint32_t _digits_>
struct FastBase32Itoa {
  static void r_itoa(char* last, uint32_t x) __attribute__((always_inline)) {
    *last = "0123456789ABCDEFGHIJKLMNOPQRSTUV"[x & 31];
    FastBase32Itoa<_digits_-1>::r_itoa(last-1, x >> 5);
  }
  static void itoa(char* buffer, uint32_t x) __attribute__((always_inline)) {
    r_itoa(buffer+_digits_-1, x);
  }
};

template <>
struct FastBase32Itoa<1> {
  static void r_itoa(char* last, uint32_t x) __attribute__((always_inline)) {
    *last = "0123456789ABCDEFGHIJKLMNOPQRSTUV"[x & 31];
  }
  static void itoa(char* buffer, uint32_t x) __attribute__((always_inline)) {
    r_itoa(buffer, x);
  }
};

template <>
struct FastBase32Itoa<0> {
public:
  static void itoa(char* buffer, uint32_t x) {
    // No op
  }
};

template <uint32_t _digits_>
class FastBase64Itoa {
public:
  static void itoa(char* buffer, uint32_t x) {
    static const char* _symbols_ =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static const uint32_t _mod_mask_ = (1 << ((_digits_-1)*6)) - 1;
    // TODO: Optimize
    uint32_t d = x >> ((_digits_-1)*6);
    uint32_t r = x & _mod_mask_;
    // static_assert(d >=0 && d < 64);
    *buffer = _symbols_[d];
    FastBase64Itoa<_digits_-1>::itoa(buffer+1, r);
  }
};

template <>
class FastBase64Itoa<1> {
public:
  static void itoa(char* buffer, uint32_t x) {
    static const char* _symbols_ =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    *buffer = _symbols_[x];
  }
};

template <>
class FastBase64Itoa<0> {
public:
  static void itoa(char* buffer, uint32_t x) {
    // No op
  }
};

#endif // _ITOA_H_
