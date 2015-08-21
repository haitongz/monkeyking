#include <iostream>
#include <functional>
#include <stack>
#include "list_node.h"

#define XOR_SWAP(a, b)\
do {\
  a ^= b;\
  b ^= a;\
  a ^= b;\
} while (0)

template <typename T>
void push(ListNodeT<T>** head, const T& v) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  ListNodeT<T>* nd = new ListNodeT<T>(v);
  nd->next = *head;
  *head = nd;
}

template <typename T>
ListNodeT<T>* pop(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  } else if (!*head) {
    return;
  }

  auto ret = *head;
  //assert(tmp);
  *head = ret->next;
  return ret;
}

template <typename T>
uint32_t length_iter(const ListNodeT<T>* head) {
  uint32_t ret = 0;
  auto curr = head;
  while (curr) {
    ++ret;
    curr = curr->next;
  }
  return ret;
}

template <typename T>
uint32_t length_recur(const ListNodeT<T>* head) {
  function<uint32_t(const ListNodeT<T>*)> solve =
    [&](const ListNodeT<T>* curr_head) {
    if (!curr_head)
      return 0;

    return 1+solve(curr_head->next);
  };

  return solve(head);
}

template <typename T>
bool search_iter(const ListNodeT<T>* head, const T& target) {
  auto curr = head;
  while (curr) {
    if (curr->value == target)
      return true;
  }

  return false;
}

template <typename T>
bool search_recur(const ListNodeT<T>* head, const T& target) {
  function<bool(const ListNodeT<T>*)> solve =
    [&](const ListNodeT<T>* curr_head) {
    if (!curr_head)
      return false;
    else if (curr_head->value == target)
      return true;
    else
      return solve(curr_head->next);
  };

  return solve(head);
}

template <typename T>
void print(const ListNodeT<T>* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  uint32_t i = 0;
  while (head) {
    cout << "Node[" << i++ << "] = " << head->value << endl;
    head = head->next;
  }
}

template <typename T>
void reversePrint_recur(const ListNodeT<T>* head) {
  function<void(const ListNodeT<T>*)> solve =
    [&](const ListNodeT<T>* curr_head) {
    if (!curr_head)
      return;

    solve(curr_head->next);

    cout << curr_head->value << " ";
  };

  solve(head);
}

template <typename T>
ListNodeT<T>* middle_iter(const ListNodeT<T>* head) {
  if (!head)
    return nullptr;

  auto slow = head;
  auto fast = head;
  while (fast && fast-next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow;
}

template <typename T>
ListNodeT<T>* reverse_iter(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  } else if (!(*head)) {
    return *head;
  } else {
    auto curr = *head;
    ListNodeT<T>* prev = nullptr;

    while (curr) {
      auto next = curr->next; // save the next ptr in next
      curr->next = prev;      // change next to privous
      prev = curr;            // set last node as previous node
      curr = next;            // set next node as last node
    }

    return prev;
  }
}
/*
template <typename T>
ListNodeT<T>* reverse_recur(ListNodeT<T>* curr, ListNodeT<T>* prev = NULL) {
  if (!curr)
    return nullptr;

  ListNodeT<T>* orig_next = curr->next;
  curr->next = prev;
  if (!orig_next)
    return curr;

  return reverse_recur(orig_next, curr);
}
 */
template <typename T>
ListNodeT<T>* reverse_recur(ListNodeT<T>* head) {
  function<ListNodeT<T>*(ListNodeT<T>*,ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head, ListNodeT<T>* prev) {
    ListNodeT<T>* new_head = nullptr;

    if (curr_head) {
      auto orig_next = curr_head->next;
      curr_head->next = prev;
      new_head = orig_next ? solve(orig_next, curr_head) : curr_head;
    }

    return new_head;
  };

  return solve(head, nullptr);
}

/*
Given a singly linked list of characters, write a function that returns true if the given list is palindrome, else false.
 */
