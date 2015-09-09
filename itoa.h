#ifndef _ITOA_H_
#define _ITOA_H_

char* itoa(int32_t value, char* buff, const uint32_t base = 10) {
  if (base < 2 || base > 36) {
    *buff = '\0';
    return buff;
  }

  char* ptr = buff;
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

  return buff;
}

#endif // _ITOA_H_
