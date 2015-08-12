/*
Sort a linked list in O(nlogn) time using constant space complexity.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* merge(ListNode* l1, ListNode* l2) {
  ListNode dummy(0);
  ListNode* curr = &dummy;

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

ListNode* sort_recur(ListNode* head) {
  if (!head || !head->next)
    return head;

  ListNode* slow = head;
  ListNode* fast = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  fast = slow->next;
  slow->next = NULL;
  head = sort_recur(head);
  fast = sort_recur(fast);
  return merge(head, fast);
}

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(-3);
  ListNode fou(4);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = NULL;

  ListNode* curr = sort_recur(&fir);
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;
  return 0;
}
