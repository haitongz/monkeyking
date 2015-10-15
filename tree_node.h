#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <iostream>
#include <queue>
#include <functional>

using namespace std;

template <typename T>
struct BinTreeNodeT { // binary tree node
  T value;
  BinTreeNodeT* left;
  BinTreeNodeT* right;

  BinTreeNodeT(const T& v)
      : value(v), left(nullptr), right(nullptr) {
  }
};

typedef BinTreeNodeT<int32_t> BinTreeNode;

#define Node BinTreeNodeT<T>

template <typename T>
struct TreeNodeWParentT : public Node {
  TreeNodeWParentT* parent;

  TreeNodeWParentT(const T& v)
      : Node(v), parent(nullptr) {
  }
};

typedef TreeNodeWParentT<uint32_t> TreeNodeWParent;
typedef TreeNodeWParentT<int32_t>  TreeNodeWParent1;

template <typename T>
inline void bfsPrint(const Node* root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const Node*> nodes;
  nodes.push_back(root);
  uint32_t lvl = 0;

  while (!nodes.empty()) {
    cout << "Level " << ++lvl << ": ";
    const uint32_t cp = nodes.size();
    for (uint32_t i = 0; i < cp; ++i) {
      const Node* nd = nodes.front();
      nodes.pop_front();
      cout << "key=" << nd->value << "; ";
      if (nd->left)
        nodes.push_back(nd->left);
      if (nd->right)
        nodes.push_back(nd->right);
    }
    cout << endl;
  }
}

template <typename T>
bool bstInsert_recur(Node** root, const T& key) {
  if (!root)
    return false;

  function<bool(Node**)> solve =
    [&](Node** curr_root) {
    Node*& ptr = *curr_root;
    if (!ptr) {
      ptr = new Node(key);
      return true;
    } else if (ptr->value == key) {
      return false;
    } else if (ptr->value > key) {
      return solve(&(ptr->left));
    } else {
      return solve(&(ptr->right));
    }
  };

  return solve(root);
}

template <typename T>
inline void delTree_iter(Node** root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const Node*> nodes;
  nodes.push_back(*root);
  while (!nodes.empty()) {
    const uint32_t cp = nodes.size();
    for (uint32_t i = 0; i < cp; ++i) {
      const Node* nd = nodes.front();
      nodes.pop_front();
      if (nd->left)
        nodes.push_back(nd->left);
      if (nd->right)
        nodes.push_back(nd->right);
      delete nd;
      nd = NULL;
    }
  }

  *root = NULL;
}

template <typename T>
inline void delTree_recur(Node** root) {
  function<void(Node**)> solve = [&](Node** ndp) { // DFS, postorder
    if (!ndp)
      throw exception();
    else if (*ndp) {
      Node* nd = *ndp;
      solve(&(nd->left));
      solve(&(nd->right));
      delete nd;
      nd = NULL;
    }
  };

  solve(root);
}

template <typename T>
inline bool isLeaf(const Node* node) {
  return (node && !node->left && !node->right);
}

template <typename T>
inline uint32_t height(const Node* root) {
  function<uint32_t(const Node*)> solve =
    [&](const Node* curr_root) -> uint32_t {
    if (!curr_root)
      return 0;
    else {
      // compute the height of each subtree
      uint32_t lheight = height(curr_root->left);
      uint32_t rheight = height(curr_root->right);

      /* use the larger one */
      return (lheight > rheight ? lheight+1 : rheight+1);
    }
  };

  return solve(root);
}

template <typename T>
inline uint32_t height_iter(const Node* root) {
  if (!root)
    return 0;

  // Create an empty queue for level order tarversal
  deque<const Node*> q = {root};
  uint32_t ret = 0;

  while (1) {
    // nodeCount (queue size) indicates number of nodes at current lelvel.
    uint32_t node_cnt = q.size();
    if (!node_cnt)
      return ret;

    ++ret;

    // Dequeue all nodes of current level and Enqueue all nodes of next level
    while (node_cnt > 0) {
      const Node* node = q.front();
      q.pop_front();
      if (node->left)
        q.push_back(node->left);
      if (node->right)
        q.push_back(node->right);

      --node_cnt;
    }
  }
}

/*
Find size of binary tree
 */
template <typename T>
uint32_t count_recur(const Node* root) {
  function<uint32_t(const Node*)> solve =
    [&](const Node* curr_root) -> uint32_t {
    if (!curr_root)
      return 0;

    uint32_t lcnt = solve(curr_root->left);
    uint32_t rcnt = solve(curr_root->right);
    return lcnt+rcnt+1;
  };

  return solve(root);
}

#endif // _TREENODE_H_