//typedef ListNodeT<char> ListNode1;
template <typename T>
bool compareLists(const ListNodeT<T>* head1, const ListNodeT<T>* head2) {
  auto tmp1 = head1;
  auto tmp2 = head2;

  while (tmp1 && tmp2) {
    if (tmp1->value == tmp2->value) {
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
    else
      return false;
  }

  if (!tmp1 && !tmp2)
    return true;

  return false;
}

template <typename T>
bool isPalindrome_iter(ListNodeT<T>* head) {
  auto slow = head;
  auto fast = head;
  ListNodeT<T>* second_half;
  auto prev_of_slow = head;
  ListNodeT<T>* mid = nullptr; // To handle odd size list
  bool ret = true; // initialize result

  if (head && head->next) {
    while (fast && fast->next) {
      fast = fast->next->next;

      /* need previous of the slow_ptr for linked lists  with odd elements */
      prev_of_slow = slow;
      slow = slow->next;
    }

    /* fast would become NULL when there are even elements in list. And not NULL for odd elements. We need to skip the middle node for odd case and store it somewhere so that we can restore the original list*/
    if (fast) {
      mid = slow;
      slow = slow->next;
    }

    // reverse the second half and compare it with first half
    second_half = slow;
    prev_of_slow->next = nullptr; // NULL terminate first half
    reverse_iter(&second_half);  // Reverse the second half
    ret = compareLists(head, second_half); // compare

    /* Construct the original list back */
    reverse_iter(&second_half); // Reverse the second half again
    if (mid) { // If there was a mid node (odd size case) which was not part of either first half or second half.
      prev_of_slow->next = mid;
      mid->next = second_half;
    } else
      prev_of_slow->next = second_half;
  }

  return ret;
}

template <typename T>
bool isPalindrome_recur(ListNodeT<T>* head) {
/*  function<bool(ListNode*&,ListNode*)> solve =
    [](ListNode*& left, ListNode* right) {
    if (!right) {
      return true;
    }

    bool ret = solve(left, right->next); // this reaches the end of list
    if (ret) {
      ret = (left->value == right->value);
    }

    left = left->next;
    return ret;
  };
*/
  stack<const ListNodeT<T>*> prevs = {nullptr};
  auto curr = head;
  while (curr) {
    prevs.push(curr);
    curr = curr->next;
  }

  auto last = prevs.top();
  prevs.pop();

  function<bool(ListNodeT<T>*,ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* start, ListNodeT<T>* end) {
    auto prev = prevs.top();
    prevs.pop();

    if (start->next == prev || start == prev) // odd or even number of nodes
      return start->value == end->value;

    return (start->value == end->value) ? solve(start->next, prev) : false;
  };

  return solve(head, last);
}

/*
Reverse a linked list from position m to n, in-place and in one-pass.
Given 1->2->3->4->5->NULL, m = 2 and n = 4,
return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m <= n <= length of list.
 */
template <typename T>
void reverseM2N(ListNodeT<T>* head, const uint32_t m, const uint32_t n) {
  if (!head || !head->next)
    return;

  ListNodeT<T>* prev = nullptr;
  auto curr = head;

  int32_t cnt = m;
  while (cnt >= 0) { // && curr) no need 2 check curr
    prev = curr;
    curr = curr->next;
    --cnt;
  }

  auto cp = prev;
  for (uint32_t i = n+1; i <= m; ++i) {
    auto next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  curr->next = cp;
  cp->next = curr;
}

template <typename T>
ListNodeT<T>* getNth(ListNodeT<T>* head, const uint32_t N) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  }

  auto ret = head;
  int32_t count = N;
  while (ret && count >= 0) {
    ret = ret->next;
  }

  if (count >= 0)
    return nullptr;
  else
    return ret;
}

template <typename T>
ListNodeT<T>* nth2End(ListNodeT<T>* head, const uint32_t N) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  }

  uint32_t i = 0;
  auto end = head;
  while (end->next && i < N-1) {
    end = end->next;
    ++i;
  }

  if (i < N-1) {
#ifdef _DEBUG_
    cerr << "There are less than " << N << " elements in the list!" << endl;
#endif
    return nullptr;
  }

  auto nth2End = head;
  while (end->next) {
    end = end->next;
    nth2End = nth2End->next;
  }

  return nth2End;
}

/* O(n2) */
template <typename T>
void sort(ListNodeT<T>* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  auto first = head;
  ListNodeT<T>* second = nullptr;
  while (first) {
    second = first->next;
    while (second) {
      if (first->value > second->value) { // ascending sort
        XOR_SWAP(first->value, second->value);
      }
      second = second->next;
    }
    first = first->next;
  }
}

template <typename T>
ListNodeT<T>* sortedInsert(ListNodeT<T>** head, const T& v) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  } else {
    ListNodeT<T>* nd = new ListNodeT<T>(v);
    if (!(*head)) {
      *head = nd;
      return *head;
    } else {
      auto curr = *head;
      auto prev = curr;

      while (curr) {
        if (curr->value > v)
          break;

        prev = curr;
        curr = curr->next;
      }

      nd->next = curr;
      if (!prev) { // insert at head
        *head = nd;
      } else {
        prev->next = nd;
      }
    }
  }

  return *head;
}

