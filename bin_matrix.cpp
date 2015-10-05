#include <iostream>
#include <functional>
#include <vector>

using namespace std;

/*
Given a boolean 2D array, where each row is sorted. Find the row with the maximum number of 1s.

Input matrix
0 1 1 1
0 0 1 1
1 1 1 1  // this row has maximum 1s
0 0 0 0

Output: 2

Step1: Get the index of first (or leftmost) 1 in the first row.
Step2: Do following for every row after the first row:
...IF the element on left of previous leftmost 1 is 0, ignore this row.
...ELSE Move left until a 0 is found. Update the leftmost index to this index and result to be the current row.

The time complexity is O(m+n) because we can possibly go as far left as we came ahead in the first step.
 */
int32_t first(const vector<uint8_t>& A) {
  function<int32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t start, const uint32_t end) -> int32_t {
    if (end >= start) {
      uint32_t mid = start+(end-start)/2;

      // check if the element at middle index is first 1
      if ((!mid || !A[mid-1]) && A[mid] == 1)
        return mid;
      else if (!A[mid]) // if the element is 0, recur for right side
        return solve(mid+1, end);
      else // If element is not first 1, recur for left side
        return solve(start, mid-1);
    }

    return -1;
  };

  return solve(0, A.size()-1);
}

uint32_t rowWithMax1s(const vector<vector<uint8_t>>& mat) {
  const uint32_t M = mat.size(), N = mat[0].size();
  if (!M || !N)
    return {};

  uint32_t ret = 0;

  // The function first() returns index of first 1 in row 0, use this index to initialize the index of leftmost 1 seen so far
  int32_t j = first(mat[0])-1;
  if (j == -1) // if 1 is not present in first row
    j = N-1;

  for (uint32_t i = 1; i < M; ++i) {
    // Move left until a 0 is found
    while (j >= 0 && mat[i][j] == 1) {
      j = j-1; // Update the index of leftmost 1 seen so far
      ret = i; // Update max_row_index
    }
  }

  return ret;
}

/*
Given a boolean matrix mat[M][N] of size MXN, modify it such that if a matrix cell mat[i][j] is 1 (or true) then make all the cells of ith row and jth column as 1.
 */

/*
Given a binary matrix, print all unique rows of the given matrix.

Since the matrix is boolean, a variant of Trie data structure can be used where each node will be having two children one for 0 and the other for 1. Insert each row in the Trie. If the row is already there, don't print the row. If row is not there in Trie, insert it in Trie and print it.

Time complexity: O(m*n)
Auxiliary Space: O(m*n)
 */
struct TrieNode
{
  bool eoc; // end of column
  TrieNode* children[2]; // Only two children needed for 0 and 1
};

// Inserts a new matrix row to Trie.  If row is already present, then returns 0, otherwise insets the row and return 1
bool insert(TrieNode** root, int (*M)[COL], int row, int col ) {
  // base case
  if (!*root)
    *root = newNode();

  // Recur if there are more entries in this row
  if (col < COL)
    return insert ( &( (*root)->child[ M[row][col] ] ), M, row, col+1 );
  else { // If all entries of this row are processed
    // unique row found, return 1
    if ( !( (*root)->isEndOfCol ) )
      return (*root)->isEndOfCol = 1;

    // duplicate row found, return 0
    return 0;
  }
}

void printRow( int (*M)[COL], int row )
{
    int i;
    for( i = 0; i < COL; ++i )
        printf( "%d ", M[row][i] );
    printf("\n");
}

// The main function that prints all unique rows in a given matrix.
void uniqueRows( int (*M)[COL] )
{
    Node* root = NULL; // create an empty Trie
    int i;

    // Iterate through all rows
    for ( i = 0; i < ROW; ++i )
        // insert row to TRIE
        if ( insert(&root, M, i, 0) )
            // unique row found, print it
            printRow( M, i );
}

int main(int argc, char** argv) {
  vector<vector<uint8_t>> mat =
    {{0, 1, 1, 1},
     {0, 0, 1, 1},
     {1, 1, 1, 1},
     {0, 0, 0, 0}};

  cout << rowWithMax1s(mat) << endl;

  int M[ROW][COL] = {{0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0}
    };

  uniqueRows(M);

  return 0;
}
