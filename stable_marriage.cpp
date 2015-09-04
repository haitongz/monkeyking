/*
Given N men and N women, where each person has ranked all members of the opposite sex
in order of preference, marry the men and women together such that there are no two people
of opposite sex who would both rather have each other than their current partners.
If there are no such people, all the marriages are 'stable'.
 */
/*
Gale-Shapley algorithm to find a stable matching:
The idea is to iterate through all free men while there is any free man available.
Every free man goes to all women in his preference list according to the order.
For every woman he goes to, he checks if the woman is free, if yes, they both become engaged.
If the woman is not free, then the woman chooses either says no to him or dumps her current
engagement according to her preference list. So an engagement done once can be broken if a woman
gets better option.
 */
#include <iostream>
#include <functional>

#define N 4

using namespace std;

// Prints stable matching for N boys and N girls. Boys are numbered as 0 to N-1. Girls are numbereed as N to 2N-1.
void stableMarriage(uint32_t prefer[2*N][N]) {
  // Stores partner of women. This is our output array that stores paing information.
  // The value of wPartner[i] indicates the partner assigned to woman N+i.
  // Note that the woman numbers between N and 2*N-1. The value -1 indicates that (N+i)'th woman is free
  int32_t wPartner[N];
  for (auto& i : wPartner)
    i = -1;

  bool mFree[N];
  for (auto& i : mFree)
    i = false;

  int32_t freemen = N;

  // This function returns true if woman 'w' prefers man 'm1' over man 'm'
  function<bool(const uint32_t,const uint32_t,const uint32_t)> preferOver =
    [&](const uint32_t w, const uint32_t m, const uint32_t m1) {
    // Check if w prefers m over her current engagment m1
    for (uint32_t i = 0; i < N; ++i) {
      // If m1 comes before m in lisr of w, then w prefers her cirrent engagement, don't do anything
      if (prefer[w][i] == m1)
        return true;
      // If m cmes before m1 in w's list, then free her current engagement and engage her with m
      if (prefer[w][i] == m)
        return false;
    }
  };

  // While there are free men
  while (freemen > 0) {
    // Pick the first free man (we could pick any)
    uint32_t m;
    for (m = 0; m < N; ++m)
      if (!mFree[m])
        break;

    // One by one go to all women according to m's preferences. Here m is the picked free man
    for (uint32_t i = 0; i < N && !mFree[m]; ++i) {
      uint32_t w = prefer[m][i];

      // The woman of preference is free, w and m become partners
      // (Note that the partnership maybe changed later).
      // So we can say they are engaged not married
      if (wPartner[w-N] == -1) {
        wPartner[w-N] = m;
        mFree[m] = true;
        --freemen;
      } else { // If w is not free
        // Find current engagement of w
        uint32_t m1 = wPartner[w-N];

        // If w prefers m over her current engagement m1, then break the engagement
        // between w and m1 and engage m with w.
        if (!preferOver(w, m, m1)) {
          wPartner[w-N] = m;
          mFree[m] = true;
          mFree[m1] = false;
        }
      } // End of Else
    } // End of the for loop that goes to all women in m's list
  } // End of main while loop

  // Print the solution
  cout << "Woman   Man" << endl;
  for (uint32_t i = 0; i < N; ++i)
    cout << " " << i+N << "\t" << wPartner[i] << endl;
}

int main(int argc, char** argv) {
  uint32_t prefer[2*N][N] =
    {{7, 5, 6, 4},
     {5, 4, 6, 7},
     {4, 5, 6, 7},
     {4, 5, 6, 7},
     {0, 1, 2, 3},
     {0, 1, 2, 3},
     {0, 1, 2, 3},
     {0, 1, 2, 3}};

  stableMarriage(prefer);
  return 0;
}
