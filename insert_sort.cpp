/*
Sort a linked list using insertion sort.
*/
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode* insertion_sort(ListNode* head) {
  if (!head || !head->next)
      return head;

  ListNode* res = NULL;

  /* take items off the input list one by one until empty */
  while (head) {
    ListNode* curr = head;
    /* trailing pointer for efficient splice */
    ListNode** trail = &res;
    /* pop head off list */
    head = head->next;

    /* splice head into sorted list at proper place */
    while (!(*trail == NULL || curr->value < (*trail)->value)) {/* does head belong here? */
      /* no - continue down the list */
      trail = &(*trail)->next;
    }

    curr->next = *trail;
    *trail = curr;
  }

  return res;
}

int main(int argc, char** argv) {
  ListNode t1(3);
  ListNode t2(4);
  ListNode t3(1);
  t1.next = &t2;
  t2.next = &t3;
  t3.next = NULL;
  ListNode* l = &t1;

  cout << "Original list:" << endl;
  while (l) {
    cout << l->value <<" ";
    l = l->next;
  }
  cout << endl;

  l = insertion_sort(&t1);

  cout << "Sorted list:" << endl;
  while (l) {
    cout << l->value << " ";
    l = l->next;
  }
  cout << endl;
  return 0;
}
