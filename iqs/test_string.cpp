#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> // for log10()
#include <string>

#define MAXLINE 1000

void
reversehelper( char* begin, char* end )
{
   while( begin < end ) {
      char temp = *begin;
      *begin = *end;
      *end = temp;
      ++begin;
      --end;
   }
}

void
myreverse( char* s )
{
   if( *s )
      reversehelper( s, s+::strlen(s)-1 );
}

#define IN 1
#define OUT 0

void
reversewords( char* s )
{
   char* p = s;
   char* q = s;
   int i = 0, state = OUT;

   for( ; *p; ++p ) {
      if( isspace( *p ) ) {
         if( state == IN )
	    state = OUT;
         ++i;
      } else if( state == OUT ) {
         state = IN;
         reversehelper( s, p-i-1 );
         s = p;
         i = 0;
      }
   }
   reversehelper( s, p-i-1 ); // reverse last word in sentence, also takes care of when there's just one word
   s = q;
}

void
reversewordorder( char* s )
{
   if( *s )
      reversehelper( s, s+::strlen(s)-1 );

   reversewords( s );
}

void
reverse_str( char* begin, char* end )
{
   char aux = '\0';
   while( end > begin ) {
      aux = *end, *end-- = *begin, *begin++ = aux;
   }
}

#if 0
void convertCase(char * c)
{
   *c += (*c + ('A'-'a')) % ('Z'-'a');
}
#endif

/* copy string src to string dest, including '\0' */
char*
mystrcpy( char* dest, const char* src )
{
   // old implementation
   // while ((*dest++ = *source++) != '\0');

   char* orig = dest;
   while( *dest++ = *src++ );
   return orig;
}

int
mystrlen( char s[] )
{
   register int count = 0;

   while( s[count] != '\0' )
      ++count;
   return count;
}

int
mystrcmp( char* s, char* t )
{
   for( ; *s == *t; ++s, ++t ) {
      if( *s == '\0' )
	 return 0;
   }
   return *s-*t;
}

void
mystrcat( char* s, char* t )
{
   while( *s++ );
   strcpy(s, t);
}

#define MAX_BUF 16

char*
my_strncpy( char* dest, const char* src, size_t n )
{
   char* p = dest;

   for( ; n > 0 && *src != '\0'; --n )
      *p++ = *src++;

   for( ; n > 0; --n )
      *p++ = '\0';

   return dest;
}

char*
my_strncat( char* s, const char* ct, size_t n )
{
   char* p = s;

   while( *p != '\0' )
      ++p;

   for( ; n > 0 && *ct != '\0'; --n )
      *p++ = *ct++;

   *p = '\0';
   return s;
}

int
my_strncmp( const char* cs, const char* ct, size_t n )
{
   while( n > 0 && *cs == *ct && *cs != '\0' ) {
      ++cs;
      ++ct;
      --n;
   }

   if( !n || *cs == *ct )
      return 0;

   if( *(unsigned char*)cs < *(unsigned char*)ct )
      return -1;
   return 1;
}

void
test_ncpy( const char* str )
{
   char std_buf[MAX_BUF];
   char my_buf[MAX_BUF];

   ::memset( std_buf, 0x42, sizeof(std_buf) );
   strncpy( std_buf, str, sizeof(std_buf) );

   ::memset(my_buf, 0x42, sizeof(my_buf));
   my_strncpy(my_buf, str, sizeof(my_buf));

   if (::memcmp(std_buf, my_buf, sizeof(std_buf)) != 0) {
      std::cerr << "my_strncpy failed for " << str << std::endl;
      return;                                     //exit(-1);
   }
}

void
test_ncat(const char * first, const char * second)
{
   char std_buf[MAX_BUF];
   char my_buf[MAX_BUF];

   ::memset(std_buf, 0x69, sizeof(std_buf));
   strcpy(std_buf, first);
   strncat(std_buf, second, sizeof(std_buf)-strlen(std_buf)-1);

   ::memset(my_buf, 0x69, sizeof(my_buf));
   strcpy(my_buf, first);
   my_strncat(my_buf, second, sizeof(my_buf) - strlen(my_buf) - 1);

   if (::memcmp(std_buf, my_buf, sizeof(std_buf)) != 0) {
      std::cerr << "my_strncat failed, "
         << first << " and " << second << std::endl;
      // exit(EXIT_FAILURE);
      return;
   }
}

void
test_ncmp(const char * first, const char * second)
{
   size_t len = strlen(first) < strlen(second) ?
      strlen(second) : strlen(first);

   int std_ret = strncmp(first, second, len);
   int my_ret = my_strncmp(first, second, len);
   if (std_ret < 0 && my_ret >= 0 ||
      std_ret > 0 && my_ret <= 0 ||
   std_ret == 0 && my_ret != 0) {
      std::cerr << "my_strncat failed, "
         << first << " and " << second << std::endl;
      return;
      //		exit(EXIT_FAILURE);
   }
}

