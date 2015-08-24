/*
Given an array of rooms with size n, thief Alibaba changes his room everyday but he can only move by 1 either left or right.
Use a strategy array to guess Alibaba's position, call it works when there's at least one bingo.
 */
#include <iostream>

using namespace std;

// O(n*k) time, O(n) space
bool alibaba(uint32_t strategy[], const uint32_t n) {
  // survival[i] means alibaba can be in spot i or not on this day
  bool survival[n+2];

  // init the first day
  // add one extra room at both start and end, to prevent j-1 and j+1 overflow
  for (auto& i : survival)
    i = true;

  survival[0] = false;
  survival[n+1] = false;
  survival[strategy[0]] = false;

  for (uint32_t i = 1; i < n; ++i) {
    for (uint32_t j = 1; j < n+1; ++j) {
      survival[j] = ((survival[j-1] || survival[j+1]) && strategy[i] != j) ? true : false;
    }
  }

  // survival array stores all rooms that thief might appear
  for (uint32_t i = 1; i < n+1; ++i) {
    if (survival[i]) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {
  return 0;
}
