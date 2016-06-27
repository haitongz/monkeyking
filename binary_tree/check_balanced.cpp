/*
Check a binary tree is height balanced or not
 */
#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

bool checkHeightBalanced(const BinTreeNode* root) {
  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* currRoot) {
    if (!currRoot)
      return 0;

    int left = solve(currRoot->left);
    if (left == -1)
      return -1;

    int right = solve(currRoot->right);
    if (right == -1)
      return -1;

    if (abs(left-right) > 1) {
      return -1;
    } else {
      return 1+max(left, right);
    }
  };

  return solve(root) != -1;
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

  cout << (checkHeightBalanced(root) ? "Balanced" : "Not balanced") << endl;

  return 0;
}
