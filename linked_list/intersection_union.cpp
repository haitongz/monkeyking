#include <iostream>
#include "list_node.h"

using namespace std;

/*
Write a program to find the node at which the intersection of two singly linked lists begins.

Given
A:          a1 - a2
                  \
                   c1 - c2 - c3
                    \
B:         b1 - b2 - b3
begin to intersect at node c1. Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
 */
/*
Two pointer solution (O(n+m) running time, O(1) memory):
Maintain two pointers pA and pB initialized at the head of A and B, respectively.
Then let them both traverse through the lists, one node at a time.
When pA reaches the end of a list, then redirect it to the head of B; similarly when pB reaches the end of a list, redirect it the head of A.  If at any point pA meets pB, then pA/pB is the intersection node.
 */
const ListNode* intersection(const ListNode* l1, const ListNode* l2) {
  if (!l1 || !l2) {
    return nullptr;
  }

  const ListNode* curr1 = l1;
  const ListNode* curr2 = l2;
  bool reached1 = false, reached2 = false;

  while (curr1 && curr2) {
    if (curr1 == curr2) {
      return curr1;
    } else if (!curr1->next) {
      if (!reached1) { // first list is shorter and this is first iteration
        curr1 = l2;
        reached1 = true;
      } else {
        return nullptr;
      }
    } else if (!curr2->next) {
      if (!reached2) { // second list is shorter and this is first iteration
        curr2 = l1;
        reached2 = true;
      } else {
        return nullptr;
      }
    } else {
      curr1 = curr1->next;
      curr2 = curr2->next;
    }
  }
}

// Find union list of two linked lists: iterate over both lists once to determine the minimum and maximum value. From these values we create a vector. With this vector we iterate over both lists again. For each number n in the list we increase the value in the vector on position n with 1. This makes sure that elements that are in the intersection will have a value of 2 in the vector, elements that are in the union will then have a value of 1. Elements that are absent will have a value of 0. Then the only thing we need to do is iterate over the vector and add the indices that have a value of 2 to the intersection and add the indices that have a value of 1 to the union.
const ListNode* unionList(const ListNode* l1, const ListNode* l2) {
  int /*minVal = MAX_LMT, */maxVal = MIN_LMT;
  ListNode* curr = const_cast<ListNode*>(l1);

  while (curr) {
    //minVal = min(minVal, curr->value);
    maxVal = max(maxVal, curr->value);
    curr = curr->next;
  }

  curr = const_cast<ListNode*>(l2);
  while (curr) {
    //minVal = min(minVal, curr->value);
    maxVal = max(maxVal, curr->value);
    curr = curr->next;
  }

  vector<uint> v(maxVal+1, 0);

  curr = const_cast<ListNode*>(l1);
  while (curr) {
    ++v[curr->value];
    curr = curr->next;
  }
  curr = const_cast<ListNode*>(l2);
  while (curr) {
    ++v[curr->value];
    curr = curr->next;
  }

  ListNode* ret = nullptr;

  for (uint i = 0; i < v.size(); ++i) {
    if (v[i] >= 1) { // union including intersection
      ListNode* ptr = new ListNode(i);
      if (!ret) {
        curr = ptr;
        ret = curr;
      } else {
        curr->next = ptr;
        curr = ptr;
      }
    }
  }

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
  auto n = intersection(&head, 1);
  cout << "Removed " << n << " elements." << endl;

  auto p = head;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
