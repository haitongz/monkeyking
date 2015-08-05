/*
Given an array that contains both positive and negative integers, find the product of the maximum product subarray. Expected Time complexity is O(n) and only O(1) extra space can be used.
 */
int32_t maxSubarrayProduct(const int32_t a[], const uint32_t n) {
  int32_t max_ending_here = 1;
  int32_t min_ending_here = 1;
  int32_t ret = 1;

  /* Traverse throught the array. Following values are maintained after the ith iteration:
       max_ending_here is always 1 or some positive product ending with a[i]
       min_ending_here is always 1 or some negative product ending with a[i] */
  for (uint32_t i = 0; i < n; ++i) {
    /* If this element is positive, update max_ending_here. Update min_ending_here only if min_ending_here is negative */
    if (a[i] > 0) {
      max_ending_here *= a[i];
      min_ending_here = min(min_ending_here*a[i], 1);
    } else if (!a[i]) { /* If this element is 0, then the maximum product cannot end here, make both max_ending_here and min_ending_here 0. Assumption: Output is alway greater than or equal to 1. */
      max_ending_here = 1;
      min_ending_here = 1;
    } else {
    /* If element is negative. This is tricky: max_ending_here can either be 1
    ** or positive. min_ending_here can either be 1 or negative. next
    ** min_ending_here will always be prev max_ending_here*a[i]. next max_ending_here will be 1 if prev min_ending_here is 1, otherwise next max_ending_here will be prev min_ending_here*a[i]
    */
      int32_t tmp = max_ending_here;
      max_ending_here = max(min_ending_here*a[i], 1);
      min_ending_here = tmp*a[i];
    }

    // update ret, if needed
    ret = max(ret, max_ending_here);
  }

  return ret;
}

/*
Given a sequence of non-negative integers, find the subsequence of length 3 having maximum product with the numbers of the subsequence being in ascending order. O(nLogn). For simplicity, let us first create two arrays LSL[] and LGR[] of size n each where n is number of elements in input array arr[]. The main task is to fill two arrays LSL[] and LGR[]. Once we have these two arrays filled, all we need to find maximum product LSL[i]*arr[i]*LGR[i] where 0 < i < n-1 (Note that LSL[i] doesn't exist for i = 0 and LGR[i] doesn't exist for i = n-1). We can fill LSL[] in O(nLogn) time. The idea is to use a Balanced Binary Search Tree like AVL. We start with empty AVL tree, insert the leftmost element in it. Then we traverse the input array starting from the second element to second last element. For every element currently being traversed, we find the floor of it in AVL tree. If floor exists, we store the floor in LSL[], otherwise we store NIL. After storing the floor, we insert the current element in the AVL tree. We can fill LGR[] in O(n) time. The idea is similar to "replace with next biggest" problem. We traverse from right side and keep track of the largest element. If the largest element is greater than current element, we store it in LGR[], otherwise we store NIL. Finally, we run a O(n) loop and return maximum of LSL[i]*arr[i]*LGR[i]. Overall complexity of this approach is O(nLogn) + O(n) + O(n) which is O(nLogn). Auxiliary space required is O(n). Note that we can avoid space required for LSL, we can find and use LSL values in final loop.
 */
