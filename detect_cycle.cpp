#include <iostream>
#include "list_node.h"

#if 0
ListNode* detectCycle(ListNode* head) {
  if (!head || !head->next)
    return NULL;

  ListNode* slow = head->next;
  ListNode* fast = head->next->next;
  while (fast && fast != slow) {
    slow = slow->next;
    fast = fast->next ? fast->next->next : fast->next;
  }
  if (!fast)
    return nullptr;

  for (fast = head; fast != slow; fast = fast->next)
    slow = slow->next;

  return slow;
}
#endif

/*
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/
bool hasCycle(ListNode* head) {
  ListNode* fast = head;
  ListNode* slow = head;
  while (fast) {
    slow = slow->next;
    fast = fast->next;
    if (fast)
      fast = fast->next;
    if (fast && slow == fast)
      return true;
  }

  return false;
}

/*
Given a linked list, return where cycle begins if there's a cycle; return NULL if there's no cycle.

Follow up:
Can you solve it without using extra space?
*/
bool find(ListNode* head, ListNode* test) {
  ListNode* p = head;
  while (p != test->next) {
    if (p == test)
      return false;
    p = p->next;
  }

  return true;
}

ListNode* detectCycle(ListNode* head) {
  if (!head)
    return NULL;

  ListNode* curr = head;
  while (curr) {
    if (find(head, curr))
      return curr->next;
    curr = curr->next;
  }

  return NULL;
}

/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
Can you solve it without using extra space?
*/
/*
ListNode* cycleBeginsAt(const ListNode* head) {
  if (!head || !head->next)
    return NULL;

  ListNode* p1 = head;
  ListNode* p2 = head;
  bool cycle_exists = false;

  while (p1 && p2) {
    p1 = p1->next;
    if (!p2->next)
      return NULL;
    p2 = p2->next->next;
    if (p1 == p2) {
      cycle_exists = true;
      break;
    }
  }

  if (!cycle_exists)
    return NULL;

  p1 = head;
  while (p1 != p2) {
    p1 = p1->next;
    p2 = p2->next;
  }

  return p1;
}
*/
int main(int argc, char** argv) {
}
