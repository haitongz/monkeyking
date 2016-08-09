What is good code and what do you do when you see it?

Let me start with defining bad code:
* Failing to meet ( nebulous ) requirements fully
* Inappropriate ( or even worse, misleading or contradictory ) documentation/comment.
* Inappropriate encapsulation
* Exhibiting redundant source code
* Inconsistency of notational style and inappropriate naming conventions
* Employing inappropriate algorithmic techniques

// 2. Delete from doubly linked list
void
deleteNode( List* l, Node* n )
{
   if( !l ) {
      printf( "Null head...\n" );
      return;
   }

   Node* curr;
   while( (curr = l->getHead()) ) {
      if( curr->value == n->value ) {
         Node* prev = curr->prev;
         Node* next = curr->next;
         if( !prev ) {                            // first node
            next->prev = prev;
            list->resetHead( next );
         }                                        // next node
         else if( !next ) {
            prev->next = next;
         }
         else {
            prev->next = next;
            next->prev = prev;
         }

         delete curr;
         return;
      }
      else {
         curr = curr->next;
      }
   }
}

// 3. string permutation
// say n = 5, list all permutations like 12345,12354,12453,...,54321
// disable warning C4786: symbol greater than 255 character, okay to ignore
#pragma warning( disable: 4786 )

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

int main()
{
   cout << "Input number: " << endl;
   int n;
   cin >> n;
   const int VECTOR_SIZE = n;

   // Define a template class vector of strings
   typedef vector<string> StrVector;

   //Define an iterator for template class vector of strings

   //Define an ostream iterator for strings
   typedef ostream_iterator<string> StrOstreamIt;

   StrVector pattern( VECTOR_SIZE );

   StrVector::iterator start, end, it;

   StrOstreamIt outIt( cout, ", " ) ;

   start = pattern.begin(  );                     // location of first element of Pattern

   end = pattern.end(  );                         // one past the location last element of Pattern

   //Initialize vector Pattern
   for ( int i = 0; i < VECTOR_SIZE; ++i ) {
      char buf[32];
      sprintf( buf, "%d", i+1 );
      pattern[i] = buf;
   }

   // print content of Pattern
   cout << "Before calling next_permutation..." << endl
      << "Pattern: " << endl;

   for ( it = start; it != end; ++it )
      cout << *it << " ";
   cout << endl;

   // Generate all possible permutations

   cout << "After calling next_permutation...." << endl;
   while ( next_permutation(start, end )) {
      copy( start, end, outIt );
      cout << endl;
   }

   return 0;
}

#if 0
// 4. convert lowercase and uppercase
void ConvertChar( char * c )
{
   *c = ( *c ) ^ ('A' - 'a');
}
#endif

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

void TwoDArraySpiral( int N )
{
   int a[N][N];
   int val = 1;

   for ( int i = 0; i < N; i++ )
      for ( int j = 0; j < N; j++ )
         a[i][j] = 1 + N*i + j;

   // spiral
   for ( int i = N-1, j = 0; i > 0; --i, ++j ) {
      for ( int k = j; k < i; ++k ) std::cout << a[j][k] << " ";
      for ( int k = j; k < i; ++k ) std::cout << a[k][i] << " ";
      for ( int k = i; k > j; --k ) std::cout << a[i][k] << " ";
      for ( int k = i; k > j; --k ) std::cout << a[k][j] << " ";
   }

   // special case for middle element if N is odd
   if ( N%2 == 1 )
      std::cout << ( a[(N-1 )/2][(N-1)/2]) << std::endl;

   std::cout << std::endl;
}

int main(  )
{
   std::cout << "Input number of rows: " << std::endl;
   int N;
   std::cin >> N;

   TwoDArraySpiral(  N  );
   return 0;
}

// 6. Check if a string parameter is a number or not
int str2int( const char *str )
{
   int value = 0;
   int sign = (str[0] == '-') ? -1 : 1;
   int i = (str[0] == '-') ? 1 : 0;
   char ch;

   while( ch = str[i++] ) {
      if( (ch >= '0') && (ch <= '9') )
         value = value * 10 + (ch - '0');
      else
         return 0;
   }

   return value*sign;
}

// 7. Print data out in a binary tree, level by level; breath-first search
struct TreeNode
{
   TreeNode* left;
   TreeNode* right;
   int value;
};

// Breadth First Search ( BFS ) method searches the tree one level at a time
// non-recursive

