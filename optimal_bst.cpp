/*
Given a sorted array keys[0.. n-1] of search keys and an array freq[0.. n-1] of frequency counts,
where freq[i] is the number of searches to keys[i]. Construct a binary search tree of all keys such that
the total cost of all the searches is as small as possible.
Let us first define the cost of a BST. The cost of a BST node is level of that node multiplied by its frequency.
Level of root is 1.

Input:  keys[] = {10, 12}, freq[] = {34, 50}
There can be following two possible BSTs
        10                       12
          \                     /
           12                 10
          I                     II
Frequency of searches of 10 and 12 are 34 and 50 respectively.
The cost of tree I is 34*1 + 50*2 = 134
The cost of tree II is 50*1 + 34*2 = 118

Input: keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
There can be following possible BSTs
    10                12                 20         10              20
      \             /    \              /             \            /
      12          10     20           12               20         10
        \                            /                 /           \
         20                        10                12             12
     I               II             III             IV             V
Among all possible BSTs, cost of the fifth BST is minimum: 1*50 + 2*34 + 3*8 = 142
 */
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

static const uint32_t max_lmt = numeric_limits<uint32_t>::max();

vector<vector<uint32_t>> sumTable(const vector<uint32_t>& freq) {
  const uint32_t n = freq.size();
  // if (!n) // size should've been checked already
  // return {{}};

  vector<vector<uint32_t>> dp(n, vector<uint32_t>(n, max_lmt));

  for (uint32_t i = 0; i < n; ++i) {
    dp[i][i] = freq[i];
  }
  for (uint32_t i = 0; i < n; ++i) {
    for (uint32_t j = i+1; j < n; ++j) {
      dp[i][j] = dp[i][j-1]+freq[j];
    }
  }

  return dp;
}

uint32_t optimalBSTCost(const vector<uint32_t>& keys,
                        const vector<uint32_t>& freq) {
  const uint32_t n = keys.size();
  if (!n)
    throw exception();

  vector<vector<uint32_t>> dp(n, vector<uint32_t>(n, max_lmt));
  for (uint32_t i = 0; i < n; ++i) {
    dp[i][i] = freq[i];
  }

  vector<vector<uint32_t>> sum_tbl = sumTable(freq);
  for (uint32_t d = 2; d <= n; ++d) {
    uint32_t i = 0, j = d-1;

    for (uint32_t r = 0; r <= n-d; ++r, ++i, ++j) {
      for (uint32_t k = i; k < d; ++k) {
        uint32_t t = (k > i ? dp[i][k-1] : 0) + (k < j ? dp[k+1][j] : 0) + sum_tbl[i][j];
        dp[i][j] = min(dp[i][j], t);
      }
    }
  }

  return dp[0][n-1];
}

int main() {
  vector<uint32_t> keys = {10, 12, 20};
  vector<uint32_t> freq = {34, 8, 50};

  cout << "Cost of optimal BST: " << optimalBSTCost(keys, freq) << endl;
  return 0;
}
