#pragma once

#include <limits>
#include <deque>

using namespace std;

static const int MAX_LMT = numeric_limits<int>::has_infinity ?
                           numeric_limits<int>::infinity() : numeric_limits<int>::max();

static const int MIN_LMT = numeric_limits<int>::has_infinity ?
                           -1*numeric_limits<int>::infinity() : numeric_limits<int>::min();

struct BinTreeNode { // binary tree node
  int value;
  BinTreeNode* left;
  BinTreeNode* right;

  BinTreeNode(const int v)
      : value(v)
      , left(nullptr)
      , right(nullptr) {
  }
};

uint maxHeight_recur(const BinTreeNode* root) {
  if (!root)
    return 0;

  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;

    return 1 + max(solve(curr_root->left), solve(curr_root->right));
  };

  return solve(root);
}

uint maxHeight_iter(const BinTreeNode* root) {
  if (!root)
    return 0;

  // Create an empty queue for level order tarversal
  deque<const BinTreeNode*> q = {root};
  uint ret = 0;

  while (1) {
    // count (queue size) indicates number of nodes at current lelvel.
    uint count = q.size();
    if (!count)
      return ret;

    ++ret;

    // Dequeue all nodes of current level and Enqueue all nodes of next level
    while (count > 0) {
      const BinTreeNode* nd = q.front();
      q.pop_front();
      if (nd->left)
        q.push_back(nd->left);
      if (nd->right)
        q.push_back(nd->right);

      --count;
    }
  }
}

void prettyPrint(const BinTreeNode* root, uint spaces = 2) {
  deque<const BinTreeNode*> q {root};
  uint height = maxHeight_recur(root);
  uint currLvlNodes = 1, nextLvlNodes = 0, level = 1;
  uint padding = spaces * (pow(2, height-level) - 1);

  cout << setw(padding/2) << "";

  while (level <= height) {
    cout << setw(spaces);

    if (q.front()) {
      cout << q.front()->value;
      q.push_back(q.front()->left);
      q.push_back(q.front()->right);
    } else {
      cout << " ";
      q.push_back(nullptr);
      q.push_back(nullptr);
    }

    nextLvlNodes += 2;
    cout << setw(padding) << "";
    q.pop_front();

    // go to next level
    if (--currLvlNodes == 0) {
      currLvlNodes = nextLvlNodes;
      nextLvlNodes = 0;
      ++level;
      padding = spaces * (pow(2, height-level) - 1);
      cout << endl << setw(padding/2) << "";
    }
  }
}
