

/*
Given two sorted arrays such the arrays may have some common elements. Find the sum of the maximum sum path to reach from beginning of any array to end of any of the two arrays. We can switch from one array to another array only at common elements.

Expected time complexity is O(m+n) where m is the number of elements in ar1[] and n is the number of elements in ar2[].
 */
int maxPathSum(int ar1[], int ar2[], int m, int n)
{
    // initialize indexes for ar1[] and ar2[]
    int i = 0, j = 0;
 
    // Initialize result and current sum through ar1[] and ar2[].
    int  result = 0, sum1 = 0, sum2 = 0;
 
    // Below 3 loops are similar to merge in merge sort
    while (i < m && j < n)
    {
        // Add elements of ar1[] to sum1
        if (ar1[i] < ar2[j])
            sum1 += ar1[i++];
 
        // Add elements of ar2[] to sum2
        else if (ar1[i] > ar2[j])
            sum2 += ar2[j++];
 
        else  // we reached a common point
        {
            // Take the maximum of two sums and add to result
            result += max(sum1, sum2);
 
            // Update sum1 and sum2 for elements after this
            // intersection point
            sum1 = 0, sum2 = 0;
 
            // Keep updating result while there are more common
            // elements
            while (i < m &&  j < n && ar1[i] == ar2[j])
            {
                result = result + ar1[i++];
                j++;
            }
        }
    }
 
    // Add remaining elements of ar1[]
    while (i < m)
        sum1  +=  ar1[i++];
 
    // Add remaining elements of ar2[]
    while (j < n)
        sum2 +=  ar2[j++];
 
    // Add maximum of two sums of remaining elements
    result +=  max(sum1, sum2);
 
    return result;
}

int main() {
    int X[] = {2, 1, 6};
    int Y[] = {1, 5};

    int m = sizeof(X)/sizeof(X[0]);
    int n = sizeof(Y)/sizeof(Y[0]);

    cout << "Total pairs = " << countPairs(X, Y, m, n);

    return 0;
}