template <typename T>
void sortedRemoveDup(ListNodeT<T>* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  auto curr = head;
  while (curr) {
    auto next = curr->next;
    while (next) {
      auto next2 = next->next;
      if (curr->value == next->value) {
        delete next;
        curr->next = next2;
      }
      next = next2;
    }
    curr = curr->next;
  }
}

template <typename T>
void move(ListNodeT<T>** dst_ref, ListNodeT<T>** src_ref) {
  auto new_nd = *src_ref;
  assert(new_nd);

  *src_ref = new_nd->next;
  new_nd->next = *dst_ref;
  *dst_ref = new_nd;
}

/*
Merge two sorted lists
 */
template <typename T>
ListNodeT<T>* merge2Sorted_iter(ListNodeT<T>* a, ListNodeT<T>* b) {
  ListNodeT<T>* ret = nullptr;
  auto last_ref = &ret;

  while (true) {
    if (!a) {
      *last_ref = b;
      break;
    } else if (!b) {
      *last_ref = a;
      break;
    }

    if (a->value <= b->value) {
      move(last_ref, &a);
    } else {
      move(last_ref, &b);
    }

    /* tricky: advance to point to the next ".next" field */
    last_ref = &((*last_ref)->next);
  }

  return ret;
}

template <typename T>
ListNodeT<T>* merge2Sorted_recur(ListNodeT<T>* a, ListNodeT<T>* b) {
  function<ListNodeT<T>*(ListNodeT<T>*,ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head1, ListNodeT<T>* curr_head2) {
    if (!curr_head1)
      return curr_head2;
    else if (!curr_head2)
      return curr_head1;

    ListNodeT<T>* ret = nullptr;
    if (curr_head1->value <= curr_head2->value) {
      ret = curr_head1;
      ret->next = solve(curr_head1->next, curr_head2);
    } else {
      ret = curr_head2;
      ret->next = merge2Sorted(curr_head1, curr_head2->next);
    }

    return ret;
  };

  return solve(a, b);
}

/*
Sort a linked list in O(nlogn) time using constant space complexity.
 */
template <typename T>
ListNodeT<T>* merge(ListNodeT<T>* l1, ListNodeT<T>* l2) {
  ListNodeT<T> dummy(0);
  auto curr = &dummy;

  while (l1 && l2) {
    if (l1->value < l2->value) {
      curr->next = l1;
      l1 = l1->next;
    } else {
      curr->next = l2;
      l2 = l2->next;
    }

    curr = curr->next;
  }

  curr->next = l1 ? l1 : l2;
  return dummy.next;
}

template <typename T>
ListNodeT<T>* mergeSort_recur(ListNodeT<T>* head) {
  function<ListNodeT<T>*(ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head) {
    if (!curr_head || !curr_head->next)
      return curr_head;

    auto slow = curr_head;
    auto fast = curr_head;
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    fast = slow->next;
    slow->next = nullptr;
    curr_head = solve(curr_head);
    fast = solve(fast);
    return merge(curr_head, fast);
  };

  return solve(head);
}

/*
Quick sort linked list
 */
template <typename T>
ListNodeT<T>* partition(ListNodeT<T>* head,
                        ListNodeT<T>* end,
                        ListNodeT<T>** new_head,
                        ListNodeT<T>** new_end) {
  auto pivot = end;
  ListNodeT<T>* prev = nullptr;
  auto curr = head;
  auto tail = pivot;

  // During partition, both the head and end of the list might change which is updated in the newHead and newEnd variables
  while (curr != pivot) {
    if (curr->value < pivot->value) {
      // First node that has a value less than the pivot - becomes the new head
      if (!(*new_head))
        (*new_head) = curr;

      prev = curr;
      curr = curr->next;
    } else { // If curr node is greater than pivot, move cur node to next of tail, and change tail
      if (prev)
        prev->next = curr->next;

      auto tmp = curr->next;
      curr->next = nullptr;
      tail->next = curr;
      tail = curr;
      curr = tmp;
    }
  }

  // If the pivot data is the smallest element in the current list, pivot becomes the head
  if (!(*new_head))
    (*new_head) = pivot;

  (*new_end) = tail;

  return pivot;
}

