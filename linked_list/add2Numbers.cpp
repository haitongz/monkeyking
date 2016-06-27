/*
You are given two linked lists representing two non-negative numbers.
The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
 */
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* add2Numbers(ListNode* l1, ListNode* l2) {
  if (!l1)
    return l2;
  else if (!l2)
    return l1;

  ListNode dummy(-1);
  auto curr = &dummy;
  uint carry = 0;

  while (l1 || l2 || carry) {
    uint n1 = l1 ? l1->value : 0;
    uint n2 = l2 ? l2->value : 0;
    uint sum = n1+n2+carry;
    curr->next = new ListNode(sum%10);

    carry = sum/10;

    l1 = l1 ? l1->next : nullptr;
    l2 = l2 ? l2->next : nullptr;
    curr = curr->next;
  }

  ListNode* ret = const_cast<ListNode*>(dummy.next);
  return ret;
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
