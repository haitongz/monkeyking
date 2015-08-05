#ifndef _ITOA_H_
#define _ITOA_H_

char* itoa(int32_t value, char* result, const uint32_t base) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char* ptr = result, *ptr1 = result, tmp_char;
  int32_t tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35+(tmp_value-value*base)];
  } while (value);

  // apply negative sign
  if (tmp_value < 0)
    *ptr++ = '-';
  *ptr-- = '\0';

  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--   = *ptr1;
    *ptr1++  = tmp_char;
  }

  return result;
}

#endif // _ITOA_H_