template <typename T>
void quickSort(ListNodeT<T>** head_ref) {
  function<ListNodeT<T>*(ListNodeT<T>*,ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head, ListNodeT<T>* end) { // sorting happens exclusive of the end node
    // base condition
    if (!curr_head || curr_head == end)
        return curr_head;

    ListNodeT<T>* new_head = nullptr, *new_end = nullptr;

    // Partition the list, newHead and newEnd will be updated by the partition function
    auto pivot = partition(curr_head, end, &new_head, &new_end);

    // If pivot is the smallest element - no need to recur for the left part.
    if (new_head != pivot) {
      // Set the node before the pivot node as NULL
      auto tmp = new_head;
      while (tmp->next != pivot)
        tmp = tmp->next;
      tmp->next = nullptr;

      // Recur for the list before pivot
      new_head = solve(new_head, tmp);

      // Change next of last node of the left half to pivot
      tmp = getTail(new_head);
      tmp->next = pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = solve(pivot->next, new_end);
    return new_head;
  };

  *head_ref = solve(*head_ref, getTail(*head_ref));
}

template <typename T>
uint32_t delNodes(ListNodeT<T>** head, const T& target) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return 0;
  } else if (!(*head)) {
    return 0;
  }

  uint32_t cnt = 0;
  auto curr = *head;
  ListNodeT<T>* prev = nullptr;

  while (curr) {
    auto next = curr->next;
    if (curr->value == target) {
      delete curr;
      if (!prev) { // delete at head
        *head = next;
      } else {
        prev->next = next;
      }
      ++cnt;
    } else {
      prev = curr;
    }

    curr = next;
  }

  return cnt;
}

/**
 * Delete whole list and set the head pointer to NULL
 */
template <typename T>
void delList_iter(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  auto curr = *head;
  while (curr) {
    auto next = curr->next;
    delete curr;
    curr = next;
  }

  *head = nullptr;
}

template <typename T>
void delList_recur(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  function<void(ListNodeT<T>*&)> solve =
    [&](ListNodeT<T>*& curr_head) {
    if (!curr_head)
      return;
    else if (!curr_head->next) {
      delete curr_head;
      curr_head = nullptr;
      return;
    } else
      solve(curr_head->next);
  };

  solve(*head);
}

/*
Write a program to find the node at which the intersection of two singly linked lists begins. For example, the following two linked lists:
A:          a1 - a2
                  \
                   c1 - c2 - c3
                    \
B:         b1 - b2 - b3
begin to intersect at node c1. Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
*/
template <typename T>
const ListNodeT<T>* intersection(const ListNodeT<T>* head1, const ListNodeT<T>* head2) {
  const uint32_t len1 = length_iter(head1);
  const uint32_t len2 = length_iter(head2);

  function<const ListNodeT<T>*(const uint32_t,const ListNodeT<T>*,const ListNodeT<T>*)> solve =
    [](const uint32_t diff, const ListNodeT<T>* longer_head, const ListNodeT<T>* shorter_head) {
    auto curr1 = longer_head;
    auto curr2 = shorter_head;

    for (uint32_t i = 0; i < diff; ++i) {
      if (!curr1) {
        return -1;
      }
      curr1 = curr1->next;
    }

    while (curr1 && curr2) {
      if (curr1 == curr2)
        return curr1;
      curr1 = curr1->next;
      curr2 = curr2->next;
    }

    return nullptr;
  };

  return (len1 > len2) ?
    find(len1-len2, head1, head2) : find(len2-len1, head2, head1);
}

/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.
Only constant memory is allowed.

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5
 */
template <typename T>
ListNodeT<T>* reverseKGroup_iter(ListNodeT<T>* head, const uint32_t k) { // O(n2)
  ListNodeT<T> dummy(0);
  dummy.next = head;
  auto prev = &dummy;

  while (head) {
    uint32_t i = 1;
    for ( ; i < k && head->next; ++i) {
      head = head->next;
    }
    if (i == k) {
      ListNode* last = prev->next;
      head = prev->next->next;
      for (i = 1; i < k; ++i) {
        ListNode* t = head->next;
        head->next = prev->next;
        prev->next = head;
        head = t;
      }
      prev = last;
      last->next = head;
    } else
      break;
  }

  return dummy.next;
}

template <typename T>
ListNodeT<T>* reverseKGroup_recur(ListNodeT<T>* head, const uint32_t k) {
  function<ListNodeT<T>*(ListNodeT<T>*)> solve = // O(n)
    [&](ListNodeT<T>* curr_head) {
    auto curr = curr_head;
    ListNodeT<T>* next = nullptr;
    auto prev = next;
    uint32_t cnt = 0;

    /*reverse first k nodes of the linked list */
    while (curr && cnt < k) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      ++cnt;
    }

    /* next is now a pointer to (k+1)th node. Recursively call for the list starting from current.
       And make rest of the list as next of first node */
    if (next) {
      curr_head->next = solve(next);
    }

    /* prev is new head of the input list */
    return prev;
  };

  return solve(head);
}

