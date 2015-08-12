/*
Given a linked list, swap every two adjacent nodes and return its head.
For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.
Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
 */
#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

ListNode* swapPairs_iter(ListNode* head) {
  function<void(ListNode*)> swap_ = [](ListNode* nd) {
    auto next = nd->next;
    if (!nd || !next || !next->next)
      return;

    auto next2 = next->next;
    auto next3 = next2->next; // ok since next2 has been checked already
    nd->next = next2;
    next2->next = next;
    next->next = next3;
  };

  ListNode dummy(0);
  dummy.next = head;
  auto curr = &dummy;

  while (curr) {
    swap_(curr);

    auto next = curr->next;
    if (!next)
      break;

    auto next2 = next->next;
    curr = next2;
  }

  return dummy.next;
}
/*
ListNode* swap_pairs(const ListNode* head) {
  if (!head || !head->next)
    return;

  ListNode dummy(0);
  dummy.next = head;
  ListNode* prev = &dummy;
  ListNode* curr = head;
  ListNode* next = curr->next;

  while (curr && next) {
    ListNode* tmp = next->next;
    prev->next = next;
    next->next = curr;
    curr->next = tmp;
    prev = curr;
    curr = tmp;
    next = curr->next;
  }

  return dummy.next;
}
*/
ListNode* swapPairs_recur(ListNode* head) {
  function<ListNode*(ListNode*)> dfs = [&](ListNode* curr) {
    if (curr && curr->next) {
      auto next = curr->next;
      auto next2 = next->next;
      ListNode* cp = curr;
      curr = next;
      curr->next = cp;
      cp->next = dfs(next2);
    }

    return curr;
  };

  return dfs(head);
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

  cout << "Original list: " << endl;
  ListNode* curr = &fir;
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  cout << "Iterative swap: " << endl;
  curr = swapPairs_iter(&fir);
  ListNode* cp = curr;
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  cout << "Recursive swap: " << endl;
  curr = swapPairs_recur(cp);
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  return 0;
}
