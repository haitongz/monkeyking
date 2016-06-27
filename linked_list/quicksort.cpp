#include <iostream>
#include <functional>
#include "list_node.h"

using namespace std;

/*
MergeSort a linked list in O(nlogn) time using constant space complexity.
 */
ListNode* partition(ListNode* head,
                    ListNode* end,
                    ListNode** newHead,
                    ListNode** newEnd) {
  auto pivot = end;
  ListNode* prev = nullptr;
  auto curr = head;
  auto tail = pivot;

  // During partition, both the head and end of the list might change which is updated in the newHead and newEnd variables
  while (curr != pivot) {
    if (curr->value < pivot->value) {
      // First node that has a value less than the pivot - becomes the new head
      if (!(*newHead)) {
        (*newHead) = curr;
      }

      prev = curr;
      curr = curr->next;
    } else { // If curr node is greater than pivot, move cur node to next of tail, and change tail
      if (prev) {
        prev->next = curr->next;
      }

      auto tmp = curr->next;
      curr->next = nullptr;
      tail->next = curr;
      tail = curr;
      curr = tmp;
    }
  }

  // If the pivot data is the smallest element in the current list, pivot becomes the head
  if (!(*newHead)) {
    (*newHead) = pivot;
  }

  (*newEnd) = tail;

  return pivot;
}

void quickSort_recur(ListNode** head) {
  function<ListNode*(ListNode*,ListNode*)> solve =
    [&](ListNode* currHead, ListNode* end) { // sorting happens exclusive of the end node
    // base condition
    if (!currHead || currHead == end) {
        return currHead;
    }

    ListNode* newHead = nullptr, *newEnd = nullptr;

    // Partition the list, newHead and newEnd will be updated by the partition function
    auto pivot = partition(currHead, end, &newHead, &newEnd);

    // If pivot is the smallest element - no need to recur for the left part.
    if (newHead != pivot) {
      // Set the node before the pivot node as NULL
      auto tmp = newHead;
      while (tmp->next != pivot) {
        tmp = tmp->next;
      }
      tmp->next = nullptr;

      // Recur for the list before pivot
      newHead = solve(newHead, tmp);

      // Change next of last node of the left half to pivot
      tmp = tail(newHead);
      tmp->next = pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = solve(pivot->next, newEnd);
    return newHead;
  };

  *head = solve(*head, tail(*head));
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

  auto p = &fir;
  quickSort_recur(&p);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  return 0;
}
