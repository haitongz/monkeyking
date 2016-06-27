#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

/*
Merge two sorted lists
 */
void move(ListNode** dst_ref, ListNode** src_ref) {
  auto new_nd = *src_ref;
  //assert(new_nd);

  *src_ref = new_nd->next;
  new_nd->next = *dst_ref;
  *dst_ref = new_nd;
}

ListNode* merge2Sorted_iter(ListNode* a, ListNode* b) {
  ListNode* ret = nullptr;
  auto last_ref = &ret;

  while (true) {
    if (!a) {
      *last_ref = b;
      break;
    } else if (!b) {
      *last_ref = a;
      break;
    }

    if (a->value <= b->value) {
      move(last_ref, &a);
    } else {
      move(last_ref, &b);
    }

    /* tricky: advance to point to the next ".next" field */
    last_ref = &((*last_ref)->next);
  }

  return ret;
}

ListNode* merge2Sorted_recur(ListNode* a, ListNode* b) {
  function<ListNode*(ListNode*,ListNode*)> solve =
    [&](ListNode* curr_head1, ListNode* curr_head2) {
    if (!curr_head1)
      return curr_head2;
    else if (!curr_head2)
      return curr_head1;

    ListNode* ret = nullptr;
    if (curr_head1->value <= curr_head2->value) {
      ret = curr_head1;
      ret->next = solve(curr_head1->next, curr_head2);
    } else {
      ret = curr_head2;
      ret->next = solve(curr_head1, curr_head2->next);
    }

    return ret;
  };

  return solve(a, b);
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

  ListNode fir2(1);
  ListNode sec2(2);
  ListNode thi2(3);
  ListNode fou2(4);
  fir2.next = &sec2;
  sec2.next = &thi2;
  thi2.next = &fou2;
  fou2.next = nullptr;

  /*
  auto p = merge2Sorted_iter(&fir, &fir2);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
 */
  auto p = merge2Sorted_recur(&fir, &fir2);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