TreeNode*
Breadth-First-Search( TreeNode* root, int searchValue )
{
   if( !root ) {
      std::cerr << "Invalid argument: NULL root node!" << std::endl;
      return NULL;
   }

   std::deque level;
   level.push_front( root );

   while( !level.empty() ) {
      for( int i = 0; i < level.size(); ++i ) {
         TreeNode* curr = level.front();
         level.pop_front();
         if( curr->data == searchValue )
            return currentNode;
      }

      if( curr->left )
         level.push_back( curr->left );

      if( curr->right )
         level.push_back( curr->right );
   }

   return NULL;
}

// Breadth First Search ( BFS ) method searches the tree one level at a time
// recursive

TreeNode*
BFS( TreeNode* root, int searchValue )
{
   if( !root ) {
      std::cerr << "Invalid argument: NULL root node!" << std::endl;
      return NULL;
   }

   TreeNode* ret = NULL;
   if( (ret = BFS( root->left )) )
      return ret;
   else if( (ret = BFS( root->right )) )
      return ret;

   return NULL;
}

// 8. Draw circle without floating point computation
void circle( int x,int y, int rad )
{
   //check boundary first
   for( int xi = x-rad, int yi = y-rad; xi <= x+rad, yi < y+rad; ++xi, ++yi )
      if( (xi-x)*(xi-x)+(yi-y)*(yi-y) = rad*rad + Error )
         set_point;
}

/* 9. find all characters in s1 appear in s2 and delete them
a 52-element array occur1[52] with 0.
Go through the string S1, and for each character s1[i], set occur1[s1[i]]=1;
Then go through the string S2, curr_pos=final_pos=0,
while( s2[curr_pos]!=NULL )
{
   if( occur1[s2[curr_pos]]==0 )
      {s2[final_pos]=s2[i];  final_pos++;}
      curr_pos++;
}

s2[final_pos]=NULL;
If the number of total characters are very large ( such as CHinese characters ),
then use some kind of hashing to speed up the table search operations.
*/

// 10. lexical analyzer for a*b
int lex-a-star-b( char *s )
{
   int i=0;
   while( s[i]=='a' )i++;
   if( (s[i]=='b' )&&(s[i+1]=='\0'))
      return 1;
   else return 0;
}

// 11. Write efficient code for extracting unique elements from a sorted list of array.
#include <stdio.h>
void main(  )
{
   int a[10] = {0, 4, 4, 4, 5, 6, 6, 8, 9, 9};

   for ( int i = 0; i < 10; ++i ) {
      if ( a[i] == a[i+1] ) {
         while ( a[i] == a[i+1] )
            ++i;
      }
      else
         printf( "%d ", a[i] );
   }
}

// 12. Print an integer using only putchar. Try doing it without using extra storage.
void printInt( int a )
{
   int b = a;
   char * str = NULL;
   int i = 1;
   int len = 0;

   while ( b ) {
      b /= 10;
      i *= 10;
      ++len;
   }

   i /= 10;

   while ( i > 0 ) {
      putchar( a/i + 48 );
      a = a%i;
      i /= 10;
   }
}

// 13. Write a function that allocates memory for a two-dimensional array of given size( parameter x & y )
void func()
{
   int x = 0, y = 0;
   Array = (int**) calloc( Height, sizeof(int*) );
   *(Array) = (int*) calloc( Width*Height, sizeof(int) );
   for( y = 0; y < Height; y++ ) {
      Array[y] = &( Array[0][x] );
      x += Width;
   }
}

// 14. Conditional compilation
#ifdef/ifndef
#else/elif
#endif

#pragma

// 15. Write a function that finds repeating characters in a string.
// use hash table
hashtable = create_hash_table( strlen(str ));
for( int i = 0; i < strlen(str ); i++)
   add_string( hashtable, str + i );
change add_string function, if element already exists, return it.

// 16. Write a routine to reverse a series of numbers without using an array.
#include <iostream.h>

int getDigit( int* );
void addToNumber( int*, int, int );

int main()
{
   int number = 98765;
   int reverse = 0;
   int digit = 0;

   for( int i = 0; number > 0; ++i ) {
      digit = getDigit( &number );
      addToNumber( &reverse, digit, i );
   }

   cout << reverse << endl;
   return 0;
}

int getDigit( int * n )
{
   int temp;
   temp = *n%10;
   *n /= 10;

   cout << "temp=" << temp << endl;
   return temp;
}

void addToNumber( int * r, int digit, int power )
{
   *r *= 10;
   *r += digit;
}

