#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

uint rmTargets_iter(ListNode** head, const int target) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid arguments!" << endl;
#endif
    return 0;
  } else if (!(*head)) {
    return 0;
  }

  uint ret = 0;
  auto curr = *head;
  ListNode* prev = nullptr;

  while (curr) {
    auto next = curr->next;
    if (curr->value == target) {
      delete curr;
      if (!prev) { // delete at head
        *head = next;
      } else {
        prev->next = next;
      }
      ++ret;
    } else {
      prev = curr;
    }

    curr = next;
  }

  return ret;
}

uint rmTargets_recur(ListNode** head, const int target) {
    if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid arguments!" << endl;
#endif
    return 0;
  } else if (!(*head)) {
    return 0;
  }

  uint ret = 0;
  auto curr = *head;

  function<void(ListNode*,ListNode*)> solve =
    [&](ListNode* curr, ListNode* prev) {
    if (!curr)
      return;

    solve(curr->next, curr);

    if (curr->value == target) {
      if (prev) {
        prev->next = curr->next;
      } else {
        *head = curr->next; // delete head node
      }
      delete curr;
      ++ret;
    } else {
      *head = prev;
    }
  };

  solve(*head, nullptr);
  return ret;
}

int main(int argc, char** argv) {
  ListNode* fir = new ListNode(1);
  ListNode* sec = new ListNode(1);
  ListNode* thi = new ListNode(1);
  ListNode* fou = new ListNode(1);
  fir->next = sec;
  sec->next = thi;
  thi->next = fou;
  fou->next = nullptr;

  ListNode* head = fir;
  auto n = rmTargets_recur(&head, 1);
  cout << "Removed " << n << " elements." << endl;

  auto p = head;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
