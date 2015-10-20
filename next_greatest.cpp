/*
Given an array of integers, replace every element with the next greatest element (greatest element on the right side)
in the array. Since there is no element next to the last element, replace it with -1.

Given array {16, 17, 4, 3, 5, 2}, then it should be modified to {17, 5, 5, 5, 2, -1}.
 */
vector<int32_t> nextGreatest(const int32_t a[], const uint32_t n) { // O(n)
  if (!n)
    return {};
  if (n < 2)
    return {-1};

  vector<int32_t> ret;

  // Initialize the next greatest element
  int32_t max_from_right = a[n-1];

  // The next greatest element for the rightmost element is always -1
  a[n-1] = -1;

  // Replace all other elements with the next greatest
  for (int32_t i = size-2; i >= 0; --i) {
    // Store the current element (needed later for updating the next greatest element)
    int32_t tmp = a[i];
    // Replace current element with the next greatest
    a[i] = max_from_right;

    // Update the greatest element, if needed
    max_from_right = max(max_from_right, tmp);
  }
}

/*
Given an array, print the Next Greater Element (NGE) for every element.
The Next greater Element for an element x is the first greater element on the right side of x in array.
Elements for which no greater element exist, consider next greater element as -1.
 */
#include <iostream>

/*
1) Push the first element to stack.
2) Pick rest of the elements one by one and follow following steps in loop.
...a) Mark the current element as next.
...b) If stack is not empty, then pop an element from stack and compare it with next.
...c) If next is greater than the popped element, then next is the next greater element fot the popped element.
...d) Keep poppoing from the stack while the popped element is smaller than next.
      next becomes the next greater element for all such popped elements
...g) If next is smaller than the popped element, then push the popped element back.
3) After the loop in step 2 is over, pop all the elements from stack and print -1 as next element for them.
 */
void NGE(const int32_t a[], const uint32_t n) { // O(n)
  if (!n)
    return;
  stack<int32_t> s = {-1};
  s.push(a[0]);

  int32_t element, next;

  for (const auto i : a) {
    next = i;
    if (!s.empty()) {
      // if stack is not empty, then pop an element from stack
      element = s.top();
      s.pop();

      /* If the popped element is smaller than next, then
         a) print the pair
         b) keep popping while elements are smaller and stack is not empty */
      while (element < next) {
        cout << element << " --> " << next << endl;
        if (s.empty())
          break;
        element = s.top();
        s.pop();
      }

      /* If element is greater than next, then push the element back */
      if (element > next)
        s.push(element);
    }

    /* push next to stack so that we can find next greater for it */
    s.push(next);
  }

  /* After iterating over the loop, the remaining elements in stack do not have the next greater element,
     so print -1 for them */
  while (!s.empty()) {
    element = s.top();
    s.pop();
    next = -1;
    cout << element << " --> " << next << endl;
  }
}

int main(int argc, char** argv) {
  uint32_t a[]= {11, 13, 21, 3};
  const uint32_t n = sizeof(a)/sizeof(a[0]);
  NGE(a, n);

  return 0;
}