// 17. Write a function to compute the factorial of a given integer.
int fact( int n )
{
   return n > 0 ? ( n * fact(n-1 )) : 1;
}

// 18. Write a function that finds the last instance of a character in a string.

int lastInstance( char * s, char c )
{
   for ( int x = strlen(s ); x >= 0; --x) {
      if ( s[x] == c )
         return x+1;
   }

   return 0;
}

// 18. How would you decide what to test for given that there isn't enough time to test everything you want to?\r
prioritize what you want to test, in the order;
whether is taking right input and giving right output;
whether all the output conditions expected are met;
which really can crash the system, checking the boundary conditions;
which really annoy the user, hanging etc.;
which can cause loss of data, like memory corruption, memory leaks etc.;

// 19. What is a balanced tree?
First of all, a balanced tree need NOT necessarily be a binary tree. For example, a 2-3 tree is one of the most
balanced forms of tree structures. However, mostly the balanced trees are implemented as binary trees.
Secondly, a balanced tree is a tree, in which the height of each subtree is dependent on the rest of the subtrees
( NOT necessarily the same or differing just by one ). For example in a Red-black tree, the height of one subtree can
at the most be double that of the other.

// 20. Tradeoff between time spent in testing a product and getting into the market first.
Given a question of trade-off between time to test the product and marketing the product
things to consider are :
where to draw a line between the product can be shippable and not shippable. Shippable products can have bugs, but
the user experience scenarios are working correctly and if it won't create a hazard or stop to user experience, the\r
product can be shipped. So testing should consider prioritizing the show-stop scenarios, like crashes, hanging, memory
corruptions, scenarios for continuity in experience of user etc in top priority and ship the product, then proceed
further.

Many times, in the hi-tech market, you are going to be able to sell only if you are the first guy out with the product.
It is really important to be the market pioneer. If the market demands it, u better get the product out and ask the
developers and testers to go to hell. Getting a prototype of the product into the market is the least you can do. At
the same time if you can afford the time (  no pressure from competitors, new entrants, substitute products or buyers  )
then do as much as testing as possible. The balance between testing and the release should totally depend on the market!

// 21. You're part of the QA team for a large web site. You want to create as much automated testing as possible. What\r
could/would you test? How? How much maintenance would these tests require as the web site changes?
1. A poller that just checks to see if the site is up and running.
2. A test that pushes a lot of test data to the site and measure time taken for push.
3. A test that pulls a lot of test data from site and measure time taken.
4. Programatically invoke applets, ActiveX controls and verify results of operation.
5. Simulate a multiple user scenario and stress out the web site, determine its breaking point.

// 22. swap two integers without extra memory
void swap( int* a, int* b )
{
   if( a != b ) {                                 // avoid aliasing problem
      *a ^= *b;
      *b ^= *a;
      *a ^= *b;
   }
}

23. what is polymorphism?
'Polymorphism' is an object-oriented term. Polymorphism may be defined as the ability of related objects to respond to
the same message with different, but appropriate actions. In other words, polymorphism means taking more than one form.
Polymorphism leads to two important aspects in Object Oriented terminology - Function Overloading and Function
Overriding. Overloading is the practice of supplying more than one definition for a given function name in the same
scope. The compiler is left to pick the appropriate version of the function or operator based on the arguments with
which it is called. Overriding refers to the modifications made in the sub class to the inherited methods from the base
class to change their behaviors.

24. What is operator overloading?
When an operator is overloaded, it takes on an additional meaning relative to a certain class. But it can still retain
all of its old meanings.
Examples:
1 ) The operators >> and << may be used for I/O operations because in the <iostream> header, they are overloaded.
2 ) In a stack class it is possible to overload the + operattor so that it appends the contents of one stack to the
contents of another. But the + operator still retains its original meaning relative to other types of data.
Also Polymorphism can be achieved in C++ through operator overloading

25. What are templates?
C++ Templates allow u to generate families of functions or classes that can operate on a variety of different data
types, freeing you from the need to create a separate function or class for each type. Using templates, u have the
convenience of writing a single generic function or class definition, which the compiler automatically translates into
a specific version of the function or class, for each of the different data types that your program actually uses.

Many data structures and algorithms can be defined independently of the type of data they work with. You can increase
the amount of shared code by separating data-dependent portions from data-independent portions, and templates were
introduced to help you do that.

