#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* sortedInsert(ListNode** head, int v) {
  if (!head) {
    return nullptr;
  } else if (!*head) {
    *head = new ListNode(v);
    return *head;
  }

  auto curr = *head;
  ListNode* prev = nullptr;

  while (curr) {
    if (curr->value < v) {
      prev = curr;
      curr = curr->next;
    } else {
      ListNode* nd = new ListNode(v);
      nd->next = curr;
      if (!prev) { // this is head
        *head = nd;
      } else {
        prev->next = nd;
      }
      return *head;
    }
  }
}

ListNode* sortedRmDups(ListNode** head) {
  if (!head || !*head) {
    return nullptr;
  }

  auto curr = head;
  while (curr) {
    auto next = curr->next;
    while (next) {
      auto next2 = next->next;
      if (curr->value == next->value) {
        delete next;
        curr->next = next2;
      }
      next = next2;
    }
    curr = curr->next;
  }
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

  ListNode* head = &fir;
  auto p = sortedInsert(&head, 0);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
