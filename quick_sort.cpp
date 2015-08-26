void quickSort(int32_t a[], const uint32_t n) {
  if (n < 2)
    return;

  function<void(const uint32_t,const uint32_t)> solve =
    [&](const uint32_t left, const uint32_t right) {
    uint32_t i = left, j = right;
    const uint32_t pivot = a[(left+right)/2];

    /* partition */
    while (i < j+1) {
      while (a[i] < pivot)
        ++i;
      while (a[j] > pivot)
        --j;
      if (i < j+1) {
        int32_t tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        ++i;
        --j;
      }
    }

    if (left < j)
      solve(left, j);
    if (i < right)
      solve(i, right);
  };

  return solve(0, n-1);
}
