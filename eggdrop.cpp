/*
Suppose that we wish to know which story in a k-story building are safe to drop eggs from, and which will cause the eggs
to break on landing. We make a few assumptions:
An egg that survives a fall can be used again.
A broken egg must be discarded.
The effect of a fall is the same for all eggs.
If an egg breaks when dropped, then it would break if dropped from a higher floor.
If an egg survives a fall then it would survive a shorter fall.

It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the kth-floor do not cause an egg to break.
If only one egg is available and we wish to be sure of obtaining the right result, the experiment can be carried out
in only one way. Drop the egg from the first-floor window; if it survives, drop it from the second floor window.
Continue upward until it breaks. In the worst case, this method may require k droppings.
Suppose n eggs are available. What is the least number of egg-droppings that is guaranteed to work in all cases?
 */
#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

static const uint32_t MAX_LMT = numeric_limits<uint32_t>::max();

uint32_t eggdrop_dp(const uint32_t egg_num, const uint32_t story_num) {
  if (!egg_num || !story_num)
    throw exception();
  else if (story_num == 1 || egg_num == 1)
    return story_num;

  vector<vector<uint32_t>> dp(egg_num+1, vector<uint32_t>(story_num+1, 0));
  // We need one trial for one floor and 0 trials for 0 floors
  for (uint32_t i = 1; i < egg_num+1; ++i) {
    dp[i][0] = 0;
    dp[i][1] = 1;
  }
  // We always need j trials for one egg and j floors.
  for (uint32_t i = 1; i < story_num+1; ++i)
    dp[1][i] = i;

  for (uint32_t i = 2; i < egg_num+1; ++i) {
    for (uint32_t j = 2; j < story_num+1; ++j) {
      dp[i][j] = MAX_LMT;

      for (uint32_t k = 1; k < j+1; ++k) {
        const uint32_t tmp = 1 + max(dp[i-1][k-1], dp[i][j-k]);
        // 1) If the egg breaks after dropping from k-th floor,
        //    then we only need to check for floors lower than k with remaining eggs
        //    so the problem reduces to k-1 floors and n-1 eggs;
        // 2) If the egg doesn't break after dropping from the k-th floor,
        //    then we only need to check for floors higher than k so the problem reduces to j-k floors and n eggs.
        dp[i][j] = min(dp[i][j], tmp);
      }
    }
  }

  return dp[egg_num][story_num];
}

uint32_t eggdrop_recur(const uint32_t n, const uint32_t k) {
  function<uint32_t(const uint32_t,const uint32_t)> solve = // DFS
    [&](const uint32_t egg_num, const uint32_t story_num) {
    if (story_num == 1 || story_num == 0)
      return story_num;
    if (egg_num == 1)
      return story_num;

    uint32_t ret = MAX_LMT;

    for (uint32_t i = 1; i < story_num+1; ++i) {
      uint32_t tmp = max(solve(egg_num-1, i-1), solve(egg_num, story_num-i));
      ret = min(ret, tmp);
    }

    return ret+1;
  };

  return solve(n, k);
}

int main(int argc, char** argv) {
  uint32_t egg_num = 2, story_num = 100;

  cout << "DP: minimum number of trials with " << egg_num << " eggs and " << story_num << " floors: "
       << eggdrop_dp(egg_num, story_num) << endl;
 // cout << "Recursive: minimum number of trials with " << egg_num << " eggs and " << story_num << " floors: " << eggdrop_recur(egg_num, story_num) << endl;
  return 0;
}
