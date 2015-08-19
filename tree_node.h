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

template <typename T>
struct TreeNodeT : public BinTreeNodeT<T> {
  TreeNodeT* parent;

  TreeNodeT(const T& v)
      : BinTreeNodeT<T>(v), parent(nullptr) {
  }
};

typedef TreeNodeT<uint32_t> TreeNode;
typedef TreeNodeT<int32_t>  TreeNode1;

template <typename T>
inline void bfsPrint(const BinTreeNodeT<T>* root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const BinTreeNodeT<T>*> nodes;
  nodes.push_back(root);
  uint32_t lvl = 0;

  while (!nodes.empty()) {
    cout << "Level " << ++lvl << ": ";
    const uint32_t cp = nodes.size();
    for (uint32_t i = 0; i < cp; ++i) {
      const BinTreeNodeT<T>* nd = nodes.front();
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
inline void delTree_iter(BinTreeNodeT<T>** root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const BinTreeNodeT<T>*> nodes;
  nodes.push_back(*root);
  while (!nodes.empty()) {
    const uint32_t cp = nodes.size();
    for (uint32_t i = 0; i < cp; ++i) {
      const BinTreeNodeT<T>* nd = nodes.front();
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
inline void delTree_recur(BinTreeNodeT<T>** root) {
  function<void(BinTreeNodeT<T>**)> solve = [&](BinTreeNodeT<T>** ndp) { // DFS, postorder
    if (!ndp)
      throw exception();
    else if (*ndp) {
      BinTreeNodeT<T>* nd = *ndp;
      solve(&(nd->left));
      solve(&(nd->right));
      delete nd;
      nd = NULL;
    }
  };

  solve(root);
}

template <typename T>
inline bool isLeaf(const BinTreeNodeT<T>* node) {
  return (node && !node->left && !node->right);
}

template <typename T>
inline uint32_t height(const BinTreeNodeT<T>* root) {
  function<uint32_t(const BinTreeNodeT<T>*)> solve =
    [&](const BinTreeNodeT<T>* curr_root) -> uint32_t {
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
inline uint32_t height_iter(const BinTreeNodeT<T>* root) {
  if (!root)
    return 0;

  // Create an empty queue for level order tarversal
  deque<const BinTreeNodeT<T>*> q = {root};
  uint32_t ret = 0;

  while (1) {
    // nodeCount (queue size) indicates number of nodes at current lelvel.
    uint32_t node_cnt = q.size();
    if (!node_cnt)
      return ret;

    ++ret;

    // Dequeue all nodes of current level and Enqueue all nodes of next level
    while (node_cnt > 0) {
      const BinTreeNodeT<T>* node = q.front();
      q.pop_front();
      if (node->left)
        q.push_back(node->left);
      if (node->right)
        q.push_back(node->right);

      --node_cnt;
    }
  }
}

#endif // _TREENODE_H_