/*
Given a linked list, write a function to reverse every alternate k nodes (where k is an input to the function) in an efficient way. Give the complexity of your algorithm.

Example:
Inputs:   1->2->3->4->5->6->7->8->9->NULL and k = 3
Output:   3->2->1->4->5->6->9->8->7->NULL.
 */
/* Reverses alternate k nodes and returns the pointer to the new head node */
template <typename T>
ListNodeT<T>* kAltReverse_recur(ListNodeT<T>* head, const uint32_t k) { // O(n)
  function<ListNodeT<T>*(ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head) {
    auto curr = curr_head;
    ListNodeT<T>* next = nullptr;
    auto prev = next;
    uint32_t cnt = 0;

    /*1) reverse first k nodes of the linked list */
    while (curr && cnt < k) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      ++cnt;
    }

    /* 2) Now head points to the kth node. So change next of head to (k+1)th node*/
    if (curr_head)
      curr_head->next = curr;
    /* 3) We do not want to reverse next k nodes. So move the current pointer to skip next k nodes */
    cnt = 0;
    while (cnt < k-1 && curr) {
      curr = curr->next;
      ++cnt;
    }
    /* 4) Recursively call for the list starting from curr->next. And make rest of the list as next of first node */
    if (curr)
      curr->next = solve(curr->next);
    /* 5) prev is new head of the input list */
    return prev;
  };

  return solve(head);
}

/*
Given a singly linked list, remove all the nodes which have a greater value on right side.

Algorithm:
1. reverse the list;
2. traverse the reversed list. Keep max till now. If next node < max then delete the next node, otherwise max = next node.
3. reverse the list again to retain the original order.

Time Complexity: O(n)
 */
template <typename T>
void delLesserNodes_recur(ListNodeT<T>** head_ref) {
  /* 1) Reverse the linked list */
  reverse_iter(head_ref);

  function<void(ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head) {
    auto curr = curr_head;
    auto maxnode = curr_head;
    ListNodeT<T>* tmp = nullptr;

    while (curr && curr->next) {
      /* If current is smaller than max, then delete current */
      if (curr->next->value < maxnode->value) {
        tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
      } else { /* If current is greater than max, then update max and move current */
        curr = curr->next;
        maxnode = curr;
      }
    }
  };

  /* 2) In the reversed list, delete nodes which have a node with greater value node on left side. Note that head node is never deleted because it is the leftmost node.*/
  solve(*head_ref);

  /* 3) Reverse the linked list again to retain the original order */
  reverse_iter(head_ref);
}

/*
Given a linked list, swap every two adjacent nodes and return its head.
For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.
Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 */
ListNode* swapPairs_iter(ListNode* head) {
  function<void(ListNode*)> swap_ = [](ListNode* nd) {
    auto next = nd->next;
    if (!nd || !next || !next->next)
      return;

    auto next2 = next->next;
    auto next3 = next2->next; // ok since next2 has been checked already
    nd->next = next2;
    next2->next = next;
    next->next = next3;
  };

  ListNode dummy(0);
  dummy.next = head;
  auto curr = &dummy;

  while (curr) {
    swap_(curr);

    auto next = curr->next;
    if (!next)
      break;

    auto next2 = next->next;
    curr = next2;
  }

  return dummy.next;
}

ListNode* swapPairs_recur(ListNode* head) {
  function<ListNode*(ListNode*)> solve =
    [&](ListNode* curr) { // DFS
    if (curr && curr->next) {
      auto next = curr->next;
      auto next2 = next->next;
      ListNode* cp = curr;
      curr = next;
      curr->next = cp;
      cp->next = solve(next2);
    }

    return curr;
  };

  return solve(head);
}

/*
Given a Singly Linked List, starting from the second node delete all alternate nodes of it. For example, if the given linked list is 1->2->3->4->5 then your function should convert it to 1->3->5, and if the given linked list is 1->2->3->4 then convert it to 1->3.
 */
template <typename T>
void delAlt_iter(ListNodeT<T>* head) {
  if (!head)
    return;

  /* Initialize prev and node to be deleted */
  auto prev = head;
  auto curr = head->next;

  while (prev && curr) {
    /* Change next link of previous node */
    prev->next = curr->next;
    delete curr;
    prev = prev->next;
    if (prev)
      curr = prev->next;
  }
}

