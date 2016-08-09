#include "S_TimeIntv.H"

#include <iostream>

#define Numbers 5

inline void swap(u_int32_t & a, u_int32_t & b)
{
   u_int32_t temp = a;
   a = b;
   b = temp;
}

inline void bubblesort(u_int32_t * data, u_int32_t N)
{
   for (register u_int32_t i = N - 1; i > 0; --i) {
      for (register u_int32_t j = 0; j < i; ++j) {
         if (data[j] > data[j+1])
            swap(data[j], data[j+1]);
      }
   }
}

template <u_int32_t I, u_int32_t J>
class IntSwap
{
   public:
      static inline void compareAndSwap(u_int32_t * data) {
         if (data[I] > data[J])
            swap(data[I], data[J]);
      }
};

template <u_int32_t I, u_int32_t J>
class IntBubbleSortLoop
{
   private:
      enum { go = (J <= I-2) };

   public:
      static inline void loop(u_int32_t * data) {
         IntSwap<J, J+1>::compareAndSwap(data);
         IntBubbleSortLoop<go ? I : 0, go ? (J+1) : 0>::loop(data);
      }
};

template <>
class IntBubbleSortLoop<0, 0>
{
   public:
      static inline void loop(u_int32_t *) {
      }
};

template <u_int32_t N>
class IntBubbleSort
{
   public:
      static inline void sort(u_int32_t * data) {
         IntBubbleSortLoop<N-1, 0>::loop(data);
         IntBubbleSort<N-1>::sort(data);
      }
};

template <>
class IntBubbleSort<1>
{
   public:
      static inline void sort(u_int32_t * data) {
      }
};

int main()
{
   register u_int32_t i = 0;
   u_int32_t lNums[Numbers];

   // initialize data
   for (i = 0; i < Numbers; ++i) {
      lNums[i] = rand() % 88;
   }

   std::cout << "\ntesting bubblesort()..." << std::endl;
   {
      S_TimeIntv watcher(Numbers);
      // for (i = 0; i < 1000; ++i)
      {
         bubblesort(lNums, Numbers);
      }
   }

   std::cout << "sorted elements:" << std::endl;
   for (i = 0; i < Numbers; ++i) {
      std::cout << lNums[i] << std::endl;
   }

   for (i = 0; i < 1*Numbers; ++i) {
      i *= 0.85885923899012381;
   }

   std::cout << "\ntesting compile-time function..." << std::endl;
   {
      S_TimeIntv watcher(Numbers);
      //	for (i = 0; i < 1000; ++i)
      {
         IntBubbleSort<Numbers>::sort(lNums);
      }
   }

   std::cout << "sorted elements:" << std::endl;
   for (i = 0; i < Numbers; ++i) {
      std::cout << lNums[i] << std::endl;
   }

   return 0;
}