/**
 *Write the function strend(s,t), which returns 1 if the string t
 *occurs at the end of the string s, and zero otherwise.
 */

int strend(char * s, char * t)
{
   int result = 0;
   int s_length = mystrlen(s);
   int t_length = mystrlen(t);

   /* check if the lengths mean that the string t could fit at the string s */
   if (t_length <= s_length) {
      /* advance the s pointer to where the string t would have to start in string s */
      s += s_length - t_length;

      /* and make the compare using strcmp */
      if (!mystrcmp(s, t)) {
         result = 1;
      }
   }

   return result;
}

#if 0
char *
myutoa(unsigned value, char * digits, int base = 10)
{
   if (digits == NULL || base < 2 || base > 36)
      return NULL;

   char * s = "0123456789abcdefghijklmnopqrstuvwxyz";
   /* don't care if s is in

    * read-only memory
    */
   if (value < (unsigned) base) {
      digits[0] = s[value];
      digits[1] = '\0';
   }
   else {
      char * p = NULL;
      for (p = myutoa(value / ((unsigned)base), digits, base);
         *p;
         p++);
      myutoa( value % ((unsigned)base), p, base);
   }
   return digits;
}

char *
myitoa(int value, char * digits, int base)
{
   char *d;
   unsigned u;
   /* assume unsigned is big enough to hold all the
    * unsigned values -x could possibly be -- don't
    * know how well this assumption holds on the
    * DeathStation 9000, so beware of nasal demons
    */

   d = digits;
   if (base == 0)
      base = 10;
   if (digits == NULL || base < 2 || base > 36)
      return NULL;
   if (value < 0) {
      *d++ = '-';
      u = -((unsigned)value);
   } else
   u = value;
   myutoa(u, d, base);
   return digits;
}

void swap(char *a, char *b, size_t n)
{
   while (n--) {
      *a ^= *b;
      *b ^= *a;
      *a ^= *b;
      a++;
      b++;
   }
}

void my_memrev(char * s, size_t n)
{
   switch (n) {
      case 0:
      case 1:
         break;
      case 2:
      case 3:
         swap(s, s + n - 1, 1);
         break;
      default:
         my_memrev(s, n / 2);
         my_memrev(s + ((n + 1) / 2), n / 2);
         swap(s, s + ((n + 1) / 2), n / 2);
         break;
   }
}

void reverse(char *s)
{
   char *p;

   for (p = s; *p; p++)
      ;
   my_memrev(s, (size_t)(p - s));
}

/* strindex: return index of t in s, -1 if not found */

/* needed strchr(), so here it is: */

char * strchr(char *s, int c)
{
   char ch = c;

   for ( ; *s != ch; ++s)
      if (*s == '\0')
         return NULL;
   return s;
}

int strindex(char *s, char *t)
{
   char *u, *v, *w;

   if (*t == '\0')
      return 0;
   for (u = s; (u = strchr(u, *t)) != NULL; ++u) {
      for (v = u, w = t; ; )
         if (*++w == '\0')
            return (int)(u - s);
      else if (*++v != *w)
         break;
   }
   return -1;
}
#endif

int getline(char s[], int lim)
{
   int c, i;

   for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
      s[i] = c;
   if(c == '\n') {
      s[i] = c;
      ++i;
   }
   s[i] = '\0';
   return i;
}

#if 0
int myatoi(const char * str)
{
   if (NULL == str || '\0' == *str)
      return -1;

   int sign = (str[0] == '-') ? -1 : 1;
   int i = (str[0] == '-') ? 1 : 0;
   u_int32_t value = 0;
   char ch = '\0';

   while (ch = str[i++]) {
      if (ch >= '0' && ch <= '9')
         value = value*10 + (ch - '0');
      else
         return 0;
   }
   return value*sign;
}

// Write a function that allocates memory for a two-dimensional array of given size(parameter x & y)
void TwoDimentional()
{
   int x = 0, y = 0;
   Array = (int **) calloc( Height, sizeof(int *));
   *(Array) = (int *) calloc( Width * Height, sizeof(int));
   for (y = 0; y < Height; ++y) {
      Array[y] = &(Array[0][x]);
      x += Width;
   }
}

int getDigit(int & n)
{
   int temp;
   temp = n % 10;
   n /= 10;
   return temp;
}

void addToNumber(int & r, int digit, int power)
{
   r *= 10;
   r += digit;
}

// Write a routine to reverse a series of numbers without using an array.
int f()
{
   int number = 98765;
   int reverse = 0;
   int digit = 0;
   for(int i = 0; number > 0; ++i) {
      digit = getDigit(number);
      addToNumber(reverse, digit, i);
   }
   return reverse;
}

