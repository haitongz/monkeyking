/*
Given a linked list, swap every two adjacent nodes and return its head.
For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.
Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 */
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* swap2Adjacents_iter(ListNode* head) {
  function<void(ListNode*)> swapPair = [](ListNode* currHead) {
    if (!currHead) {
      return;
    }
    auto next = currHead->next;
    if (!next) {
      return;
    }
    auto next2 = next->next;
    if (!next2) {
      return;
    }
    auto next3 = next2->next;
    currHead->next = next2;
    next2->next = next;
    next->next = next3;
  };

  ListNode dummy(0);
  dummy.next = head;
  auto curr = &dummy;

  while (curr) {
    swapPair(curr);

    auto next = curr->next;
    if (!next)
      break;

    auto next2 = next->next;
    curr = next2;
  }

  return dummy.next;
}

// need to fix...
ListNode* swap2Adjacents_recur(ListNode* head) {
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

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  auto p = swap2Adjacents_iter(&fir);
  while (p) {
    cout << p->value << " -> ";
    p = p->next;
  }
  cout << endl;

  p = swap2Adjacents_recur(&fir);
  while (p) {
    cout << p->value << " -> ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
