/*
Given a linked list, remove the nth node from the end of list and return its head.

Given linked list: 1->2->3->4->5, and n = 2.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

// Note: will loop infitely if list has cycle
ListNode* removeNthFromEnd(ListNode* head, uint32_t n) {
  ListNode dummy(0);
  dummy.next = head;
  ListNode* curr = &dummy;

  while (head) {
    if (!n)
      curr = curr->next;
    if (n > 0)
      --n;

    head = head->next;
  }

  curr->next = curr->next->next;
  return dummy.next;
}

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(-3);
  ListNode fou(4);
  ListNode fiv(5);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = &fiv;
  fiv.next = NULL;

  ListNode* curr = removeNthFromEnd(&fir, 2);
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;
  return 0;
}
