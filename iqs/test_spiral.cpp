// 5. Print a 2-D array in spiral way
/*
 * Sample output:
  1  2  3  4
  5  6  7  8
  9 10 11 12
 13 14 15 16
 17 18 19 20

 1 2 3 4 8 12 16 20 19 18 17 13 9 5 6 7 11 15 14 10
 */
#include <iostream>

void TwoDArraySpiral(int N)
{
   int a[N][N];
   int val = 1;

   for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
         a[i][j] = 1 + N*i + j;

   // spiral
   for (int i = N-1, j = 0; i > 0; --i, ++j) {
      for (int k = j; k < i; ++k) std::cout << a[j][k] << " ";
      for (int k = j; k < i; ++k) std::cout << a[k][i] << " ";
      for (int k = i; k > j; --k) std::cout << a[i][k] << " ";
      for (int k = i; k > j; --k) std::cout << a[k][j] << " ";
   }

   // special case for middle element if N is odd
   if (N % 2 == 1)
      std::cout << (a[(N-1)/2][(N-1)/2]) << std::endl;

   std::cout << std::endl;
}

int main()
{
   std::cout << "Input number of rows: " << std::endl;
   int N;
   std::cin >> N;

   TwoDArraySpiral(N);
   return 0;
}
