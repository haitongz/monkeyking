/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1).
You begin the journey with an empty tank at one of the gas stations.
Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.
Note:
The solution is guaranteed to be unique.
 */
#include <iostream>
#include <vector>

using namespace std;

int32_t canComplete(const vector<uint32_t>& gas, const vector<uint32_t>& costs) {
  const uint32_t n = gas.size();
  if (!n)
    return -1;

  for (uint32_t i = 0; i < n;) {
    int32_t left = 0;
    uint32_t j = 0;

    for (; j < n; ++j) {
      const uint32_t t = (i+j)%n;
      left += gas[t]-costs[t];
      if (left < 0)
        break;
    }

    if (j == n)
      return i;
    else
      i += j+1;
  }

  return -1;
}
/*
int32_t canCompleteCircuit(const vector<uint32_t>& gas, const vector<uint32_t>& cost) {
  const uint32_t n = gas.size(); // same as cost.size()
  if (!n)
    return -1;

  uint32_t i = 0, j = 0;
  uint32_t tank = 0;

  while (true) {
    if (j >= n) {
      return i;
    }

    uint32_t net;
    if (i+j >= n) {
      net = gas[i+j-n]-cost[i+j-n];
    } else {
      net = gas[i+j]-cost[i+j];
    }
    if (tank+net < 0) {
      ++j;
      i += j;
      if (i >= n) {
        return -1;
      }
      tank = 0;
      j = 0;
    } else {
      tank += net;
      ++j;
    }
  }
}
*/
int main(int argc, char** argv) {
}
