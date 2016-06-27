#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

/*
Given a binary tree (not a binary search tree) and two values say n1 and n2,
write a program to find the least common ancestor.
 */
const BinTreeNode* LCA(const BinTreeNode* root, const int v1, const int v2) {
  if (!root) {
    return nullptr;
  }

  int target = SIGNED_MIN;
  vector<const BinTreeNode*> to_ext;

  function<bool(const BinTreeNode*)> solve = // backtracking
    [&](const BinTreeNode* currRoot) {
    if (!currRoot) {
      return false;
    }

    to_ext.push_back(currRoot);

    if (currRoot->value == target ||
        solve(currRoot->left) ||
        solve(currRoot->right)) {
      return true;
    }

    to_ext.pop_back(currRoot);
    return false;
  };

  vector<const BinTreeNode*> path1;
  target = v1;
  bool found = solve(root);
  if (!found) {
    return nullptr;
  } else {
    path1 = to_ext;
  }

  vector<const BinTreeNode*> path2;
  target = v2;
  found = solve(root);
  if (!found) {
    return nullptr;
  } else {
    path2 = to_ext;
  }

  uint i = 0;
  for (; i < path1.size() && path1[i] == path2[i]; ++i);

  return i > 0 ? path1[i-1] : nullptr;
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
  cout << "Number of leaves in binary tree: " << countLeaves_recur(root) << endl;

  return 0;
}
