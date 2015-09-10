/*
Imagine you have a special keyboard with the following keys:
Key 1: Prints 'A' on screen
Key 2: (Ctrl-A): Select screen
Key 3: (Ctrl-C): Copy selection to buffer
Key 4: (Ctrl-V): Print buffer on screen appending it
                 after what has already been printed.

If you can only press the keyboard for N times (with the above four
keys), write a program to produce maximum numbers of A's. That is to
say, the input parameter is N (No. of keys that you can press), the
output is M (No. of As that you can produce).

Input:  N = 3
Output: 3

We can at most get 3 A's on screen by pressing following key sequence:
A, A, A
 */
#include <iostream>

using namespace std;

uint32_t optimal(const uint32_t n) {
  if (n <= 6) // optimal string length is n when n < 7
    return n;

  uint32_t dp[n];
  for (uint8_t i = 1; i < 7; ++i)
    dp[i-1] = i;

  // Solve all subproblems in bottom manner
  for (uint32_t i = 7; i < n+1; ++i) {
    dp[i-1] = 0;

    // For any keystroke i, we need to loop from i-3 keystrokes
    // back to 1 keystroke to find a breakpoint 'j' after which
    // we will have ctrl-a, ctrl-c and then only ctrl-v all the way.
    for (uint32_t j = i-3; j >= 1; --j) {
      // if the breakpoint is at j-th keystroke then the optimal string
      // would have length (i-j-1)*dp[j-1];
      uint32_t curr = (i-j-1)*dp[j-1];
      dp[i-1] = max(curr, dp[i-1]);
    }
  }

  return dp[n-1];
}

int main(int argc, char** argv) {
  for (uint32_t i = 1; i < 21; ++i)
    cout << "Maximum number of A's with "
      << i << " keystrokes is " << optimal(i) << endl;

  return 0;
}
