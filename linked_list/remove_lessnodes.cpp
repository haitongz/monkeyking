/*
Given a singly linked list, remove all the nodes which have a greater value on right side.

Algorithm:
1. reverse the list;
2. traverse the reversed list. Keep max till now. If next node < max then delete the next node, otherwise max = next node.
3. reverse the list again to retain the original order.

Time Complexity: O(n)
 */
#include <iostream>
#include "list_node.h"

using namespace std;

void rmLesserNodes_recur(ListNode** head) {
  /* 1) Reverse the linked list */
  reverse_iter(head);

  function<void(ListNode*)> solve =
    [&](ListNode* currHead) {
    auto curr = currHead;
    auto maxnode = currHead;
    ListNode* tmp = nullptr;

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

  /* 2) In the reversed list, delete nodes which have a node with greater value node on left side.
        Note that head node is never deleted because it is the leftmost node.*/
  solve(*head);

  /* 3) Reverse the linked list again to retain the original order */
  reverse_iter(head_ref);
}

int main(int argc, char** argv) {
  ListNode fir(2);
  ListNode sec(4);
  ListNode thi(3);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = nullptr;
  ListNode fir2(5);
  ListNode sec2(6);
  ListNode thi2(4);
  fir2.next = &sec2;
  sec2.next = &thi2;
  thi2.next = nullptr;

  auto p = add2Numbers(&fir, &fir2);
  while (p) {
    cout << p->value << " -> ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
