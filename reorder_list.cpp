/*
Given a singly linked list L: L0->L1...Ln-1->Ln, reorder it to: L0->Ln->L1->Ln-1...L2->Ln-2
You must do this in-place without altering the nodes' values.

Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

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
  fou.next = NULL;

  reorderList(&fir);

  ListNode* p = &fir;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
  return 0;
}
