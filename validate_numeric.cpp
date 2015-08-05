/*
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
*/
#include <iostream>

using namespace std;

bool validateNumberic(const char* s) {
  enum InputType {
    INVALID,   // 0
    SPACE,     // 1
    SIGN,      // 2
    DIGIT,     // 3
    DOT,       // 4
    EXPONENT,  // 5
    NUM_INPUTS // 6
  };

  int8_t transit_table[][NUM_INPUTS] = {
    -1,  0,  3,  1,  2, -1, // state 0: initial no input or only spaces
    -1,  8, -1,  1,  4,  5, // state 1: after digit input
    -1, -1, -1,  4, -1, -1, // state 2: after no digit only dot input
    -1, -1, -1,  1,  2, -1, // state 3: after sign input
    -1,  8, -1,  4, -1,  5, // state 4: after digits and dot input
    -1, -1,  6,  7, -1, -1, // state 5: after 'e' or 'E' input
    -1, -1, -1,  7, -1, -1, // state 6: after 'e' and sign input
    -1,  8, -1,  7, -1, -1, // state 7: after 'e' and digit input
    -1,  8, -1, -1, -1, -1, // state 8: after space after valid digits input
  };

  int8_t state = 0;

  while (*s != '\0') {
    InputType type = INVALID;
    if (isspace(*s))
      type = SPACE;
    else if (*s == '+' || *s == '-')
      type = SIGN;
    else if (isdigit(*s))
      type = DIGIT;
    else if (*s == '.')
      type = DOT;
    else if (*s == 'e' || *s == 'E')
      type = EXPONENT;

    // Get next state from current state and input symbol
    state = transit_table[state][type];

    // Invalid input
    if (state == -1)
      return false;
    else
      ++s;
  }

  // If the current state belongs to one of the accepting (final) states,
  // then the number is valid
  return state == 1 || state == 4 || state == 7 || state == 8;
}

int main(int argc, char** argv) {
  std::string s = "0";
  std::cout << s << " is" << (validateNumberic(s.c_str()) ? " " : " not ") << "numberic!" << std::endl;
  s = " 0.1 ";
  std::cout << s << " is" << (validateNumberic(s.c_str()) ? " " : " not ") << "numberic!" << std::endl;
  s = "abc";
  std::cout << s << " is" << (validateNumberic(s.c_str()) ? " " : " not ") << "numberic!" << std::endl;
  s = "1 a";
  std::cout << s << " is" << (validateNumberic(s.c_str()) ? " " : " not ") << "numberic!" << std::endl;
  s = "2e10";
  std::cout << s << " is" << (validateNumberic(s.c_str()) ? " " : " not ") << "numberic!" << std::endl;
}
