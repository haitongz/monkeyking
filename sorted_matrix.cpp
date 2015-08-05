#include <iostream>
#include <vector>
#include <functional>
#include <limits>

using namespace std;

static const int32_t MAX_LIMIT = numeric_limits<int32_t>::max();

/*
Given an nxn matrix, where every row and column is sorted in increasing order. Given a number x, how to decide whether this x is in the matrix. The designed algorithm should have linear time complexity.
 */
bool found(const vector<vector<int32_t>>& mat, const int32_t target) {
  const uint32_t n = mat.size();
  if (!n)
    return false;

  int32_t i = 0, j = n-1;  //set indexes for top right element

  while (i < n && j >= 0) {
    if (mat[i][j] == target) {
 //        printf("\n Found at %d, %d", i, j);
      return true;
    }
    if (mat[i][j] > target)
      --j;
    else // if mat[i][j] < target
      ++i;
  }

  //printf("\n Element not found");
  return false;  // if ( i==n || j== -1 )
}

/*
Write an efficient algorithm that searches for a value in an mxn matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

For example,
Consider the following matrix:
[
  [1,  3, 5, 7],
  [10,11,16,20],
  [23,30,34,50]
]
Given target = 3, return true.
 */
bool found2(const vector<vector<int32_t>>& mat, const int32_t target) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return false;

  uint32_t left = 0, right = n*m-1;
  while (left <= right) {
    const uint32_t mid = left+(right-left)/2;
    const int32_t curr = mat[mid/n][mid%n];
    if (curr > target){
      right = mid-1;
    } else if (curr < target) {
      left = mid+1;
    } else {
      return true;
    }
  }

  return false;
}

/*
Follow up:
How if the matrix has only one feature:
Integers in each row are sorted from left to right.
 */
bool found3(const vector<vector<int32_t>>& mat, const int32_t target) {
  const uint32_t m = mat.size();
  const uint32_t n = mat[0].size();
  if (!m || !n)
    return false;

  uint32_t row = 0;
  int32_t col = n-1;

  while (col >= 0 && row < m) {
    if (mat[row][col] > target)
      --col;
    else if (mat[row][col] < target)
      ++row;
    else
      return true;
  }

  return false;
}

/*
Given an nxn matrix, where every row and column is sorted in non-decreasing order. Print all values of matrix in sorted order.

Example:

Input: mat[][]  =  {{10, 20, 30, 40},
                    {15, 25, 35, 45},
                    {27, 29, 37, 48},
                    {32, 33, 39, 50}};

Output:
values of matrix in sorted order
10 15 20 25 27 29 30 32 33 35 37 39 40 45 48 50

Use a minheap of size N which stores values of first column. Then do extract minimum. In extract minimum, replace the minimum value with the next value of the row from which the value is extracted. Time complexity of this solution is O(N2LogN).
 */
struct MinHeapNode {
  int32_t value;
  uint32_t i, j; // indices
};

class MinHeap {
  vector<MinHeapNode> harr; // pointer to array of values in heap
  uint32_t size; // size of minheap

  public:
    MinHeap(vector<MinHeapNode>& a);

    // to heapify a subtree with root at given index
    void heapify(const uint32_t);

    // to get index of left child of node at index i
    uint32_t leftChildIdx(const uint32_t idx) { return (2*idx+1); }

    // to get index of right child of node at index i
    uint32_t rightChildIdx(const uint32_t idx) { return (2*idx+2); }

    // to get the root
    MinHeapNode getMin() { return harr[0]; }

    // to replace root with new node x and heapify() new root
    void replaceMin(MinHeapNode x) { harr[0] = x; heapify(0); }
};

// This function prints values of a given matrix in non-decreasing order. It assumes that ma[][] is sorted row wise sorted.
vector<int32_t> sorted(const vector<vector<int32_t>>& mat) {
  const uint32_t N = mat.size();
  if (!N)
    return {};

  // Create a min heap with k heap nodes. Every heap node has first value of an array
  vector<MinHeapNode> harr(N, MinHeapNode());

  for (uint32_t i = 0; i < N; ++i) {
    harr[i].value = mat[i][0]; // Store the first value
    harr[i].i = i; // index of row
    harr[i].j = 1; // Index of next value to be stored from row
  }

  MinHeap hp(harr); // Create the min heap
  vector<int32_t> ret;
  // Now one by one get the minimum value from minheap and replace it with next value of its array
  for (uint32_t count = 0; count < N*N; ++count) {
    // Get the minimum value and store it in output
    MinHeapNode root = hp.getMin();
    ret.push_back(root.value);

    // Find the next elvalue that will replace current root of heap. The next value belongs to same array as the current root.
    if (root.j < N) {
      root.value = mat[root.i][root.j];
      root.j += 1;
    } else // If root was the last value of its array
      root.value = MAX_LIMIT;

    // Replace root with next value of array
    hp.replaceMin(root);
  }

  return ret;
}

MinHeap::MinHeap(vector<MinHeapNode>& a)
    : harr(a), size(harr.size()) {
  int32_t i = (size-1)/2;
  while (i >= 0) {
    heapify(i);
    --i;
  }
}

// A recursive method to heapify a subtree with root at given index. This method assumes that the subtrees are already heapified
void MinHeap::heapify(const uint32_t idx) {
  uint32_t left = leftChildIdx(idx);
  uint32_t right = rightChildIdx(idx);
  uint32_t smallest = idx;

  if (left < size && harr[left].value < harr[idx].value)
    smallest = left;
  if (right < size && harr[right].value < harr[smallest].value)
    smallest = right;
  if (smallest != idx) {
    swap(harr[idx], harr[smallest]);
    heapify(smallest);
  }
}

int main(int argc, char** argv) {
  vector<vector<int32_t>> mat =
    {{10, 20, 30, 40},
     {15, 25, 35, 45},
     {27, 29, 37, 48},
     {32, 33, 39, 50}};

  vector<int32_t> res = sorted(mat);
  for (const auto& i : res)
    cout << i << " ";
  cout << endl;

  const int32_t x = 25;
  cout << x << (found(mat, x) ? " " : " not ") << "found in matrix." << endl;

  mat = {{1,3,5,7},
         {10,11,16,20},
         {23,30,34,50}};
  const int32_t v = 3;
  cout << v << (found3(mat, v) ? " found" : " not found") << " in matrix." << endl;
  cout << v << (found3(mat, v) ? " found" : " not found") << " in matrix." << endl;

  return 0;
}