26. Type-define a function pointer which takes a int and float as parameter and returns a float *
typedef float*( *PF )(int , float );
and use PF as pointer to function.(  of one int argument, one floaat argument, returning float * ) like PF a;

27. How do you call a C module within a C++ module.
extern "C"
{
   #include <sys/types.h>
   #include <unistd.h>
   #include <sys/wait.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <whatever.h>
   ......
};

28. What is the difference between run time binding and compile time binding? Discuss.
Compile Time Binding: In case of operator overloading and function overloading the name of the function is resolved
during the compile time. Even if there are two or more functions with the same name the compiler mangles the name so
that each function is uniquely identified. This has to be resolved at compile time and is known as compile-time binding
or early binding.

Run Time Binding: In case of polymorphism ( virtual functions ) if a base class pointer (or reference) is allocated a
pointer ( or reference ) of derived class the actual function called is determined only during runtime through the
virtual table entry. This is runtime binding or late binding

29. Compare and contrast C++ and Java
1>Platform Independent: Java code is said to be a multiplatform code and can run on any platform because after the
compilation of the source code byte code( s ) are created rather than a binary code so it can run on any platform which
supports JVM concept but on the contrast at time( s ) it slows down the application tremendously
2> Garbage Collection: Java handles freeing up of the memory but this is not guranteed since the GC thread has the
lowest priority
3>Operator Overloading: is not provided in Java,but what are the advantages of Operator Overloading but one may
question what are its advantages, well it makes a more readable and a modular code. In c++ cin and cout objects can
also be overloaded which again leads to a better readability and flexibility
4> Multiple Inheritance: Java does provide multiple inheritance in form of Interfaces, In Java a class can not inherit
from more than one class but it definitely can implement any number of interfaces
5> Templates: in c++ give such a lot of flexibility and avoids redundant coding which again is not provided by Java

30. Why does C/C++ give better run-time performance then Java?
That's because the Java byte code is interpreted, not compiled. Programs written in C are compiled into binaries,\r
which can be executed by a specific computer processor. Programs written in Java require one more step -- they must be
interpreted by the Java "virtual machine" before running on particular computer architecture. As a result, a computer
running a Java program has to execute more machine-language instructions to do the same amount of work than a computer
running an equivalent program written in C.

31. Does C++ come with in-built threading support?
No. C++ does not support in-built Multithreading. To do so, you must use the operating system functions manually.

32. Class A derived B derived C. All have foo(  ). I cast C to A and call foo(). What happens?
If access is not specified, it defaults to private derivation. In private derivation, binding is static. So, whether
foo is declared virtual or not it still defaults to static binding. So, A->foo(  ) is called.

However, If a public derivation is specified from C <-- B and B <-- A, then if foo(  ) is virtual C->foo() is called; if
foo(  ) is non virtual A->foo() is called.

33. All classes A, B, C have default constructor, foo(  ) that calls parent foo() and allocates 100 bytes to their own
private local variable, and a destructor that frees the 100 bytes. I create a C object and then destroy it. What's the\r
problem? Did all the memory get freed? What if I create C, cast to A, and then destroy it. How would I make sure memory
is freed? ( destructor must be "virtual" and each destructor must call parent destructor )

In this case all memory will not be freed. To avoid this problem declare the destructor as Virtual.

34. What errors are caught at compile time vs link time?
Syntactical and semantically errors ( code errors ) are caught at compile time.

Dependency errors ( for example resolving function calls or errors in including other modules ) are caught at link time.

35. What is the value of "a" after this?
int ( *a ) [10];
a++;
int ( *a )[10]; represents the declaration of a pointer to an array of ten integers. So the value of a is initially some
address allocated by the compiler and don't rely on the fact the address is 0 as it happens for static variables. The\r
value can be zero if you add the "static" keyword in front of declaration but I don't advise you to further use this\r
pointer to access some elements.

If the integer is n bytes (  2 or 4 depending on the language ) it is true that the value of a will be increase with
10*n.
//
//Test this program to understand:
//
//#include <stdio.h>
//
//void main( int argc,char*argv[] )
//{
//int b[10]={1,2,3,4};
//int ( *a )[10];
//printf( "%p\n",a );
//printf( "%d\n",(*a )[0]);
//a++;
//printf( "%p\n",a );
//a=&b;
//printf( "%p\n",a );
//printf( "%d\n",(*a )[0]);
//}

36. What is wrong with this?
void main(  )
{
   int *ptr;
      *ptr=10;
}

