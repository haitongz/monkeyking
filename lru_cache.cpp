/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 */
#include <iostream>

struct DListNode {
  int32_t    key;
  uint32_t   value;
  DLinkNode* prev;
  DListNode* next;

  DListNode(const int32_t k, const uint32_t v)
      : key(k), value(v), prev(NULL), next(NULL) {
  }
};

class LRUCache {
  private:
    DListNode head_tail;
    map<int32_t,DListNode*> store;
    const uint32_t capacity;

    void insertHead(DListNode*& p) { // construct a circle doubly linked list
      p->next = head_tail.next;
      head_tail.next = p;
      p->prev = &head_tail;
      p->next->prev = p;
    }
    void unchain(DListNode*& t) {
      t->prev->next = t->next;
      t->next->prev = t->prev;
    }

  public:
    LRUCache(const uint32_t c)
        : head_tail(0, 0), capacity(c) {
      if (!c)
        throw exception();

      head_tail.prev = head_tail.next = &head_tail;
    }
    int32_t get(const int32_t key) {
      if (!store.count(key))
        return -1;

      DListNode* t = store[key];
      unchain(t);
      insertHead(t);
      return t->value;
    }
    void set(const int32_t key, const uint32_t v) {
      if (!store.count(key)) {
        if (store.size() >= capacity) {
          DListNode* t = head_tail.prev;
          unchainNode(t);
          store.erase(t->key);
          delete t;
        }

        DListNode* p = new DListNode(key, v);
        insertHead(p);
        store[key] = p;
      } else {
        DListNode* t = store[key];
        t->value = v;
        unchain(t);
        insertHead(t);
      }
    }
};
