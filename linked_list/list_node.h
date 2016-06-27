#pragma once

#include <limits>
#include <functional>

using namespace std;

static const int SIGNED_MAX = numeric_limits<int>::has_infinity ?
                              numeric_limits<int>::infinity() : numeric_limits<int>::max();

static const int SIGNED_MIN = numeric_limits<int>::has_infinity ?
                              -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();

struct ListNode {
  ListNode(const int v)
    : value(v)
    , next(nullptr) {
  }

  int value;
  ListNode* next;
};

ListNode* tail(ListNode* head) {
  if (!head) {
    return nullptr; // or report error?
  }

  auto curr = head;
  auto ret = curr;

  while (curr) {
    ret = curr; // record previous node
    curr = curr->next;
  }

  return ret;
}

const ListNode* middle_iter(const ListNode* head) {
  if (!head)
    return nullptr;

  auto slow = head;
  auto fast = head;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow;
}

#define XOR_SWAP(a, b)\
do {\
  a ^= b;\
  b ^= a;\
  a ^= b;\
} while (0)

void push(ListNode** head, const int v) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
#endif
    return;
  }

  ListNode* nd = new ListNode(v);
  nd->next = *head;
  *head = nd;
}

ListNode* pop(ListNode** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
    return nullptr;
#endif
    return nullptr;
  } else if (!*head) {
    return nullptr;
  }

  auto ret = *head;
  //assert(tmp);
  *head = ret->next;
  return ret;
}

uint length_iter(const ListNode* head) {
  uint ret = 0;
  auto curr = head;
  while (curr) {
    ++ret;
    curr = curr->next;
  }
  return ret;
}

uint length_recur(const ListNode* head) {
  function<uint(const ListNode*)> solve =
    [&](const ListNode* curr_head) -> uint {
    if (!curr_head)
      return 0;

    return 1+solve(curr_head->next);
  };

  return solve(head);
}

bool search_iter(const ListNode* head, const int target) {
  auto curr = head;
  while (curr) {
    if (curr->value == target)
      return true;
  }

  return false;
}

bool search_recur(const ListNode* head, const int target) {
  function<bool(const ListNode*)> solve =
    [&](const ListNode* curr_head) {
    if (!curr_head)
      return false;
    else if (curr_head->value == target)
      return true;
    else
      return solve(curr_head->next);
  };

  return solve(head);
}

void print(const ListNode* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  uint i = 0;
  while (head) {
    cout << "Node[" << i++ << "] = " << head->value << endl;
    head = head->next;
  }
}

/**
 * Delete whole list and set the head pointer to NULL
 */
void delete_iter(ListNode** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
#endif
    return;
  }

  auto curr = *head;
  while (curr) {
    auto next = curr->next;
    delete curr;
    curr = next;
  }

  *head = nullptr;
}

void delete_recur(ListNode** head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Invalid argument!" << endl;
#endif
    return;
  }

  function<void(ListNode*&)> solve =
    [&](ListNode*& curr_head) {
    if (!curr_head) {
      return;
    } else if (!curr_head->next) {
      delete curr_head;
      curr_head = nullptr;
      return;
    } else {
      solve(curr_head->next);
    }
  };

  solve(*head);
}
