/*
Inversion Count for an array indicates ¿ how far (or close) the array is from being sorted. If array is already sorted then inversion count is 0. If array is sorted in reverse order that inversion count is the maximum.

Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j.

O(nlogn)
 */
/* This funt merges two sorted arrays and returns inversion count in the arrays.*/
uint32_t merge(int32_t a[], int32_t temp[], const uint32_t left, const uint32_t mid, const uint32_t right) {
  uint32_t inv_cnt = 0;
  uint32_t i = left; /* i is index for left subarray*/
  uint32_t j = mid;  /* i is index for right subarray*/
  uint32_t k = left; /* i is index for resultant merged subarray*/
  while (i < mid && j < right+1) {
    if (a[i] <= a[j]) {
      temp[k++] = a[i++];
    } else {
      temp[k++] = a[j++];
      /*this is tricky -- see above explanation/diagram for merge()*/
      inv_cnt += mid-i;
    }
  }

  /* Copy the remaining elements of left subarray (if there are any) to temp*/
  while (i < mid)
    temp[k++] = a[i++];

  /* Copy the remaining elements of right subarray (if there are any) to temp*/
  while (j < right+1)
    temp[k++] = arr[j++];

  /*Copy back the merged elements to original array*/
  for (i = left; i < right+1; ++i)
    a[i] = temp[i];

  return inv_count;
}

int32_t mergeSort(const int32_t a[], const uint32_t n) {
  if (!n)
    return -1;

  int32_t temp[n];

  function<uint32_t(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t left, const uint32_t right) {
    uint32_t mid, inv_cnt = 0;
    if (right > left) {
      /* Divide the array into two parts and call _mergeSortAndCountInv() for each of the parts */
      mid = (right+left)/2;

      /* Inversion count will be sum of inversions in left-part, right-part and number of inversions in merging */
      inv_cnt = solve(left, mid);
      inv_cnt += solve(mid+1, right);

      /*Merge the two parts*/
      inv_cnt += merge(a, temp, left, mid+1, right);
    }

    return inv_cnt;
  };

  return solve(0, size-1);
}

int main(int argv, char** args) {
  int a[] = {1, 20, 6, 4, 5};
  cout << "Number of inversions are " << mergeSort(a, 5) << endl;
  return 0;
}
