/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 */
#include <iostream>
#include <functional>
#include <queue>
#include "list_node.h"

using namespace std;

ListNode* mergeKLists(vector<ListNode*>& lists) {
  const uint32_t k = lists.size();
  if (!k)
    return nullptr;

  auto comp = [](ListNode* x, ListNode* y) {
    return x->value > y->value;
  };

  vector<ListNode*> heap;
  for (auto n : lists)
    if (n)
      heap.push_back(n);

  make_heap(heap.begin(), heap.end(), comp);

  ListNode dummy(0);
  auto curr = &dummy;

  while (!heap.empty()) {
    pop_heap(heap.begin(), heap.end(), comp);

    auto small = heap.back();
    curr->next = small;
    heap.pop_back();

    curr = curr->next;
    small = small->next;
    if (small) {
      heap.push_back(small);
      push_heap(heap.begin(), heap.end(), comp);
    }
  }

  curr->next = nullptr;
  return dummy.next;
}

/*
  Doesn't work
 */
ListNode* mergeKLists2(vector<ListNode*>& lists) {
  const uint32_t k = lists.size();
  if (!k)
    return nullptr;

  auto comp = [](ListNode* x, ListNode* y) {
    return x->value > y->value;
  };

  priority_queue<ListNode*> heap;
  for (uint32_t i = 0; i < k; ++i) {
    ListNode* nd = lists[i];
    if (nd) {
      heap.push(nd);
    }
  }

  ListNode* head = nullptr;
  ListNode* prev = head;

  while (heap.size()) {
    ListNode* curr = heap.top();
    heap.pop();

    if (!head) {
      head = curr;
      prev = head;
    } else {
      prev->next = curr;
    }

    prev = curr;
    if (curr->next)
      heap.push(curr->next);
  }

  return head;
}

int main() {
  ListNode head(0);
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  ListNode fiv(5);
  ListNode six(6);
  ListNode sev(7);
  ListNode eig(8);
  ListNode nin(9);
  ListNode ten(10);
  ListNode da(6);
  ListNode db(9);
  ListNode dc(10);
  ListNode de(19);
  ListNode df(100);

  da.next = &db;
  db.next = &dc;
  dc.next = &de;
  de.next = &df;
  df.next = NULL;
  head.next = &fir;
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = &fiv;
  fiv.next = NULL;
  six.next = &sev;
  sev.next = &eig;
  eig.next = &nin;
  nin.next = &ten;
  ten.next = NULL;

  vector<ListNode*> lists(3);
  lists[0] = &head;
  lists[1] = &six;
  lists[2] = &da;

  ListNode* p = mergeKLists(lists);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;
  return 0;
}
