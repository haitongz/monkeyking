/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
 */
#include <iostream>
#include <cstring>
#include "list_node.h"

using namespace std;

ListNode* addTwoNums(const ListNode* l1, const ListNode* l2) {
  ListNode* sumList = new ListNode(-1);
  ListNode* curr = sumList;

  uint8_t carry = 0;
  while (l1 || l2 || carry) {
    int32_t l1val = !l1 ? 0 : l1->value;
    int32_t l2val = !l2 ? 0 : l2->value;
    int32_t sum = l1val+l2val+carry;
    carry = sum/10; // 0 or 1
    sum %= 10;

    curr->next = new ListNode(sum);
    curr = curr->next;
    l1 = !l1 ? NULL : l1->next;
    l2 = !l2 ? NULL : l2->next;
  }

  ListNode* res = sumList->next;
  delete sumList;
  return res;
}

int main(int argc, char** argv) {
  ListNode h1(2), f1(4), s1(3), h2(5), f2(6), s2(4);
  h1.next = &f1;
  f1.next = &s1;
  h2.next = &f2;
  f2.next = &s2;

  const ListNode* l1 = &h1;
  const ListNode* l2 = &h2;
  const ListNode* res = addTwoNums(&h1, &h2);
  while (res) {
    cout << res->value;
    res = res->next;
  }
  cout << endl;
}
