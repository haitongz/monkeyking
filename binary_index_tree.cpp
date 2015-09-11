#include <iostream>

using namespace std;

/*
We have an array a[0...n-1]. We should be able to
1. Find the sum of first i elements;
2. Change value of a specified element of the array a[i] = x where 0 <= i <= n-1;

Using Binary Indexed Tree, we can do both tasks in O(logn) time.
The advantages of Binary Indexed Tree over Segment are, requires less space and very easy to implement.
 */
// Updates a node in Binary Index Tree (BITree) at given index in BITree.
// The given value is added to BITree[i] and all of its ancestors in tree.
void updateBIT(int32_t BITree[], const uint32_t n,
               uint32_t index, const int32_t value) {
  // index in BITree[] is 1 more than the index in arr[]
  index += 1;

  while (index <= n) { // Traverse all ancestors and add value
    BITree[index] += value; // add value to current node
    // Update index to that of parent
    index += index & (-index);
  }
}

// Constructs and returns a Binary Indexed Tree for given array of size n.
int32_t* constructBITree(const int32_t a[], const uint32_t n) {
  int32_t* BITree = new int32_t[n+1];
  for (uint32_t i = 0; i < n+2; ++i)
    BITree[i] = 0;

  // Store the actual values in BITree[] using update()
  for (uint32_t i = 0; i < n; ++i)
    updateBIT(BITree, n, i, a[i]);

  // Uncomment below lines to see contents of BITree[]
    //for (int i=1; i<=n; i++)
    //      cout << BITree[i] << " ";

  return BITree;
}

// Returns sum of a[0...index].
// This function assumes that the array is preprocessed and partial sums
// of array elements are stored in a[].
int32_t getSum(const int32_t a[], const uint32_t n, uint32_t index) {
  // index in BITree[] is 1 more than the index in a[]
  index += 1;

  int32_t ret = 0; // Iniialize result

  // Traverse ancestors of BITree[index]
  while (index > 0) {
    // Add current element of BITree to sum
    ret += a[index];

    // Move index to parent node
    index -= index & (-index);
  }

  return ret;
}

int main(int argc, char** argv) {
  int32_t freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  const uint32_t n = sizeof(freq)/sizeof(freq[0]);

  int32_t* BITree = constructBITree(freq, n);
  cout << "Sum of elements in A[0...5] is " << getSum(BITree, n, 5) << endl;

  // Let use test the update operation
  freq[3] += 6;
  updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[]

  cout << "Sum of elements in A[0...5] after update is " << getSum(BITree, n, 5) << endl;
  return 0;
}
