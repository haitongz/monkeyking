#ifndef _LISTNODE_H_
#define _LISTNODE_H_

#include <iostream>

using namespace std;

template <typename T>
struct ListNodeT {
  ListNodeT(const T& v)
      : value(v), next(NULL) {
  }
  T value;
  ListNodeT* next;
};

typedef ListNodeT<int32_t> ListNode;

template <typename T>
struct DListNodeT {
  T value;
  DListNodeT<T>* prev;
  DListNodeT<T>* next;

  DListNodeT(const T& v)
      : value(v), prev(nullptr), next(nullptr) {
  }
};

typedef DListNodeT<int32_t> DListNode;

#endif // _LISTNODE_H_
