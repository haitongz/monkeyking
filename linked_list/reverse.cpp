#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

void reversePrint_recur(const ListNode* head) {
  function<void(const ListNode*)> solve =
    [&](const ListNode* currHead) {
    if (!currHead) {
      return;
    }

    solve(currHead->next);

    cout << currHead->value << " ";
  };

  solve(head);
}

ListNode* reverse_iter(ListNode** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
#endif
    return nullptr;
  } else if (!(*head)) {
    return *head;
  } else {
    auto curr = *head;
    ListNode* prev = nullptr;

    while (curr) {
      auto next = curr->next; // save the next ptr in next
      curr->next = prev;      // change next to privous
      prev = curr;            // set last node as previous node
      curr = next;            // set next node as last node
    }

    return prev;
  }
}

ListNode* reverse_recur(ListNode* head) {
  function<ListNode*(ListNode*,ListNode*)> solve =
    [&](ListNode* currHead, ListNode* prev) {
    ListNode* newHead;

    if (currHead) {
      auto next = currHead->next;
      currHead->next = prev;
      newHead = next ? solve(next, currHead) : currHead;
    }

    return newHead;
  };

  return solve(head, nullptr);
}

/*
Reverse a linked list from position m to n, in-place and in one-pass.
Given 1->2->3->4->5->NULL, m = 2 and n = 4,
return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 <= m <= n <= length of list.
 */
void reverseM2N(ListNode* head, const uint m, const uint n) {
  if (!head || !head->next)
    return;

  ListNode* prev = nullptr;
  auto curr = head;

  uint cnt = m-1;
  while (cnt > 0) {
    prev = curr;
    curr = curr->next;
    --cnt;
  }

  auto cp1 = prev, cp2 = curr;
  for (uint i = m; i < n+1; ++i) {
    auto next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  cp1->next = prev;
  cp2->next = curr;
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
ListNode* reverseKGroup_iter(ListNode* head, const uint k) { // O(n2)
  ListNode dummy(0);
  dummy.next = head;
  auto prev = &dummy;

  while (head) {
    uint i = 1;
    for (; i < k && head->next; ++i) {
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
    } else {
      break;
    }
  }

  return dummy.next;
}

ListNode* reverseKGroup_recur(ListNode* head, const uint k) {
  function<ListNode*(ListNode*)> solve = // O(n)
    [&](ListNode* currHead) {
    auto curr = currHead;
    ListNode* next = nullptr;
    auto prev = next;
    uint cnt = 0;

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
      currHead->next = solve(next);
    }

    /* prev is new head of the input list */
    return prev;
  };

  return solve(head);
}

/*
Given a linked list, write a function to reverse every alternate k nodes (where k is an input to the function)
in an efficient way. Give the complexity of your algorithm.

Inputs:   1->2->3->4->5->6->7->8->9->NULL and k = 3
Output:   3->2->1->4->5->6->9->8->7->NULL.
 */
/* Reverses alternate k nodes and returns the pointer to the new head node */
ListNode* reverseAlternateK_recur(ListNode* head, const uint k) { // O(n)
  function<ListNode*(ListNode*)> solve =
    [&](ListNode* currHead) {
    auto curr = currHead;
    ListNode* next = nullptr;
    auto prev = next;
    uint cnt = 0;

    /*1) reverse first k nodes of the linked list */
    while (curr && cnt < k) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      ++cnt;
    }

    /* 2) Now head points to the kth node. So change next of head to (k+1)th node*/
    if (currHead)
      currHead->next = curr;
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


int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  ListNode fri(5);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = &fri;
  fri.next = nullptr;

  auto p = reverse_recur(&fir);
  auto cp = p;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  reversePrint_recur(cp);
  cout << endl;

  reverseM2N(cp, 2, 4);
  while (cp) {
    cout << cp->value << " ";
    cp = cp->next;
  }
  cout << endl;

  return 0;
}
