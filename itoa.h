#ifndef _ITOA_H_
#define _ITOA_H_

char* itoa(int32_t value, char* buffer, const uint32_t base = 10) {
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

  // apply negative sign
  if (tmp_v < 0)
    *ptr++ = '-';
  *ptr-- = '\0';

  while (cp < ptr) {
    char tmp = *ptr;
    *ptr-- = *cp;
    *cp++ = tmp;
  }

  return buffer;
}

#endif // _ITOA_H_
