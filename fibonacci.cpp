#include <iostream>

// recursive
uint64_t fib(const uint64_t n) {
   if (n <= 1)
      return n;
   return fib(n-1) + fib(n-2);
}

// dynamic programming
uint64_t fib2(const uint64_t n) {
  uint64_t f[n+1];
  /* 0th and 1st number of the series are 0 and 1*/
  f[0] = 0;
  f[1] = 1;
  for (uint64_t i = 2; i < n+1; ++i) {
    f[i] = f[i-1] + f[i-2];
  }

  return f[n];
}

// space-optimized fib2
uint64_t fib3(const uint64_t n) {
  uint64_t a = 0, b = 1;
  if (!n)
    return a;

  for (uint64_t i = 2; i < n+1; ++i) {
    uint64_t c = a+b;
    a = b;
    b = c;
  }

  return b;
}

// O(logn)
void mulMatrix(uint64_t F[2][2]) {
  uint64_t a = F[0][0];
  uint64_t b = F[1][0];
  F[0][0] = a+b;
  F[0][1] = a;
  F[1][0] = a;
  F[1][1] = b;
}

void powMatrix(uint64_t F[2][2], const uint64_t n) {
  for (uint64_t i = 2; i < n; ++i)
    mulMatrix(F);
}

uint64_t fib4(const uint64_t n) {
  if (!n)
    return 0;

  uint64_t F[2][2] = {{1,1},{1,0}};
  powMatrix(F, n);
  return F[0][0];
}

// optimized fib4
void mulOneMatrix(uint64_t F[2][2]) {
  uint64_t a = F[0][0];
  uint64_t b = F[1][0];
  F[0][0] = a+b;
  F[0][1] = a;
  F[1][0] = a;
  F[1][1] = b;
}

void pow2Matrix(uint64_t F1[2][2]) {
  uint64_t a = F1[0][0];
  uint64_t b = F1[0][1];
  uint64_t c = F1[1][0];
  uint64_t d = F1[1][1];
  F1[0][0] = a*a+b*c;
  F1[0][1] = a*b+b*d;
  F1[1][0] = c*a+c*d;
  F1[1][1] = c*b+d*d;
}

void powMatrix2(uint64_t F[2][2], const uint64_t n) {
  if (n < 2)
    return;

  const uint64_t mid = n>>1;
  powMatrix2(F, mid);
  pow2Matrix(F);
  if (n%2 == 1)
    mulOneMatrix(F);
}

uint64_t fib5(const uint64_t n) {
  if (!n)
    return 0;

  uint64_t F[2][2] = {{1,1},{1,0}};
  powMatrix2(F, n-1);
  return F[0][0];
}

int main(int argc, char** argv) {
  std::cout << fib(10) << std::endl;
  std::cout << fib2(10) << std::endl;
  std::cout << fib3(10) << std::endl;
  std::cout << fib4(10) << std::endl;
  std::cout << fib5(10) << std::endl;
}
