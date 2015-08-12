/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
You should preserve the original relative order of the nodes in each of the two partitions.
For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* partitionList(ListNode* head, const int32_t x) {
  ListNode dum1(0);
  ListNode dum2(0);
  ListNode* p1 = &dum1;
  ListNode* p2 = &dum2;
  ListNode* curr = head;

  while (curr) {
    if (curr->value < x) {
      p1->next = curr;
      p1 = p1->next;
    } else {
      p2->next = curr;
      p2 = p2->next;
    }
    curr = curr->next;
  }

  p1->next = dum2.next;
  p2->next = NULL;
  return dum1.next;
}

int main(int argc, char** argv) {
  ListNode t1(1);
  ListNode t2(4);
  ListNode t3(3);
  ListNode t4(2);
  ListNode t5(5);
  ListNode t6(2);
  t1.next = &t2;
  t2.next = &t3;
  t3.next = &t4;
  t4.next = &t5;
  t5.next = &t6;
  t6.next = NULL;
  ListNode* h = &t1;

  while (h) {
    cout << h->value << " ";
    h = h->next;
  }
  cout << endl;

  h = &t1;
  h = partitionList(h, 3);
  while (h) {
    cout << h->value << " ";
    h = h->next;
  }
  cout << endl;
  return 0;
}