/* itoa implementation with malloc */
void myitoa(int value, char ** str, int base)
{
   /* Validate base */
   if (base < 2 || base > 35) {
      *str = strdup("");
      return;
   }

   /* Take care of sign */
   int sign = value;
   if (sign < 0)
      value = -value;

   static char num[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   unsigned digits = (sign >= 0) ? log10(value)+1 : log10(value)+2;

   /* for speed, should allocate a big buffer*/
   char * wstr = *str = (char *)malloc(digits+1); //malloc(68);
   div_t res;

   /* Conversion. Number is reversed. */
   do {
      res = div(value, base);
      *wstr++ = num[res.rem];
   }
   while ((value = res.quot));

   if(sign < 0)
      *wstr++='-';
   *wstr='\0';

   /* Reverse string */
   reverse_str(*str, wstr-1);
}
#endif

u_int64_t
S_div64(u_int64_t & aNum, u_long base = 10)
{
   u_int64_t lTmp = aNum % base;
   aNum /= base;
   return lTmp;
}

/* fast, but can only be called once at a time */
char *
untostr(unsigned long long num, unsigned int base, int len, char fill)
{
   static char digits[] ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   static char buf[66];

   char * p = buf + sizeof(buf);
   *--p = '\0';

   if (base > 62) {
      return p;
   }

   u_int64_t num64 = num;

   do {
      *--p = digits[S_div64(num64, base)];
   } while (num64);

   if (len <= -1) {
      return p;
   }
   else {
      char * q = buf + sizeof(buf)-len-1;
      while (p > q) {
         *--p = fill;
      }
      return q;
   }
}

#if 0
int base64EncodingRequired(const char * str)
{
   unsigned int i = 0;
   int validText = 1;

   while ('\0' != str[i]) {
      if (str[i] < 32) {
         if (isspace(str[i])) {
            ++i;
            continue;
         }
         else {
            validText = 0;
            break;
         };
      }
      #if 0
      else if (str[i] > 127) {
         validText = 0;
         break;
      }
      #endif
      ++i;
   }                                              /* end of while */

   return !validText;
}

inline std::string
trim(const char * aString)
{
   if (NULL != aString) {
      while (isspace(*aString))
         ++aString;
      register std::string::size_type lStrLength = ::strlen(aString);
      while (lStrLength > 0 && isspace(aString[lStrLength - 1]))
         --lStrLength;
      static std::string lRet(aString, lStrLength);
      return lRet.c_str();
   }
   else
      return "";
}

inline size_t
my_strlcpy(register char *dst, const char *src, register size_t maxBytes)
{
   if (0 == maxBytes)
      return 0;

   size_t srclen = strlen(src);
   if (srclen < maxBytes) {
      ::memcpy(dst, src, srclen);
      dst[srclen] = 0;
      return srclen;
   }
   else {
      ::memcpy(dst, src, maxBytes - 2);
      dst[maxBytes - 1] = '\0';
      return maxBytes - 2;
   }
}
#endif

void trim(std::string & str)
{
   // trim Both leading and trailing spaces
   std::size_t start = str.find_first_not_of(" \t");
   std::size_t end   = str.find_last_not_of(" \t");

   // if all spaces or empty return an empty string
   if (std::string::npos == start || std::string::npos == end) {
      str = "";
   }
   else
      str = str.substr(start, end-start+1);
   /* 
     // Code for  Trim Leading Spaces only
     size_t startpos = str.find_first_not_of(” \t”); // Find the first character position after excluding leading blank spaces
     if( string::npos != startpos )
         str = str.substr( startpos );
     // Code for Trim trailing Spaces only
     size_t endpos = str.find_last_not_of(” \t”); // Find the first character position from reverse af
     if( string::npos != endpos )
         str = str.substr( 0, endpos+1 );
     */
}

std::string
missingLetters(const std::string & sentence)
{
   if (sentence.empty())
      return "abcdefghigklmnopqrstuvwxyz";

   std::string otpt;
   char lower = 'a';
   char upper = 'A';

   for (; lower <= 'z'; ++lower, ++upper) {
      if (std::string::npos == sentence.find_first_of(lower) &&
      std::string::npos == sentence.find_first_of(upper)) {
         otpt += lower;
      }
   }

   return otpt;
}

int main(int argc, char **argv)
{
   if (argc < 2 || argc > 2) {
      printf("IllegalArgument Exception!\n");
      return -1;
   }

   myreverse(argv[1]);
   printf("Reversed input is: %s\n", argv[1]);
   // reverse(argv[1]);
   // printf("Reversed again input is: %s\n", argv[1]);
   reversewords(argv[1]);
   printf("Reversed words are: %s\n", argv[1]);
   reversewordorder(argv[1]);
   printf("Reversed words are: %s\n", argv[1]);
   reverse_str(argv[1], argv[1]+::strlen(argv[1])-1);
   printf("Reversed order of words are: %s\n", argv[1]);

   printf("The input length is: %d\n", mystrlen(argv[1]));
   char * temp = (char *)malloc(sizeof(char));
   mystrcpy(temp, argv[1]);
   printf("Copied string is %s\n", temp);
   test_ncpy("");
   test_ncpy("a");
   test_ncpy("ab");
   test_ncpy("abcdefghijklmnopqrstuvwxyz");       /* longer than MAX_BUF */

   test_ncat("", "a");
   test_ncat("a", "bc");
   test_ncat("ab", "cde");
   test_ncat("ab", "cdefghijklmnopqrstuvwxyz");   /* longer than MAX_BUF */

   test_ncmp("", "");
   test_ncmp("", "a");
   test_ncmp("a", "a");
   test_ncmp("a", "ab");
   test_ncmp("abc", "ab");

   printf("All tests pass.\n");
   delete [] temp;

   const char * s = "12345";
   std::cout << "total length is " << strlen(s) << std::endl;

   std::string sentence = "A quick broWn foX jumps over the laZy dog";
   std::cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
      << missingLetters(sentence) << "\"" << std::endl;

   sentence = "A slow yellow fox craWls unDer the proactive dog";
   std::cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
      << missingLetters(sentence) << "\"" << std::endl;
   sentence = "Lions, and Tigers, and Bears, oh my!";
   std::cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
      << missingLetters(sentence) << "\"" << std::endl;

   std::string testStr = "\n   c,vnm,wojk234190adv,234!kfsf0&@^&@#(Q@&$kjdfkm,nvc,ekdfja.z.a[]wmncvmnwo9.120903,nmcvznme[qkl...   \t";
   std::cout << "Trimming the string...\n" << std::endl;

   #if 0
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         trim(lTestStr);
      }
   }
   #endif

   trim(testStr);
   std::cout << testStr << std::endl;

   int i = 18;
   int * p = &i;
   ++(*p);
   std::cout << "The number is " << i << "." << std::endl;

   #if 0
   char dest[32];
   std::cout << "source string has " << testStr.size()
      << " bytes, " << cbr_strlcpy(dest, testStr.c_str(), sizeof(dest))
      << " bytes copied over to destination, string is "
      << dest << std::endl;

   unsigned long loops = 1000000;
   char data[16];
   char data2[15];
   char data3[128];
   size_t size = sizeof(data);
   size_t size2 = sizeof(data2);
   size_t size3 = sizeof(data3);
   const char * str = "benchmarking...";
   const char * str2 = "";
   char str3[10000];

   for (unsigned i = 0; i < 10000; ++i) {
      str3[i] = 'a';
   }

   std::cout << "\ncbr_strlcpy: 16 bytes dest(same length)..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         cbr_strlcpy(data, str, size);
      }
   }
   std::cout << "data is now " << data << std::endl;

   std::cout << "\nmy_strlcpy 16 bytes dest(same length)..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         my_strlcpy(data, str, size);
      }
   }
   std::cout << "data is now " << data << std::endl;

   std::cout << "\ncbr_strlcpy: 15 bytes dest(one byte short)..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         cbr_strlcpy(data2, str, size2);
      }
   }
   std::cout << "data is now " << data2 << std::endl;

   std::cout << "\nmy_strlcpy: 15 bytes dest(one byte short)..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         my_strlcpy(data2, str, size2);
      }
   }
   std::cout << "data is now " << data2 << std::endl;

   std::cout << "\ncbr_strlcpy: 128 bytes dest..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         cbr_strlcpy(data3, str, size3);
      }
   }
   std::cout << "data is now " << data3 << std::endl;

   std::cout << "\nmy_strlcpy: 128 bytes dest..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         my_strlcpy(data3, str, size3);
      }
   }
   std::cout << "data is now " << data3 << std::endl;

   std::cout << "\ncbr_strlcpy: empty src..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         cbr_strlcpy(data, str2, size);
      }
   }
   std::cout << "data is now " << data << std::endl;

   std::cout << "\nmy_strlcpy: empty src..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         my_strlcpy(data, str2, size);
      }
   }
   std::cout << "data is now " << data << std::endl;

   std::cout << "\ncbr_strlcpy: 100,000 bytes src..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         cbr_strlcpy(data2, str3, size2);
      }
   }
   std::cout << "data is now " << data2 << std::endl;

   std::cout << "\nmy_strlcpy: 100,000 bytes src..." << std::endl;
   {
      S_TimeIntv watcher(loops);
      for (unsigned i = 0; i < loops; ++i) {
         my_strlcpy(data2, str3, size2);
      }
   }
   std::cout << "data is now " << data2 << std::endl;
   #endif

   return 0;
}
