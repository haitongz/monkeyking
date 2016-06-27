#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

/*
MergeSort a linked list in O(nlogn) time using constant space complexity.
 */
ListNode* merge(ListNode* l1, ListNode* l2) {
  ListNode dummy(0);
  auto curr = &dummy;

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

ListNode* mergeSort_recur(ListNode* head) {
  function<ListNode*(ListNode*)> solve =
    [&](ListNode* currHead) {
    if (!currHead || !currHead->next) {
      return currHead;
    }

    auto slow = currHead;
    auto fast = currHead;
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    fast = slow->next;
    slow->next = nullptr;
    currHead = solve(currHead);
    fast = solve(fast);
    return merge(currHead, fast);
  };

  return solve(head);
}

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(6);
  ListNode thi(3);
  ListNode fou(2);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  auto p = mergeSort_recur(&fir);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
