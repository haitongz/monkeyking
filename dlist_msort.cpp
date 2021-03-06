/*
Given a doubly linked list, write a function to sort the doubly linked list in increasing order using merge sort.
 */
#include <iostream>
#include "list_node.h"

using namespace std;

/*
Quick Sort in its general form is an in-place sort (i.e. it doesn't require any extra storage)
whereas merge sort requires O(N) extra storage, N denoting the array size which may be quite expensive.
Allocating and de-allocating the extra space used for merge sort increases the running time of the algorithm.
Comparing average complexity we find that both type of sorts have O(NlogN) average complexity but the constants differ.
For arrays, merge sort loses due to the use of extra O(N) storage space.

Most practical implementations of Quick Sort use randomized version. The randomized version has expected time complexity
of O(nLogn). The worst case is possible in randomized version also, but worst case doesn't occur for a particular pattern
(like sorted array) and randomized Quick Sort works well in practice.

Quick Sort is also a cache friendly sorting algorithm as it has good locality of reference when used for arrays.

Quick Sort is also tail recursive, therefore tail call optimizations is done.

Why is Merge Sort preferred for Linked Lists?

In case of linked lists the case is different mainly due to difference in memory allocation of arrays and linked lists.
Unlike arrays, linked list nodes may not be adjacent in memory. Unlike array, in linked list, we can insert items
in the middle in O(1) extra space and O(1) time. Therefore merge operation of merge sort can be implemented without
extra space for linked lists.

In arrays, we can do random access as elements are continuous in memory. Let us say we have an integer (4-byte) array A
and let the address of A[0] be x then to access A[i], we can directly access the memory at (x + i*4).
Unlike arrays, we can not do random access in linked list. Quick Sort requires a lot of this kind of access.
In linked list to access i-th index, we have to travel each and every node from the head to i-th node
as we don't have continuous block of memory. Therefore, the overhead increases for quick sort.
Merge sort accesses data sequentially and the need of random access is low.
 */
DListNode* mergeSort(ListNode* head) {
  function<DListNode*(DListNode*,DListNode*)> merge
    = [&](DListNode* first, DListNode* second) {
    // If first linked list is empty
    if (!first)
      return second;

    // If second linked list is empty
    if (!second)
      return first;

    // Pick the smaller value
    if (first->value < second->value) {
      first->next = merge(first->next, second);
      first->next->prev = first;
      first->prev = nullptr;
      return first;
    } else {
      second->next = merge(first,second->next);
      second->next->prev = second;
      second->prev = NULL;
      return second;
    }
  };

  function<DListNode*(DListNode*)> split = [&](DListNode* curr_head) {
    DListNode* fast = curr_head, *slow = curr_head;
    while (fast->next && fast->next->next) {
      fast = fast->next->next;
      slow = slow->next;
    }

    DListNode* tmp = slow->next;
    slow->next = nullptr;
    return tmp;
  };

  DListNode* second = split(head);

  function<DListNode*(DListNode*)> solve =
    [&](DListNode* curr_head) {
    if (!curr_head || !curr_head->next)
      return head;

    curr_head = solve(curr_head);
    second = solve(second);

    return merge(curr_head, second);
  };

  return solve(head);
}