template <typename T>
void delAlt_recur(ListNodeT<T>* head) {
  function<void(ListNodeT<T>*)> solve =
    [&](ListNodeT<T>* curr_head) {
    if (!curr_head)
      return;

    auto nd = curr_head->next;
    if (!nd)
      return;

    curr_head->next = nd->next;
    delete nd;

    /* Recursively call for the new next of head */
    solve(curr_head->next);
  };

  return solve(head);
}

/*
Write a function that takes one list and divides up its nodes to make two smaller lists 'a' and 'b'. The sublists should be made from alternating elements in the original list. So if the original list is 0->1->0->1->0->1 then one sublist should be 0->0->0 and the other should be 1->1->1.

Time Complexity: O(n)
 */
template <typename T>
void alternatingSplit(ListNodeT<T>* src, ListNodeT<T>** aref, ListNodeT<T>** bref) {
  ListNodeT<T> adummy, bdummy;
  auto atail = &adummy; /* points to the last node in 'a' */
  auto btail = &bdummy; /* points to the last node in 'b' */
  auto curr = src;
  adummy.next = nullptr;
  bdummy.next = nullptr;

  while (curr) {
    move(&(atail->next), &curr); /* add at 'a' tail */
    atail = atail->next; /* advance the 'a' tail */
    if (curr) {
      move(&(btail->next), &curr);
      btail = btail->next;
    }
  }

  *aref = adummy.next;
  *bref = bdummy.next;
}

/*
Given a Linked List of integers, write a function to modify the linked list such that all even numbers appear before all the odd numbers in the modified linked list. Also, keep the order of even and odd numbers same.

Examples:
Input: 17->15->8->12->10->5->4->1->7->6->NULL
Output: 8->12->10->4->6->17->15->5->1->7->NULL
 */
void segregate(ListNode** head_ref) { // O(n)
  auto end = *head_ref;
  ListNode* prev = nullptr;
  auto curr = *head_ref;

  /* Get pointer to the last node */
  while (end->next)
    end = end->next;

  auto new_end = end;

  /* Consider all odd nodes before the first even node and move then after end */
  while (curr->value%2 && curr != end) {
    new_end->next = curr;
    curr = curr->next;
    new_end->next->next = nullptr;
    new_end = new_end->next;
  }

  // 10->8->17->17->15
  /* Do following steps only if there is any even node */
  if (!(curr->value%2)) {
    /* Change the head pointer to point to first even node */
    *head_ref = curr;
    /* now current points to the first even node */
    while (curr != end) {
      if (!(curr->value%2)) {
        prev = curr;
        curr = curr->next;
      } else { /* break the link between prev and current */
        prev->next = curr->next;
        /* Make next of curr as NULL  */
        curr->next = nullptr;
        /* Move curr to end */
        new_end->next = curr;
        /* make curr as new end of list */
        new_end = curr;
        /* Update current pointer to next of the moved node */
        curr = prev->next;
      }
    }
  } else
    prev = curr;

  /* We must have prev set before executing lines following this statement */
  /* If there are more than 1 odd nodes and end of original list is odd then move this node to end to maintain same order of odd numbers in modified list */
  if (new_end != end && end->value%2) {
    prev->next = end->next;
    end->next = nullptr;
    new_end->next = end;
  }
}

/*
Detect and remove loop
 */
/* Function to remove loop.
 loop_node --> Pointer to one of the loop nodes
 head -->  Pointer to the start node of the linked list */
template <typename T>
void removeLoop(ListNodeT<T>* loop_node, ListNodeT<T>* head) {
  auto ptr1 = head;
  auto ptr2 = loop_node;

  /* Set a pointer to the beging of the Linked List and move it one by one to find the first node which is
      part of the Linked List */
  while (true) {
    /* Now start a pointer from loop_node and check if it ever reaches ptr2 */
    ptr2 = loop_node;
    while (ptr2->next != loop_node && ptr2->next != ptr1) {
      ptr2 = ptr2->next;
    }

    /* If ptr2 reahced ptr1 then there is a loop. So break the loop */
    if (ptr2->next == ptr1)
      break;
    else /* If ptr2 did't reach ptr1 then try the next node after ptr1 */
      ptr1 = ptr1->next;
  }

  /* After the end of loop ptr2 is the last node of the loop. So make next of ptr2 as NULL */
  ptr2->next = nullptr;
}

