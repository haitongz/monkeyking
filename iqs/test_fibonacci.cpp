#include <iostream>

uint64_t
fib_iterative( unsigned stage )
{
   uint64_t minus_two = 1, minus_one = 1;

   for( unsigned i = 3; i <= stage; ++i ) {
      uint64_t curr_val = minus_two + minus_one;
      minus_two = minus_one;
      minus_one = curr_val;
   }

   return minus_one;
}

template< int stage >
struct fib_num
{
   /*
   enum
   {
      minus_one = fib_num< stage-1 >::value,
      minus_two = fib_num< stage-2 >::value
   };*/

   static const uint64_t value = fib_num<stage-1>::value + fib_num<stage-2>::value;

   static inline uint64_t get_value( int i )
   {
      if( i == stage )
      {                          // Does the current class hold the given place?
         return value; // Return it!
      }
      else {
         return fib_num<stage-1>::get_value( i ); // Get it from the previous class!
      }
   }
};

template<> // Template specialization for the 0's case.
struct fib_num<0>
{
   static const uint64_t value = 1;

   static inline uint64_t get_value( int i )
   {
      return value;
   }
};

template<> // Template specialization for the 1's case
struct fib_num<1>
{
   static const uint64_t value = 1;

   static inline uint64_t get_value( int i )
   {
      return value;
   }
};

struct helper
{
   static uint64_t fib_nums[100];

   static void initialize() {
      for( int i = 0; i < 100; ++i ) {
         fib_nums[i] = fib_num<100>::get_value( i );
         std::cout << "n:=" << i << " => " << helper::fib_nums[i] << std::endl;
      }
   }
};

uint64_t helper::fib_nums[100];

int main( int, char*[] )
{
   std::cout << "fibonacci number for 100=" << fib_iterative( 100 ) << std::endl;
   //generate (at compile time) 100 places of the Fib sequence.
   //Then, (at runtime) output the 100 calculated places.
   //Note: a 64 bit int overflows at place 92

   helper::initialize();
}
