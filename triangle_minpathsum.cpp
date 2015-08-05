/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

Given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
 */
#include <iostream>
#include <vector>

using namespace std;

int32_t minPathSum(const vector<vector<int32_t> >& triangle) {
  const uint32_t lvls = triangle.size();
  if (!lvls)
    throw exception();

  int32_t dp[lvls+1];
  for (uint32_t i = 0; i <= lvls; ++i)
    dp[i] = 0;

  for (int32_t i = lvls-1; i >= 0; --i) {
    for (uint32_t j = 0; j < triangle[i].size(); ++j) {
      dp[j] = triangle[i][j] + min(dp[j], dp[j+1]); // for the bottom level, b[j] == triangle[i][j]
    }
  }

  return dp[0];
}

int main(int argc, char** argv) {
  vector<vector<int32_t> > triangle;
  vector<int32_t> v;
  v.push_back(2);
  triangle.push_back(v);
  v.clear();
  v.push_back(3);
  v.push_back(4);
  triangle.push_back(v);
  v.clear();
  v.push_back(6);
  v.push_back(5);
  v.push_back(7);
  triangle.push_back(v);
  v.clear();
  v.push_back(4);
  v.push_back(1);
  v.push_back(8);
  v.push_back(3);
  triangle.push_back(v);

  cout << "Minimum path sum: " << minPathSum(triangle) << endl;
}
