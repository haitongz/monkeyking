#include <iostream>

using namespace std;

struct DLLNode {
  int value;
  DLLNode* prev;
  DLLNode* next;

  DLLNode(const int v)
    : value(v), prev(nullptr), next(nullptr) {
  }
};

void reverse(DLLNode** head_ref) {
  if (!head_ref || !*head_ref)
    return;

  DLLNode* prev = nullptr;
  DLLNode* curr = *head_ref;

  while (curr) {
    prev = curr->prev;
    curr->prev = curr->next;
    curr->next = prev;
    curr = curr->prev;
  }

  if (prev)
    *head_ref = prev->prev;
}

void push(DLLNode** head_ref, int value) {
  DLLNode* new_node = new DLLNode(value);
  new_node->next = (*head_ref);
  if (*head_ref)
    (*head_ref)->prev = new_node;
  (*head_ref) = new_node;
}

int main(int argc, char** argv) {
  DLLNode* head = nullptr;
  push(&head, 2);
  push(&head, 4);
  push(&head, 8);
  push(&head, 10);

  cout << "Original list:" << endl;
  DLLNode* curr = head;
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  reverse(&head);
  cout << "Reversed list:" << endl;
  curr = head;
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  return 0;
}
