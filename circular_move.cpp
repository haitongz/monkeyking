/*
Given a sequence of moves for a robot, check if the sequence is circular or not. A sequence of moves is circular
if first and last positions of robot are same. A move can be on of the following:
  G - Go one unit
  L - Turn left
  R - Turn right
 */
#include <iostream>

using namespace std;

bool isCircular(const char seq[], const uint32_t N) {
  // Initialize starting point for robot as (0, 0) and starting direction as N North
  uint32_t x = 0, y = 0;
  uint32_t dir = N;

  for (uint32_t i = 0; seq[i]; ++i) {
    char move = seq[i];
    if (move == 'R') // If move is left or right, then change direction
      dir = (dir+1)%4;
    else if (move == 'L')
      dir = (4+dir-1)%4;
    else { // if (move == 'G')
      // If move is Go, then change x or y according to current direction
      if (dir == N)
        ++y;
      else if (dir == E)
        ++x;
      else if (dir == S)
        --y;
      else // dir == W
        --x;
    }
  }

  // If robot comes back to (0, 0), then path is cyclic
  return (x == 0 && y == 0);
}

int main(int argc, char** argv) {
}
