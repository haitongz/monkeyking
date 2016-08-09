#include "S_TimeIntv.H"

#include <iostream>
// #include <cmath> for log10

#define loops 1000000

inline void
strreverse(char* begin, char* end)
{
   char aux;
   while (end > begin) {
      aux=*end, *end--=*begin, *begin++=aux;
   }
}

#if 0
void itoa(int value, char* str, int base)
{
   static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
   char* wstr = str;
   int sign;
   div_t res;

   // Validate base
   if (base < 2 || base > 35) {
      *wstr='\0';
      return;
   }

   // Take care of sign
   if ((sign=value) < 0)
      value = -value;

   // Conversion. Number is reversed.
   do {
      res = div(value,base);
      *wstr++ = num[res.rem];
   }
   while (value = res.quot);

   if(sign < 0)
      *wstr++='-';
   *wstr='\0';

   // Reverse string
   strreverse(str,wstr-1);
}
#endif

inline void
itoa(int64_t value, char ** str, int32_t base)
{
   /* Validate base */
   if (base < 2 || base > 35) {
      *str = strdup("");
      return;
   }

   /* Take care of sign */
   bool negative = (value < 0);
   if (negative)
      value = -value;

   ///	digits = (sign >= 0) ? std::log10(static_cast<double>(value))+1 : std::log10(static_cast<double>(value))+2;
   static char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   char * wstr = *str = (char *)malloc(66);       /// digits + 1);
   ldiv_t res;

   /* Conversion. Number is reversed. */
   do {
      res = std::div(static_cast<long>(value), static_cast<long>(base));
      *wstr++ = num[res.rem];
   }
   while ((value = res.quot));

   if (negative)
      *wstr++='-';
   *wstr='\0';

   /* Reverse string */
   strreverse(*str, wstr-1);
}

inline u_int64_t
S_div64(register u_int64_t & aNum, register u_int32_t base = 10)
{
   register u_int64_t lTmp = aNum % base;
   aNum /= base;
   return lTmp;
}

inline void
ntostr(register char ** aRet, register int64_t & aNum, register u_int32_t base = 10, register int32_t len = -1, register char fill = '0')
{
   bool negative = aNum < 0;
   u_int64_t num = negative ? -aNum : aNum;

   static char digits[] ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   static char buf[66];
   register char * p = buf + 66;                  // sizeof(buf);
   *--p = '\0';
   if (base > 62) {
      return;
   }
   do {
      *--p = digits[S_div64(num, base)];
   } while (num);

   #if 0
   if (len <= -1)
   #endif
   {
      if (negative)
         *--p = '-';
      *aRet = p;
   }
   #if 0
   else {
      register char * q = buf + sizeof(buf) - len - 1;
      while (p > q) {
         *--p = fill;
      }
      return q;
   }
   #endif
}

int main()
{
   register u_int32_t i = 0;
   int64_t lNums[loops];
   char * lArray[loops];
   char * lArray2[loops];

   for (i = 0; i < loops; ++i) {
      lNums[i] = rand();
      if (0 == lNums[i]%3)
         lNums[i] = -lNums[i];
   }

   std::cout << "\ntesting itoa..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (i = 0; i < loops; ++i) {
         itoa(lNums[i], &lArray[i], 10);
      }
   }
   for (i = 0; i < loops; ++i) {
      std::cout << "The " << i << "th element of itoa is: " << lArray[i] << std::endl;
   }
   std::cout << "\ntesting ntostr..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (i = 0; i < loops; ++i) {
         ntostr(&lArray2[i], lNums[i]);
      }
   }
   for (i = 0; i < loops; ++i) {
      std::cout << "The " << i << "th element of ntostr is: " << lArray2[i] << std::endl;
   }
   delete [] lArray;
   return 0;
}
