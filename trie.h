#ifndef _TRIE_H_
#define _TRIE_H_

#include <cassert>
#include <functional>

using namespace std;

/*
Insert and search costs O(key_length), however the memory requirements of trie
is O(ALPHABET_SIZE*key_length*N) where N is number of keys in trie.
 */
struct Trie {
  enum Consts {
    ALPHA_NUM = 26
  };

  struct Node {
    Node(char v) : value {v} {
    }
    ~Node() {
      for (uint8_t i = 0; i < ALPHA_NUM+1; ++i) {
        if (children[i]) {
          delete children[i];
          children[i] = nullptr;
        }
      }
    }
    Node* get(char c, bool auto_create = true) {
      assert((c >= 'a' && c <= 'z') || c == '\0');
      uint8_t idx = (c == '\0') ? ALPHA_NUM : (c-'a');
      if (!children[idx] && auto_create) {
        children[idx] = new Node(c);
        children[idx]->parent = this;
        ++children_num;
      }

      return children[idx];
    }
    bool end() {
      return get('\0', false);
    }

    uint32_t children_num {0};
    char value {'\0'};
    Node* parent {nullptr};
    Node* children[ALPHA_NUM+1] {nullptr}; // one more for '\0'
  };
  Trie() {
    root = new Node('\0');
  }
  ~Trie() {
    if (root) {
      delete root;
      root = nullptr;
    }
  }
  void add(const string& s) {
    auto nd = root;
    for (auto c : s) {
      nd = nd->get(c);
    }
    nd->get('\0');
  }
  bool search(const string& key) {
    const uint32_t len = key.length();
    if (!len)
      return false;

    Node* nd = root;
    for (uint32_t i = 0; i < len; ++i) {
      uint8_t idx = key[i]-'a';
      if (!nd->children[idx])
        return false;
      nd = nd->children[idx];
    }
    return (nd && nd->children_num);
  }
  bool wildcardSearch(const string& key) { // doesn't work after deleteKey("the")
    const uint32_t len = key.length();
    if (!len)
      return false;

    function<bool(Node*,const uint32_t)> solve = // DFS
      [&](Node* curr, const uint32_t idx) {
      if (!curr || !curr->children_num)
        return false;
      if (idx == len && curr->children[ALPHA_NUM]) // last char except '\0'
        return true;

      char c = key[idx];
      if (c == '*') {
        for (uint8_t i = 0; i < ALPHA_NUM; ++i) {
          Node* new_nd = curr->children[i];
          if (new_nd && solve(new_nd, idx+1))
            return true;
        }
        return false;
      } else {
        Node* new_nd = curr->children[c-'a'];
        return new_nd ? solve(new_nd, idx+1) : false;
      }
    };

    return solve(root, 0);
  }
  bool isFree(Node* nd) {
    for (uint32_t i = 0; i < ALPHA_NUM; ++i) {
      if (nd->children[i])
        return false;
    }

    return true;
  }
  bool isLeaf(Node* nd) {
    return !nd->children_num;
  }
  /*
   1. Key may not be there in trie. Delete operation should not modify trie.
   2. Key present as unique key (no part of key contains another key (prefix),
      nor the key itself is prefix of another key in trie). Delete all the nodes.
   3. Key is prefix key of another long key in trie. Unmark the leaf node.
   4. Key present in trie, having atleast one other key as prefix key.
      Delete nodes from end of key until first leaf node of longest prefix key.
   */
  void deleteKey(const string& key) {
    const uint32_t len = key.length();
    if (!len)
      return;

    function<bool(Node*,const uint32_t)> solve = // DFS
      [&](Node* curr, const uint32_t idx) {
      if (curr) {
        if (idx == len) {
          if (curr->children_num) { // unmark leaf node
            curr->children_num = 0;
            return isFree(curr);
          }
        } else {
          uint8_t new_idx = key[idx]-'a';
          if (solve(curr->children[new_idx], idx+1)) {
            // last node marked, delete it
            delete curr->children[new_idx];
            curr->children[new_idx] = nullptr;
            // recursively climb up, and delete eligible nodes
            return !isLeaf(curr) && isFree(curr);
          }
        }
      }
    };

    solve(root, 0);
  }

  Node* root {nullptr};
};

#endif // _TRIE_H_
