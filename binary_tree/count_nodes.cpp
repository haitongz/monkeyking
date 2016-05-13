#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

uint countNodes_iter(const BinTreeNode* root) {
  if (!root) {
    return 0;
  }

  uint ret = 0;
  auto curr = root;
  deque<const BinTreeNode*> lvl {root};

  while (1) {
    const uint sz = lvl.size();
    if (!sz) {
      break;
    }

    for (uint i = 0; i < sz; ++i) {
      ++ret;

      auto nd = lvl.front();
      lvl.pop_front();
      if (nd->left) {
        lvl.push_back(nd->left);
      }
      if (nd->right) {
        lvl.push_back(nd->right);
      }
    }
  }

  return ret;
}

uint countNodes_recur(const BinTreeNode* root) {
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;

    return 1+solve(curr_root->left)+solve(curr_root->right);
  };

  return solve(root);
}

int main(int argc, const char** argv) {
  BinTreeNode* root = new BinTreeNode(-15);
  root->left = new BinTreeNode(5);
  root->right = new BinTreeNode(6);
  root->left->left = new BinTreeNode(-8);
  root->left->right = new BinTreeNode(1);
  root->left->left->left = new BinTreeNode(2);
  root->left->left->right = new BinTreeNode(6);
  root->right->left = new BinTreeNode(3);
  root->right->right = new BinTreeNode(9);
  root->right->right->right = new BinTreeNode(0);
  root->right->right->right->left = new BinTreeNode(4);
  root->right->right->right->right = new BinTreeNode(-1);
  root->right->right->right->right->left = new BinTreeNode(10);

  prettyPrint(root);
  cout << "Size of binary tree: " << countNodes_iter(root) << endl;
  cout << "Size of binary tree: " << countNodes_recur(root) << endl;

  return 0;
}
