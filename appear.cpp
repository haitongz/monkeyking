/*
Given an array of size n, find all elements in array that appear more than n/k times. For example, if the input arrays is {3, 1, 2, 2, 1, 2, 3, 3} and k is 4, then the output should be [2, 3]. Note that size of array is 8 (or n = 8), so we need to find all elements that appear more than 2 (or 8/4) times. There are two elements that appear more than two times, 2 and 3.
 */
#include <iostream>

/*
O(nk) solution:
We can solve the above problem in O(nk) time using O(k-1) extra space. Note that there can never be more than k-1 elements in output (Why?). There are mainly three steps in this algorithm.

1) Create a temporary array of size (k-1) to store elements and their counts (The output elements are going to be among these k-1 elements).
2) Traverse through the input array and update temp[] (add/remove an element or increase/decrease count) for every traversed element. The array temp[] stores potential (k-1) candidates at every step. This step takes O(nk) time.
3) Iterate through final (k-1) potential candidates (stored in temp[]). or every element, check if it actually has count more than n/k. This step takes O(nk) time.
 */
void moreThanNdK(const int32_t a[], const uint32_t n, const uint32_t k) {
    // k must be greater than 1 to get some output
    if (k < 2)
       return;
 
    /* Step 1: Create a temporary array (contains element
       and count) of size k-1. Initialize count of all
       elements as 0 */
    struct eleCount temp[k-1];
    for (int i=0; i<k-1; i++)
        temp[i].c = 0;
 
    /* Step 2: Process all elements of input array */
    for (int i = 0; i < n; i++)
    {
        int j;
 
        /* If arr[i] is already present in
           the element count array, then increment its count */
        for (j=0; j<k-1; j++)
        {
            if (temp[j].e == arr[i])
            {
                 temp[j].c += 1;
                 break;
            }
        }
 
        /* If arr[i] is not present in temp[] */
        if (j == k-1)
        {
            int l;
             
            /* If there is position available in temp[], then place 
              arr[i] in the first available position and set count as 1*/
            for (l=0; l<k-1; l++)
            {
                if (temp[l].c == 0)
                {
                    temp[l].e = arr[i];
                    temp[l].c = 1;
                    break;
                }
            }
 
            /* If all the position in the temp[] are filled, then 
               decrease count of every element by 1 */
            if (l == k-1)
                for (l=0; l<k; l++)
                    temp[l].c -= 1;
        }
    }
 
    /*Step 3: Check actual counts of potential candidates in temp[]*/
    for (int i=0; i<k-1; i++)
    {
        // Calculate actual count of elements 
        int ac = 0;  // actual count
        for (int j=0; j<n; j++)
            if (arr[j] == temp[i].e)
                ac++;
 
        // If actual count is more than n/k, then print it
        if (ac > n/k)
           cout << "Number:" << temp[i].e
                << " Count:" << ac << endl;
    }
}