Actual reality is like this. When the pointer is declared it contains some garbage value as u know. Conceptually
speaking it points to location indicated by that "garbage memory address". Now when we assign some value to *a ;
i.e. *a=12;  we are trying to place 12 in the memory cell number indicated by 'a' ; which in this case is any random
memory address because it is garbage. So the program will be compiled fine. But when run, if the garbage value assigned
to 'a' is invalid ( or restricted by OS ) memory address; the OS will generate error. So it is up to OS.

37. Given int n, i=10, j=20, x=3, y = 100;
What is the value of n and y at the end of each of the following expressions?
a ) n = ( i > j) && (x < ++y);
b ) n = ( j - i) && (x < y++);
c ) n = ( i < j)

1> n = 0, y = 100, second condition will not be evaluated.
2> n = 1, y = 101
3> n = 1, y = 100

38. int x = 5; int y = 7; What is the value of x and y after the expression y+=x++;
Y = 12 and X = 6, Why?
Because X will be incremented after y = Y+X has been carried out and result has been assigned to Y.

39. What's the difference between C and C++?\r
C does not have a class/object concept.
C++ provides data abstraction, data encapsulation, Inheritance and Polymorphism.
C++ supports all C syntax.
In C passing value to a function is "Call by Value" whereas in C++ it supports both "Call by Reference" and
¡°call by value¡±.
File extension is .c in C while .cpp in C++.( C++ compiler compiles the files with .c extension but C compiler can not! )
In C structures cannot have contain functions declarations. In C++ structures are like classes, so declaring functions
is legal and allowed.
C++ can have inline/virtual functions for the classes.
C is Top Down Approach; C++ is Bottom Up Programming approach.
C does not support OOP ( Object Oriented Programming ) and do not support Polymorphism, Inheritance, Encapsulation,
Function Overloading.
Some common C style commands and their corresponding C++ style commands are shown below.
Console I/O
***********
C
===
printf( "Hello World!\n" );
scanf( "%s", name );
C++
===
cout << "Hello World!" << endl;
cin >> name;

Comments
********
C
===
/* comment */
C++
===
// comment

File extensions
***************
C
===
.c, .h
C++
===
.C, .h, .CPP, .HPP

File I/O
*********
C
===
out = fopen( "output_file.dat", "wb" );
in = fopen( "input_file.dat", "rb" );
C++
===
ofstream out( "output_file.dat" );
ifstream in( "input_file.dat" );

Dynamic Memory
**************
C
===
text = ( char * ) malloc(1000);
free( text );
C++
===
text = new char[1000];
delete [] text;

Constants
*********
C
===
#define PI 3.14159
C++
===
const float PI = 3.14159;

Macros
******
C
===
#define MAX( a,b ) ((a) > (b) ? (a) : (b))
C++
===
inline int MAX( int a, int b ) { return a > b ? a : b; }
40. What does Public and Private mean in C++
Public:
Makes class members accessible outside the class. It can be accessed in the C code.
Private:
Makes the members specified accessible only to the class and it's functions.\r

41. Is it possible to keep 2 stacks in a single array, if one grows from position one of the array, and the other
grows from the last position. Write a procedure PUSH( x,s ) that pushes element x onto stack S, where S is one or the
other of these two stacks. Include all necessary error checks.
The question did not ask for a suggestion. It is definitely possible to implement 2 stacks using a single array. The
array should be visible to both stacks ( and therefore be global, or should provide equivalent effect ). Also the stack
tops should be taken care of. one top will decrement every time the push method is called and one would be incremented.
As soon as s1.top==s2.top we should throw an exception.

42. What is a virtual function in C++?
A virtual function is a function member of a class, declared using the "virtual" keyword. A pointer to a derived class
object may be assigned to a base class pointer, and a virtual function called through the pointer. If the function is
virtual and occurs both in the base class and in derived classes, then the right function will be picked up based on
what the base class pointer "really" points at.

43. What are testing procedures in your mind?
1.      understand the program
2.      cover new feature/code
3.      document the success and failure
4.      regression test: make sure old functions still work
5.      work closely with development engineer to identify any problems

44. Why do you want to work at our company?
Your company is one of the best companies to work for. There are a lot of most intelligent and enthusiastic people,
whom I would very much like to meet with and learn from. Most important reason is that this position matches my skill
and interest very well, and Microsoft is the leader in software industry. I am very interested in it and want to build
my career starting from it. I believe I can make distinct contribution and advance my knowledge and skills as well.
