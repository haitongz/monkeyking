/*
The API: int read4(char *buf) reads 4 characters at a time from a file.
The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.
By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
Note:
The read function will only be called once for each test case.
 */
#include <iostream>

using namespace std;

uint32_t read(char* buf, const uint32_t n) {
  const uint32_t blocks = n/4;
  auto orig = buf;

  for (uint32_t i = 0; i < blocks; ++i) {
    uint8_t curr = read4(buf);
    buf += curr;
    if (curr < 4) // reached end of file
      return buf-orig;
  }

  const uint8_t left = n%4;
  char last[4];
  const uint8_t last_read = read4(last);
  const uint8_t actual = min(left, last_read); // in case end of file
  memcpy(buf, last, actual);
  buf += actual;
  return buf-orig;
}

/*
Follow up: what if read can be called multiple times?
 */
char last_buf[4] {0};
uint32_t last_pos {0}, last_len {0};

uint32_t read(char* buf, const uint32_t n) {
  auto orig = buf;

  uint32_t read_last = min(last_len-last_pos, n);
  memcpy(buf, last_buf+last_pos, read_last);
  buf += read_last;
  last_pos += read_last;
  n -= read_last;
  if (n <= 0)
    return (buf-orig);

  const uint32_t blocks = n/4;
  for (uint32_t i = 0; i < blocks; ++i) {
    const uint8_t curr = read4(buf);
    buf += curr;
    if (curr < 4) // reached end of file
      return (buf-orig);
  }

  last_len = read4(last_buf);
  last_pos = min(last_len, n%4);
  memcpy(buf, last_buf, last_pos);
  buf += last_pos;
  return (buf-orig);
}

int main(int argc, char** argv) {
}
