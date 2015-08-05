/*
Given a number line from -infinity to +infinity. You start at 0 and can go either to the left or to the right. The condition is that in i-th move, you take i steps.
a) Find if you can reach a given number x
b) Find the most optimal way to reach a given number x, if we can indeed reach it. For example, 3 can be reached om 2 steps, (0, 1) (1, 3) and 4 can be reached in 3 steps (0, -1), (-1, 1) (1, 4).
 */
#include <iostream>

using namespace std;

uint32_t minSteps(const int32_t dst) {
  function<uint32_t(const int32_t,const uint32_t)> solve =
    [&](const int32_t curr_src, const uint32_t curr_steps) {
    if (abs(curr_src) > dst)
      return MAX_LIMIT;

    if (curr_src == dst)
      return curr_steps;

    // if we go on positive side
    uint32_t pos = solve(curr_src+curr_steps+1, curr_steps+1);
    // if we go on negative side
    uint32_t neg = solve(curr_src-curr_steps-1, curr_steps+1);

    // minimum of both cases
    return min(pos, neg);
  };

  uint32_t ret = solve(0, 1);
  if (ret == MAX_LIMIT)
    cerr << "Cannot reach destination!" << endl;
  else
    return ret;
}
