#include <iostream>
#include <vector>

using namespace std;

/*
Given numRows, generate the first numRows of Pascal's triangle.

Given numRows = 5,
Return
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
/*
vector<vector<uint32_t> > genPascalsTriangle(const uint32_t num_rows) {
  vector<vector<uint32_t> > res;
  for (uint32_t i = 0; i < num_rows; ++i) {
    vector<uint32_t> curr(i+1, 1);
    if (res.size() > 0) {
      for (uint32_t j = 1; j < i; ++j)
        curr[j] = res.back()[j-1]+res.back()[j];
    }
    res.push_back(curr);
  }
  return res;
}
*/
vector<vector<uint32_t> > pascalsTriangle(const uint32_t row_num) {
  if (row_num < 1)
    return vector<vector<uint32_t> >();

  vector<vector<uint32_t> > res(1, vector<uint32_t>(1, 1));
  for (uint32_t i = 1; i < row_num; ++i) {
    res.push_back(vector<uint32_t>(1, 1));
    for (uint32_t j = 1; j < i; ++j) {
      res.back().push_back(res[i-1][j-1]+res[i-1][j]);
    }
    res.back().push_back(1);
  }

  return res;
}

/*
Given an index k, return the kth row of the Pascal's triangle.
For example, given k = 3,
Return [1,3,3,1].
Note:
Could you optimize your algorithm to use only O(k) extra space?
*/
vector<uint32_t> getKthRow(const uint32_t row) {
  vector<uint32_t> res(row+1, 1);
  if (row <= 1)
    return res;

  vector<uint32_t> tmp;
  for (uint32_t i = 1; i < row; ++i) {
    tmp = res;
    for (uint32_t j = 1; j <= i; ++j) {
      res[j] = tmp[j-1]+tmp[j];
    }
  }
  return res;
}

int main(int argc, char** argv) {
  vector<vector<uint32_t> > res = pascalsTriangle(5);
  for (uint32_t i = 0; i < res.size(); ++i) {
    for (uint32_t j = 0; j < res[i].size(); ++j) {
      cout << res[i][j] << ",";
    }
    cout << endl;
  }
}
