/*
Follow Up:
Let's change the function signature, suppose the input is only a integer N, please just print all power sets for {1,2,...,N}.
How can you reduce the memory usage?
 */
void printPowerSets(const uint n) {
  uint size = pow(2, n);

  // Run from i 000..0 to 111..1
  for (uint i = 0; i < size; ++i) {
    for (uint j = 0; j < n; ++j) {
      // Check if j-th bit in i is set. If set then pront j-th element from set
      if (i & (1 << j))
        cout << j+1 << " ";
    }
    cout << endl;
  }
}
