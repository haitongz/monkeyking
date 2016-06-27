#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* rmDups_iter(ListNode* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid arguments!" << endl;
#endif
    return nullptr;
  } else if (!head->next) {
    return nullptr;
  }

  auto p1 = head;
  while (p1) {
    auto p2 = p1->next;
    auto prev = p1;

    while (p2) {
      auto next = p2->next;
      if (p1->value == p2->value) {
        prev->next = next;
        delete p2;
      } else {
        prev = p2;
      }

      p2 = p2->next;
    }

    p1 = p1->next;
  }

  return head;
}

/* O(n2) */
void comparisonSort(ListNode* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  auto p1 = head;

  while (p1) {
    auto p2 = p1->next;
    while (p2) {
      if (p1->value > p2->value) { // ascending sort
        XOR_SWAP(p1->value, p2->value);
      }
      p2 = p2->next;
    }

    p1 = p1->next;
  }
}

int main(int argc, char** argv) {
  ListNode* fir = new ListNode(1);
  ListNode* sec = new ListNode(2);
  ListNode* thi = new ListNode(1);
  ListNode* fou = new ListNode(1);
  fir->next = sec;
  sec->next = thi;
  thi->next = fou;
  fou->next = nullptr;

  auto p = rmDups_iter(fir);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
