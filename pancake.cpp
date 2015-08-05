/*
Given an unsorted array, sort the given array. You are allowed to do only following operation on array.

flip(arr, i): Reverse array from 0 to i

Unlike a traditional sorting algorithm, which attempts to sort with the fewest comparisons possible, the goal is to sort the sequence in as few reversals as possible.
 */
void flip(int32_t a[], const uint32_t idx) {
  int32_t tmp, start = 0;

  while (start < idx) {
    tmp = a[start];
    a[start] = a[idx];
    a[idx] = tmp;
    ++start;
    --idx;
  }
}

/* Returns index of the maximum element in a[0..n-1] */
uint32_t maxElemIdx(const int32_t a[], const uint32_t n) {
  uint32_t ret = 0;

  for (uint32_t i = 0; i < n; ++i)
    if (a[i] > a[ret])
      ret = i;

  return ret;
}

// The main function that sorts given array using flip operations
int pancakeSort(int32_t *a, const uint32_t n) {
  // Start from the complete array and one by one reduce current size by one
  for (uint32_t curr_size = n; curr_size > 1; --curr_size) {
    // Find index of the maximum element in arr[0..curr_size-1]
    uint32_t mi = maxElemIdx(a, curr_size);

    // Move the maximum element to end of current array if it's not already at the end
    if (mi != curr_size-1) {
      // To move at the end, first move maximum number to beginning
      flip(a, mi);

      // Now move the maximum number to end by reversing current array
      flip(a, curr_size-1);
    }
  }
}

/*
Imagine a hypothetical machine where flip(i) always takes O(1) time. Write an efficient program for sorting a given array in O(nLogn) time on the given machine.
 */
int32_t ceilSearch(int32_t a[], const uint32_t low, const uint32_t high, const int32_t x) {
    int mid;
 
    /* If x is smaller than or equal to the first element,
      then return the first element */
    if(x <= arr[low])
        return low;
 
    /* If x is greater than the last element, then return -1 */
    if(x > arr[high])
        return -1;
 
    /* get the index of middle element of arr[low..high]*/
    mid = (low + high)/2;  /* low + (high ¿ low)/2 */
 
    /* If x is same as middle element, then return mid */
    if(arr[mid] == x)
        return mid;
 
    /* If x is greater than arr[mid], then either arr[mid + 1]
      is ceiling of x, or ceiling lies in arr[mid+1...high] */
    if(arr[mid] < x)
    {
        if(mid + 1 <= high && x <= arr[mid+1])
            return mid + 1;
        else
            return ceilSearch(arr, mid+1, high, x);
    }
 
    /* If x is smaller than arr[mid], then either arr[mid]
       is ceiling of x or ceiling lies in arr[mid-1...high] */
    if (mid - 1 >= low && x > arr[mid-1])
        return mid;
    else
        return ceilSearch(arr, low, mid - 1, x);
}

/* Function to sort an array using insertion sort, binary search and flip */
void insertionSort(int arr[], int size)
{
    int i, j;
 
    // Start from the second element and one by one insert arr[i]
    // in already sorted arr[0..i-1]
    for(i = 1; i < size; i++)
    {
        // Find the smallest element in arr[0..i-1] which is also greater than
        // or equal to arr[i]
        int j = ceilSearch(arr, 0, i-1, arr[i]);
 
        // Check if there was no element greater than arr[i]
        if (j != -1)
        {
            // Put arr[i] before arr[j] using following four flip operations
            flip(arr, j-1);
            flip(arr, i-1);
            flip(arr, i);
            flip(arr, j);
        }
    }
}
