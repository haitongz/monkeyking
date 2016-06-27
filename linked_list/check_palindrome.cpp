#include <iostream>
#include <functional>
#include <stack>
#include "list_node.h"

using namespace std;

/*
Given a singly linked list of characters, write a function that returns true if the given list is palindrome, else false.
 */
#if 0
bool compareLists(const ListNode* head1, const ListNode* head2) {
  auto tmp1 = head1;
  auto tmp2 = head2;

  while (tmp1 && tmp2) {
    if (tmp1->value == tmp2->value) {
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    } else {
      return false;
    }
  }

  if (!tmp1 && !tmp2)
    return true;

  return false;
}

bool isPalindrome_iter(ListNode* head) {
  auto slow = head;
  auto fast = head;
  ListNode* second_half;
  auto prev_of_slow = head;
  ListNode* mid = nullptr; // To handle odd size list
  bool ret = true; // initialize result

  if (head && head->next) {
    while (fast && fast->next) {
      fast = fast->next->next;

      /* need previous of the slow_ptr for linked lists  with odd elements */
      prev_of_slow = slow;
      slow = slow->next;
    }

    /* fast would become NULL when there are even elements in list. And not NULL for odd elements.
       We need to skip the middle node for odd case and store it somewhere so that we can restore the original list*/
    if (fast) {
      mid = slow;
      slow = slow->next;
    }

    // reverse the second half and compare it with first half
    second_half = slow;
    prev_of_slow->next = nullptr; // NULL terminate first half
    reverse_iter(&second_half);  // Reverse the second half
    ret = compareLists(head, second_half); // compare

    /* Construct the original list back */
    reverse_iter(&second_half); // Reverse the second half again
    if (mid) { // If there was a mid node (odd size case) which was not part of either first half or second half.
      prev_of_slow->next = mid;
      mid->next = second_half;
    } else
      prev_of_slow->next = second_half;
  }

  return ret;
}
#endif

bool checkPalindrome_recur(ListNode* head) {
  stack<ListNode*> prevs({nullptr});

  auto curr = head;
  while (curr) {
    prevs.push(curr);
    curr = curr->next;
  }

  auto last = prevs.top();
  prevs.pop();

  function<bool(ListNode*,ListNode*)> solve =
    [&](ListNode* start, ListNode* end) {
    auto prev = prevs.top();
    prevs.pop();

    if (start->next == prev || start == prev) // only 2 or 3 nodes left
      return start->value == end->value;

    return (start->value == end->value) ? solve(start->next, prev) : false;
  };

  return solve(head, last);
}

int main(int argc, char** argv) {
  ListNode fir('a');
  ListNode sec('b');
  ListNode thi('b');
  ListNode fou('a');
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  bool f = checkPalindrome_recur(&fir);
  cout << "The list is" << (f ? " " : "not ") << "palindrome." << endl;

  return 0;
}
