#include <iostream>
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

  ListNodeT<T>* res = *head;
  //assert(tmp);
  *head = res->next;
  return res;
}

template <typename T>
uint32_t length_iter(const ListNodeT<T>* head) {
  uint32_t ret = 0;
  const ListNodeT<T>* curr = head;
  while (curr) {
    ++ret;
    curr = curr->next;
  }
  return ret;
}

template <typename T>
uint32_t length_recur(const ListNodeT<T>* head) {
  function<uint32_t(const ListNodeT<T>*)> solve = [](const ListNodeT<T>* curr) {
    if (!curr)
      return 0;

    return 1+solve(curr->next);
  };

  return solve(head);
}

template <typename T>
bool found_iter(const ListNodeT<T>* head, const T& target) {
  const ListNodeT<T>* curr = head;
  while (curr) {
    if (curr->value == target)
      return true;
  }

  return false;
}

template <typename T>
bool found_recur(const ListNodeT<T>* head, const T& target) {
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
  function<void(const ListNodeT<T>*)> solve = [](const ListNodeT<T>* curr) {
    if (!curr)
      return;
    solve(curr->next);
    cout << curr->value << " ";
  };

  solve(head);
}

template <typename T>
ListNodeT<T>* middle_iter(const ListNodeT<T>* head) {
  if (!head)
    return nullptr;

  const ListNodeT<T>* slow = head;
  const ListNodeT<T>* fast = head;

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
    ListNodeT<T>* curr = *head;
    ListNodeT<T>* prev = nullptr;

    while (curr) {
      ListNodeT<T>* next = curr->next; // save the next ptr in next
      curr->next = prev;               // change next to privous
      prev = curr;                     // set last node as previous node
      curr = next;                     // set next node as last node
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
    [](ListNodeT<T>* curr_head, ListNodeT<T>* prev) {
    ListNodeT<T>* new_head = nullptr;

    if (curr_head) {
      ListNodeT<T>* orig_next = curr_head->next;
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
bool compareLists(const ListNode* head1, const ListNode* head2) {
  const ListNode* tmp1 = head1, *tmp2 = head2;

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

bool isPalindrome_iter(ListNode* head) {
  ListNode* slow = head, *fast = head;
  ListNode* second_half, *prev_of_slow = head;
  ListNode* mid = nullptr;  // To handle odd size list
  bool res = true; // initialize result

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
    prev_of_slow->next = NULL; // NULL terminate first half
    reverse_iter(&second_half);  // Reverse the second half
    res = compareLists(head, second_half); // compare

    /* Construct the original list back */
    reverse_iter(&second_half); // Reverse the second half again
    if (mid) { // If there was a mid node (odd size case) which was not part of either first half or second half.
      prev_of_slow->next = mid;
      mid->next = second_half;
    } else
      prev_of_slow->next = second_half;
  }

  return res;
}

bool isPalindrome_recur(ListNode* head) {
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
  stack<const ListNode*> prevs = {nullptr};
  const ListNode* curr = head;
  while (curr) {
    prevs.push(curr);
    curr = curr->next;
  }
  ListNode* last = prevs.top();
  prevs.pop();

  function<bool(ListNode*,ListNode*)> solve =
    [&](ListNode* start, ListNode* end) {
    const ListNode* prev = prevs.top();
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

  ListNode* prev = nullptr;
  ListNode* curr = head;

  int32_t cnt = m;
  while (cnt >= 0) { // && curr) no need 2 check curr
    prev = curr;
    curr = curr->next;
    --cnt;
  }

  ListNode* cp = prev;
  for (uint32_t i = n+1; i <= m; ++i) {
    ListNode* next = curr->next;
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

  const ListNodeT<T>* ret = head;
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
  ListNodeT<T>* end = head;
  while (end->next && i < N-1) {
    end = end->next;
    ++i;
  }

  if (i < N-1) {
#ifdef _DEBUG_
    cerr << "There are less than " << N << " elements in the list!" << endl;
#endif
    return NULL;
  }

  ListNodeT<T>* nth2End = head;
  while (end->next) {
    end = end->next;
    nth2End = nth2End->next;
  }

  return nth2End;
}

/*this is an O(n2) algorithm, any better ones? */

template <typename T>
void sort(ListNodeT<T>* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  ListNodeT<T>* first = head;
  ListNodeT<T>* second = NULL;
  while (first) {
    second = first->next;
    while (second) {
      if (first->value > second->value) {         // ascending sort
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
      ListNodeT<T>* curr = *head;
      ListNodeT<T>* prev = nullptr;

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
uint32_t deleteNodes(ListNodeT<T>** head, const T& target) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return 0;
  } else if (!(*head)) {
    return 0;
  }

  uint32_t cnt = 0;
  ListNodeT<T>* curr = *head;
  ListNodeT<T>* prev = nullptr;

  while (curr) {
    ListNodeT<T>* next = curr->next;
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
void deleteList_iter(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  ListNodeT<T>* curr = *head;
  while (curr) {
    ListNodeT<T>* next = curr->next;
    delete curr;
    curr = next;
  }

  *head = nullptr;
}

template <typename T>
void deleteList_recur(ListNodeT<T>** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  function<void(ListNodeT<T>*&)> solve = [](ListNodeT<T>*& curr_head) {
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
    const ListNodeT<T>* curr1 = longer_head;
    const ListNodeT<T>* curr2 = shorter_head;

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
ListNode* reverseKGroup(ListNode* head, const uint32_t k) {
  ListNode dummy(0);
  dummy.next = head;
  ListNode* prev = &dummy;

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

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = NULL;

  ListNode* head = &fir;
  ListNode* p = reverse_recur<int32_t>(head);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
  return 0;
}
