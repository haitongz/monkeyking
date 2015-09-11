/*
Given N jobs where every job is represented by following three elements of it.
1) Start Time
2) Finish Time.
3) Profit or Value Associated.

Find the maximum profit subset of jobs such that no two jobs in the subset overlap.

Input: Number of Jobs n = 4
       Job Details {Start Time, Finish Time, Profit}
       Job 1:  {1, 2, 50}
       Job 2:  {3, 5, 20}
       Job 3:  {6, 19, 100}
       Job 4:  {2, 100, 200}
Output: The maximum profit is 250.
 */
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Job {
  uint32_t start, finish, profit;
};

// Find the latest job (in sorted array) that doesn't
// conflict with the job[i]. If there is no compatible job,
// then it returns -1.
int32_t latestNonConflict(const vector<Job>& jobs, const uint32_t n) {
  for (int32_t i = n-1; i >= 0; --i) {
    if (jobs[i].finish <= jobs[n-1].start)
      return i;
  }

  return -1;
}

uint32_t maxProfit(vector<Job>& jobs) {
  const uint32_t n = jobs.size();
  if (!n)
    return 0;

  sort(jobs.begin(), jobs.end(),
       [](const Job& a, const Job& b) { return a.finish < b.finish; });

  function<uint32_t(const uint32_t)> solve = [&](const uint32_t m) {
    if (m == 1)
      return jobs[0].profit;

    uint32_t inclProf = jobs[m-1].profit; // profit when current job is inclueded
    uint32_t i = latestNonConflict(jobs, m);
    if (i != -1)
      inclProf += solve(i+1);
    uint32_t exclProf = solve(m-1); // profit when current job is excluded

    return max(inclProf, exclProf);
  };

  return solve(n);
}

int main(int argc, char** argv) {
  vector<Job> a = {{3, 5, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
  cout << "Optimal profit is " << maxProfit(a) << endl;

  return 0;
}
