#include <iostream>
#include "list_node.h"

using namespace std;

template <typename T>
void removeDupsFromSortedList(ListNodeT<T>* head) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return;
  }

  ListNodeT<T>* curr = head;
  while (curr) {
    ListNodeT<T>* next = curr->next;
    while (next) {
      ListNodeT<T>* next2 = next->next;
      if (curr->value == next->value) {
        delete next;
        curr->next = next2;
      }
      next = next2;
    }
    curr = curr->next;
  }
}


int main(int argc, char** argv) {
}
