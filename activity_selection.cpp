/*
Given n activities with their start and finish times. Select the maximum number of activities that can be performed
by a single person, assuming that a person can only work on a single activity at a time.

Consider the following 6 activities.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};

The maximum set of activities that can be executed by a single person is {0, 1, 3, 4}
 */
#include <iostream>

using namespace std;

void printMaxActivities(const uint32_t start[], const uint32_t finish[], const uint32_t n) {
  cout << "Following activities are selected:" << endl;

  // The first activity always gets selected
  uint32_t i = 0;
  cout << i << " ";

  // Consider rest of the activities
  for (uint32_t j = 1; j < n; ++j) {
    // If this activity has start time greater than or equal to the finish time of
    // previously selected activity, then select it
    if (start[j] >= finish[i]) {
      cout << j << " ";
      i = j;
    }
  }
}
