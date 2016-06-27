/*
Given an unsorted array that contains even number of occurrences for all numbers except two numbers.
Find the two numbers which have odd occurrences in O(n) time complexity and O(1) extra space.
 */
pair<int,int> twoOdd(const int a[], const uint n) {
  if (!n) {
    return {-1,-1};
  }

  int xor2 = a[0]; /* Will hold XOR of two odd occurring elements */
  uint setBitNo = 0;  /* Will have only single set bit of xor2 */
 // int n = size - 2;
  int x = 0, y = 0;

  /* Get the xor of all elements in arr[]. The xor will basically be xor of two odd occurring elements */
  for (uint i = 1; i < n; ++i) {
    xor2 ^= a[i];
  }

  /* Get one set bit in the xor2. We get rightmost set bit in the following line as it is easy to get */
  setBitNo = xor2 & ~(xor2-1);

  /* Now divide elements in two sets:
    1) The elements having the corresponding bit as 1.
    2) The elements having the corresponding bit as 0.  */
  for (uint i = 0; i < n; ++i) {
    /* XOR of first set is finally going to hold one odd occurring number x */
    if (a[i] & set_bit_no) {
      x ^= a[i];
    } else { /* XOR of second set is finally going to hold the other odd occurring number y */
      y ^= a[i];
    }
  }

  return {x, y};
}
