#include <iostream>
#include <cstring>

using namespace std;

#define XOR_SWAP(a, b)\
do {\
  a ^= b;\
  b ^= a;\
  a ^= b;\
} while (0)

void reverse_iter(char* start, char* end) {
  while (start < end) {
    XOR_SWAP(*start, *end);
    ++start, --end;
  }
}

void reverse_recur(char** str) {
  if (!str)
    return;

  char* newStr = (char*)malloc(strlen(*str));

  function<void(const char*)> solve = [](const char* s) {
    if (*s) {
      reverse(s+1);
      newStr = *s;
    }
  };

  solve(*str);
  *str = newStr; // caller is responsible to free memory?
}

string trim(const string& str) { // trim both leading and trailing spaces
  size_t start = str.find_first_not_of(" \t");
  size_t end = str.find_last_not_of(" \t");

  // if all spaces or empty return an empty string
  return (string::npos == start || string::npos == end) ?
    "" : str.substr(start, end-start+1);
}

string missingLetters(const string& sentence) {
  if (sentence.empty())
    return "abcdefghigklmnopqrstuvwxyz";

  string otpt;
  char lower = 'a';
  char upper = 'A';

  for (; lower <= 'z'; ++lower, ++upper) {
    if (string::npos == sentence.find_first_of(lower) &&
        string::npos == sentence.find_first_of(upper)) {
      otpt += lower;
    }
  }

  return otpt;
}

int main(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    cerr << "IllegalArgument Exception!" << endl;
    return -1;
  }

  char* str = strdup(argv[1]);
  const uint16_t len = strlen(str);

  reverse(str, str+len-1);
  printf("Reversed input is: %s\n", str);

  string sentence = "A quick broWn foX jumps over the laZy dog";
  cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
    << missingLetters(sentence) << "\"" << endl;
  sentence = "A slow yellow fox craWls unDer the proactive dog";
  cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
    << missingLetters(sentence) << "\"" << endl;
  sentence = "Lions, and Tigers, and Bears, oh my!";
  cout << "Missing letters in sentence \"" << sentence << "\" are:\n\""
    << missingLetters(sentence) << "\"" << endl;

  string testStr = "\t   c,vnm,wojk234190adv,234!kfsf0&@^&@#(Q@&$kjdfkm,nvc,ekdfja.z.a[]wmncvmnwo9.120903,nmcvznme[qkl...   \t";
  cout << "Trimming " << testStr << endl;
  cout << trim(testStr) << endl;

  return 0;
}
