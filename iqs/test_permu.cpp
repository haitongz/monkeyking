// 3. string permutation
// say n=5, list all permutations like 12345,12354,12453,...,54321
// disable warning C4786: symbol greater than 255 character, okay to ignore
#pragma warning(disable: 4786)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

int main()
{
   int n;
   cout << "Input number: " << endl;
   cin >> n;
   const int VECTOR_SIZE = n ;

   // Define a template class vector of strings
   typedef vector<string> StrVector;

   //Define an iterator for template class vector of strings

   //Define an ostream iterator for strings
   typedef ostream_iterator<string> StrOstreamIt;

   StrVector pattern(VECTOR_SIZE);

   StrVector::iterator start, end, it;

   StrOstreamIt outIt(cout, ", ") ;

   start = pattern.begin();                       // location of first element of Pattern

   end   = pattern.end();                         // one past the location last element of Pattern

   //Initialize vector Pattern
   for (int i = 0; i < VECTOR_SIZE; ++i) {
      char buf[32];
      sprintf(buf, "%d", i+1);
      pattern[i] = buf;
   }

   // print content of Pattern
   cout << "Before calling next_permutation..." << endl
      << "Pattern: " << endl;

   for (it = start; it != end; ++it)
      cout << *it << " ";
   cout << endl;

   // Generate all possible permutations

   cout << "After calling next_permutation...." << endl;
   while (next_permutation(start, end)) {
      copy(start, end, outIt);
      cout << endl;
   }

   return 0;
}
