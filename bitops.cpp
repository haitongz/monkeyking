#include <cassert>
#include <iostream>

using namespace std;

#define BYTE_SIZE 8
#define bit2Byte(numOfBits) ((numOfBits+7) >> 3) // convert number of bits to number of bytes

namespace {
  const unsigned char singleBit[8] = {0x80, 0x40, 0x20, 0x10, 0x8,  0x4,  0x2,  0x1};
  const unsigned char leftMask[8]  = {0xFF, 0x7F, 0x3F, 0x1F, 0xF,  0x7,  0x3,  0x1};
  const unsigned char rightMask[8] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
}

void setBit(unsigned char* b, uint idx) { // set a single bit
  b[idx>>3] |= singleBit[idx&7];
}

void clearBit(unsigned char* b, uint idx) { // clear a single bit
  b[idx>>3] &= ~singleBit[idx&7];
}

bool readBit(unsigned char* b, uint idx) { // read a single bit
  return (b[idx>>3] & singleBit[idx&7]) != 0;
}

uint nextSetBit(unsigned char* b, uint idx, bool v, uint numOfBits) { // find the index of the the next set bit
  unsigned char notByteV = v ? 0 : 0xff;
  uint iBit = idx;
  uint endByte = ((numOfBits-1) >> 3);
  uint iByte;

  /* scan initial byte */
  while ((iBit&7) && iBit < numOfBits) {
    if (readBit(b, iBit) == v) {
      return iBit;
    }

    ++iBit;
  }

  /* scan byte at a time, if not already in last byte */
  iByte = iBit >> 3;
  if (iByte < endByte) {
    while (iByte < endByte && b[iByte] == notByteV) {
      ++iByte;
    }

    iBit = iByte << 3;
  }

  /* scan last byte */
  while (iBit < numOfBits) {
    if (readBit(b, iBit) == v) {
      return iBit;
    }

    ++iBit;
  }

  return numOfBits;
}

uint reverseBits(uint v) {
  uint ret = v; // first get LSB of v
  uint shift = sizeof(v)*sizeof(char)-1; // extra shift needed at end

  for (v >>= 1; v; v >>= 1) {
    ret <<= 1;
    ret |= v&1;
    --shift;
  }

  ret <<= shift; // shift when v's highest bits are zero
  return ret;
}

uint bitcount2(int i) {
   i = i - ((i >> 1) & 0x55555555);
   i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
   return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

uint bitcount_kernighan(int i) {
  uint ret = 0;

  while (i) {
    i &= i-1;
    ++ret;
  }

  return ret;
}

template <int N>
struct Bits { // recursive template computing number of bits set in an integer
  static const uint count = (N&1) + Bits<(N>>1)>::count;
};

template <>
struct Bits<0> {
  static const uint count = 0;
};

// This template recursively generates a constructor that will populate a table of 256 entries
template <int N>
struct Table : public Table<N-1> {
  Table() {
    this->mem[N-1] = Bits<N-1>::count;
  }
};

template <>
struct Table<0> {
  uint mem[256];
};

static Table<256> table;

template <typename T>
uint bitcount(T v) {
  uint ret = 0;

  for (uint i = 0; v && (i != sizeof(T)); ++i, v >>= BYTE_SIZE) {
    ret += table.mem[v&0xff];
  }

  return ret;
}

uint bitcount(unsigned char c) {
  return table.mem[c];
}

uint bitcount(char c) {
  return bitcount(static_cast<unsigned char>(c));
}

int main(int argc, char** argv) {
  assert(Bits<127>::count == 7);
  assert(bitcount(0) == 0);
  assert(bitcount(1) == 1);
  assert(bitcount(-1) == 32);
  assert(bitcount((char)-1) == 8);
  assert(bitcount(3) == 2);
  assert(bitcount(127) == 7);
  assert(bitcount(1023) == 10);
  assert(bitcount(1025) == 2);

  cout << "255 has " << Bits<255>::count << " set bits." << endl;
  cout << "255 has " << bitcount2(255) << " set bits." << endl;
  cout << "255 has " << bitcount_kernighan(255) << " set bits." << endl;
  cout << "255 has " << __builtin_popcount(255) << " set bits." << endl;

  unsigned char c = 0;
  setBit(&c, 1);
  bool f = readBit(&c, 1);
  cout << "Read bit: " << (f ? "1" : "0") << endl;
  clearBit(&c, 1);
  f = readBit(&c, 1);
  cout << "Read bit: " << (f ? "1" : "0") << endl;

  uint n = 15;
  cout << "Reversed bits: " << reverseBits(n) << endl;

  n = (1 << 31);
  cout << "Wah: " << n << endl;
  for (uint i = 0; i < 9; ++i) {
    cout << "Index is: " << i << "\t";
    cout << "Shifting: " << (1 << i) << "\t";
    cout << "Bit manipulating: " << (i & 0x7) << "\t";
    cout << "Bit manipulating2: " << (i >> 3) << endl;
  }

  return 0;
}