template <typename T>
uint8_t detectAndRemoveLoop(ListNodeT<T>* head) {
  auto slow_p = head, fast_p = head;

  while (slow_p && fast_p && fast_p->next) {
    slow_p = slow_p->next;
    fast_p  = fast_p->next->next;

    /* If slow_p and fast_p meet at some point then there is a loop */
    if (slow_p == fast_p) {
      removeLoop(slow_p, head);

      /* Return 1 to indicate that loop is found */
      return 1;
    }
  }

  /* Return 0 to indeciate that ther is no loop*/
  return 0;
}

/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
 */
ListNode* addTwoNums(const ListNode* l1, const ListNode* l2) {
  ListNode* sumList = new ListNode(-1);
  ListNode* curr = sumList;

  uint8_t carry = 0;
  while (l1 || l2 || carry) {
    int32_t l1val = !l1 ? 0 : l1->value;
    int32_t l2val = !l2 ? 0 : l2->value;
    int32_t sum = l1val+l2val+carry;
    carry = sum/10; // 0 or 1
    sum %= 10;

    curr->next = new ListNode(sum);
    curr = curr->next;
    l1 = !l1 ? NULL : l1->next;
    l2 = !l2 ? NULL : l2->next;
  }

  ListNode* res = sumList->next;
  delete sumList;
  return res;
}

template <typename T>
ListNodeT<T>* Union(ListNodeT<T>* head1, ListNodeT<T>* head2) {
  auto t1 = head1, t2 = head2;
  ListNodeT<T>* ret = nullptr;

  // Insert all elements of list1 to the result list
  while (t1) {
    push(&ret, t1->value);
    t1 = t1->next;
  }

  // Insert those elements of list2 which are not present in result list
  while (t2) {
    if (!isPresent(ret, t2->value))
      push(&ret, t2->value);
    t2 = t2->next;
  }

  return ret;
}

/*
Given three linked lists, say a, b and c, find one node from each list such that the sum of the values of the nodes is equal to a given number.

1) Sort list b in ascending order, and list c in descending order.
2) After the b and c are sorted, one by one pick an element from list a and find the pair by traversing both b and c.

Time complexity: linked lists b and c can be sorted in O(nLogn) time using Merge Sort. Step 2 takes O(n*n) time. So the overall time complexity is O(nlogn)+O(nlogn)+O(n*n) = O(n*n)
 */
bool isSumSorted(ListNode* ahead, ListNode* bhead,
                 ListNode* chead, const int32_t target) {
  ListNode* a = ahead;

  // Traverse through all nodes of a
  while (a) {
    ListNode* b = bhead;
    ListNode* c = chead;

    // For every node of list a, prick two nodes from lists b abd c
    while (b && c) {
      // If this a triplet with given sum, print it and return true
      int32_t sum = a->value+b->value+c->value;
      if (sum == target) {
        cout << "Triplet Found: " << a->value << " " << b->value << " " << c->value << endl;
        return true;
      } else if (sum < target) // If sum of this triplet is smaller, look for greater values in b
        b = b->next;
      else // If sum is greater, look for smaller values in c
        c = c->next;
    }

    a = a->next; // Move ahead in list a
  }

  cout << "No such triplet!" << endl;
  return false;
}

/*
Given a list, rotate the list to the right by k places, where k is non-negative.
For example, given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.
 */
template <typename T>
ListNodeT<T>* rightRotateByK(ListNodeT<T>* head, uint32_t k) {
  if (!head || !head->next || !k)
    return head;

  ListNodeT<T> dummy;
  dummy.next = head;
  const uint32_t n = length(head);
  k %= n; // note: k can become 0
  while (k > 1 && head->next) {
    head = head->next;
    --k;
  }

  auto prev = &dummy;
  while (head->next) {
    head = head->next;
    prev = prev->next;
  }

  auto ret = prev->next;
  prev->next = nullptr;
  head->next = dummy.next;
  return ret;
}

/*
Given two linked lists, insert nodes of second list into first list at alternate positions of first list.
For example, if first list is 5->7->17->13->11 and second is 12->10->2->4->6, the first list should become 5->12->7->10->17->2->13->4->11->6 and second list should become empty. The nodes of second list should only be inserted when there are positions available. For example, if the first list is 1->2->3 and second list is 4->5->6->7->8, then first list should become 1->4->2->5->3->6 and second list to 7->8.

Use of extra space is not allowed (Not allowed to create additional nodes), i.e., insertion must be done in-place. Expected time complexity is O(n) where n is number of nodes in first list.
 */
