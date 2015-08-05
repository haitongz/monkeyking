/*
Given two unsorted arrays that represent two sets (elements in every array are distinct), find union and intersection of two arrays.

Using sorting and searching

Union:
1) Initialize union U as empty.
2) Find smaller of m and n and sort the smaller array.
3) Copy the smaller array to U.
4) For every element x of larger array, do following
...b) Binary Search x in smaller array. If x is not present, then copy it to U.
5) Return U.

Intersection:
1) Initialize intersection I as empty.
2) Find smaller of m and n and sort the smaller array.
3) For every element x of larger array, do following
...b) Binary Search x in smaller array. If x is present, then copy it to I.
4) Return I.

Time complexity of this method is min(mLogm + nLogm, mLogn + nLogn) which can also be written as O((m+n)Logm, (m+n)Logn). This approach works much better than the previous approach when difference between sizes of two arrays is significant.
 */

vector<int32_t> Union(int32_t a1[], int32_t a2[], const uint32_t m, const uint32_t n) {
  if (m > n) {
    vector<int32_t> tmp(a1);
    a1 = a2;
    a2 = tmp;

    uint32_t temp = m;
    m = n;
    n = temp;
  }

  vector<int32_t> ret;
  // Now arr1[] is smaller
  // Sort the first array and print its elements (these two steps can be swapped as order in output is not important)
  sort(a1, a1+m);
  for (const auto& i : a1)
    ret.push_back(i);

  // Search every element of bigger array in smaller array and print the element if not found
  for (uint32_t i = 0; i < n; ++i)
    if (binarySearch(a1, 0, m-1, a2[i]) == -1)
      ret.push_back(a2[i]);

  return ret;
}

// Prints intersection of arr1[0..m-1] and arr2[0..n-1]
void Intersection(const int32_t a1[], const int32_t a2[], const uint32_t m, const uint32_t n) {
  // Before finding intersection, make sure arr1[0..m-1] is smaller
  if (m > n) {
    int *tempp = a1;
    a1 = a2;
    a2 = tempp;

    int temp = m;
    m = n;
    n = temp;
  }

  // Now arr1[] is smaller

  // Sort smaller array a1[0..m-1]
  sort(a1, a1+m);

  // Search every element of bigger array in smaller array and print the element if found
  for (uint32_t i = 0; i < n; ++i)
    if (binarySearch(a1, 0, m-1, a2[i]) != -1)
      ret.push_back(a2[i]);
}

// A recursive binary search function. It returns location of x in
// given array arr[l..r] is present, otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        // If the element is present at the middle itself
        if (arr[mid] == x)  return mid;

        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present in right subarray
        return binarySearch(arr, mid+1, r, x);
    }

    // We reach here when element is not present in array
    return -1;
}

/* Driver program to test above function */
int main()
{
    int arr1[] = {7, 1, 5, 2, 3, 6};
    int arr2[] = {3, 8, 6, 20, 7};
    int m = sizeof(arr1)/sizeof(arr1[0]);
    int n = sizeof(arr2)/sizeof(arr2[0]);
    cout << "Union of two arrays is \n";
    printUnion(arr1, arr2, m, n);
    cout << "\nIntersection of two arrays is \n";
    printIntersection(arr1, arr2, m, n);
    return 0;
}
