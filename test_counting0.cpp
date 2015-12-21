#include <cassert>
#include <cstdlib>
#include <iostream>

// Recursive template, computes the number of bits set in an integer ( e.q. Bits<127>::count == 7 )
template <int N>
struct Bits
{
  static const unsigned count = (N&1) + Bits<(N>>1)>::count;
};

template <>
struct Bits<0>
{
  static const unsigned count = 0;
};

// This template recursively generates a constructor that will populate a table of 256 entries
template <int N>
struct Table : public Table<N-1>
{
  Table<N>() {
    this->bitcount_[N-1] = Bits<N-1>::count;
  }
};

template <>
struct Table<0> {
  unsigned bitcount_[256];
};

static const size_t BYTE_SIZE = 8;
static Table<256> table;

template <typename T>
unsigned count_bits(T value) {
  size_t result = 0;
  for (size_t i = 0; value && (i != sizeof(T)); ++i, value >>= BYTE_SIZE) {
    result += table.bitcount_[value & 0xff];
  }

  return result;
}

unsigned
count_bits(unsigned char value) {
  return table.bitcount_[value];
}

unsigned
count_bits(char value)
{
  return count_bits(static_cast<unsigned char>(value));
}

// test
int main() {
  std::cout << "255 has " << Bits<255>::count << " 0s..." << std::endl;
  assert(Bits<127>::count == 7);
  assert(count_bits(0) == 0);
  assert(count_bits(1) == 1);
  assert(count_bits(-1) == 32);
  assert(count_bits((char)-1) == 8);
  assert(count_bits(3) == 2);
  assert(count_bits(127) == 7);
  assert(count_bits(1023) == 10);
  assert(count_bits(1025) == 2);

  return 0;
}