template <typename T>
void mergeAlt(ListNodeT<T>* p, ListNode** q) {
  auto p_curr = p;
  auto q_curr = *q;

  // While therre are avialable positions in p
  while (p_curr && q_curr) {
    auto p_next = p_curr->next;
    auto q_next = q_curr->next;

    // Make q_curr as next of p_curr
    q_curr->next = p_next; // Change next pointer of q_curr
    p_curr->next = q_curr; // Change next pointer of p_curr

    // Update current pointers for next iteration
    p_curr = p_next;
    q_curr = q_next;
  }

  *q = q_curr;
}

/*
Given two sorted linked lists, construct a linked list that contains maximum sum path from start to end. The result list may contain nodes from both input lists. When constructing the result list, we may switch to the other input list only at the point of intersection (which mean the two node with the same value in the lists). You are allowed to use O(1) extra space.
 */
ListNode* finalMaxSumList(ListNode* a, ListNode* b) {
  ListNode* ret = nullptr;
  auto prev1 = a, curr1 = a;
  auto prev2 = b, curr2 = b;

  // Till either of the current pointers is not NULL execute the loop
  while (curr1 || curr2) {
    // Keeping 2 local variables at the start of every loop run to keep track
    // of the sum between prev and curr pointer elements.
    int32_t sum1 = 0, sum2 = 0;

    // Calculating sum by traversing the nodes of linked list as the merging of two linked list.
    // The loop stops at a common node
    while (curr1 && curr2 && curr1->value != curr2->value) {
      if (curr1->value < curr2->value) {
        sum1 += curr1->value;
        curr1 = curr1->next;
      } else { // (curr2->data < curr1->data)
        sum2 += curr2->value;
        curr2 = curr2->next;
      }
    }

    // If either of current pointers becomes NULL carry on the sum calculation for other one.
    if (!curr1) {
      while (curr2) {
        sum2 += curr2->value;
        curr2 = curr2->next;
      }
    }
    if (!curr2) {
      while (curr1) {
        sum1 += curr1->value;
        curr1 = curr1->next;
      }
    }

    if (prev1 == a && prev2 == b)
      ret = (sum1 > sum2) ? prev1 : prev2;
    else { // If pre1 and pre2 don't contain the head pointers of lists adjust the next pointers of previous pointers.
      if (sum1 > sum2)
        prev2->next = prev1->next;
      else
        prev1->next = prev2->next;
    }

    // Adjusting previous pointers
    prev1 = curr1;
    prev2 = curr2;

    // If curr1 is not NULL move to the next.
    if (curr1)
      curr1 = curr1->next;
    // If curr2 is not NULL move to the next.
    if (curr2)
      curr2 = curr2->next;
  }

 /* while (ret) {
        cout << result->data << " ";
        result = result->next;
    } */
  return ret;
}

/*
Given a singly linked list L: L0->L1...Ln-1->Ln, reorder it to: L0->Ln->L1->Ln-1...L2->Ln-2
You must do this in-place without altering the nodes' values.
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
void reverseList(ListNode* prev) {
  ListNode* tail = prev->next;

  while (tail->next) {
    ListNode* t = tail->next;
    tail->next = t->next;
    t->next = prev->next;
    prev->next = t;
  }
}

void intertwinedList(ListNode* h1, ListNode* h2) {
  while (h2) {
    ListNode* t = h2;
    h2 = h2->next;
    t->next = h1->next;
    h1->next = t;
    h1 = t->next;
  }
}

void reorderList(ListNode* head) {
  if (!head || !head->next || !head->next->next)
    return;

  ListNode* prev = head->next;
  ListNode* tail = prev->next;
  while (tail && tail->next) {
    prev = prev->next;
    tail = tail->next->next;
  }
  reverseList(prev);

  tail = prev->next;
  prev->next = NULL;
  intertwinedList(head, tail);
}

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  ListNode* head = &fir;
  ListNode* p = reverse_recur<int32_t>(head);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  fir.value = 1;
  sec.value = 2;
  thi.value = -3;
  fou.value = 4;
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  ListNode* curr = mergeSort_recur(&fir);
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  ListNode h1(2), f1(4), s1(3), h2(5), f2(6), s2(4);
  h1.next = &f1;
  f1.next = &s1;
  h2.next = &f2;
  f2.next = &s2;

  const ListNode* l1 = &h1;
  const ListNode* l2 = &h2;
  const ListNode* res = addTwoNums(&h1, &h2);
  while (res) {
    cout << res->value;
    res = res->next;
  }
  cout << endl;

  fir.value = 1;
  sec.value = 2;
  thi.value = 3;
  fou.value = 4;
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = NULL;

  reorderList(&fir);

  p = &fir;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
