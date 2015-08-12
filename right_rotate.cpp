/*
Given a list, rotate the list to the right by k places, where k is non-negative.

Given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* rightRotateByK(ListNode* head, uint32_t k) {
  if (!head || !head->next || !k)
    return head;

  ListNode dummy(-1);
  dummy.next = head;
  const uint32_t n = length(head);
  k %= n; // note: k can become 0
  while (k > 1 && head->next) {
    head = head->next;
    --k;
  }
  ListNode* prev = &dummy;
  while (head->next) {
    head = head->next;
    prev = prev->next;
  }
  ListNode* h = prev->next;
  prev->next = NULL;
  head->next = dummy.next;
  return h;
}

int main(int argc, char** argv) {
  ListNode head(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  ListNode fiv(5);

  head.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = &fiv;
  fiv.next = NULL;

  ListNode* p = rightRotateByK(&head, 2);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
  return 0;
}
