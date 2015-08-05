/*
There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 */
#include <iostream>
#include <functional>

using namespace std;

/*
O(logn)

1) Calculate the medians m1 and m2 of the input arrays ar1[] and ar2[] respectively.
2) If m1 and m2 both are equal then we are done, return m1 (or m2)
3) If m1 is greater than m2, then median is present in one of the below two subarrays.
    a)  From first element of ar1 to m1 (ar1[0...|_n/2_|])
    b)  From m2 to last element of ar2  (ar2[|_n/2_|...n-1])
4) If m2 is greater than m1, then median is present in one of the below two subarrays.
   a)  From m1 to last element of ar1  (ar1[|_n/2_|...n-1])
   b)  From first element of ar2 to m2 (ar2[0...|_n/2_|])
5) Repeat the above process until size of both the subarrays becomes 2.
6) If size of the two arrays is 2 then use below formula to get the median.
    Median = (max(ar1[0], ar2[0]) + min(ar1[1], ar2[1]))/2
 */
int32_t median(const vector<int32_t>& arr1, const vector<int32_t>& arr2) {
  const uint32_t n = ar1.size();
  if (!n)
    return -1;

  int32_t m1, m2;

  /* return -1  for invalid input */
    if (n <= 0)
        return -1;
 
    if (n == 1)
        return (ar1[0] + ar2[0])/2;
 
    if (n == 2)
        return (max(ar1[0], ar2[0]) + min(ar1[1], ar2[1])) / 2;
 
    m1 = median(ar1, n); /* get the median of the first array */
    m2 = median(ar2, n); /* get the median of the second array */
 
    /* If medians are equal then return either m1 or m2 */
    if (m1 == m2)
        return m1;
 
     /* if m1 < m2 then median must exist in ar1[m1....] and ar2[....m2] */
    if (m1 < m2)
    {
        if (n % 2 == 0)
            return getMedian(ar1 + n/2 - 1, ar2, n - n/2 +1);
        else
            return getMedian(ar1 + n/2, ar2, n - n/2);
    }
 
    /* if m1 > m2 then median must exist in ar1[....m1] and ar2[m2...] */
    else
    {
        if (n % 2 == 0)
            return getMedian(ar2 + n/2 - 1, ar1, n - n/2 + 1);
        else
            return getMedian(ar2 + n/2, ar1, n - n/2);
    }
}

double median_dnc(const int32_t A[], const uint32_t m, const int32_t B[], const uint32_t n) {
  if (!m && !n)
    return 0.0;

  function<double(const int32_t [],const uint32_t,const int32_t [],const uint32_t,const uint32_t)> solve =
    [&](const int32_t a[], const uint32_t t_m, const int32_t b[], const uint32_t t_n, const uint32_t idx) -> double {
    if (!t_m)
      return b[idx-1];
    if (!t_n)
      return a[idx-1];
    if (idx == 1)
      return (a[0] < b[0]) ? a[0] : b[0];

    const uint32_t mid = min(min(t_m, idx/2), t_n);

    if (a[mid-1] < b[mid-1])
      return solve(a+mid, t_m-mid, b, t_n, idx-mid);
    else
      return solve(a, t_m, b+mid, t_n-mid, idx-mid);
  };

  uint32_t k = (m+n)/2;
  if ((m+n)%2)
    return solve(A, m, B, n, k+1);
  return (solve(A, m, B, n, k)+solve(A, m, B, n, k+1))/2;
}

int main(int argc, char** argv) {
  int32_t A[] = {1,2,3,4,5,6};
  int32_t B[] = {3,4,5,6,7,8,9};
  cout << medianOf2Sorted(A, 6, B, 7) << endl;

  return 0;
}
