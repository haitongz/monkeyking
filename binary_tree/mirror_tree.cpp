#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

/*
Mirror of a tree is another binary tree with
left and right children of all non-leaf nodes interchanged.
 */
void mirror(BinTreeNode* root) {
  function<void(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) { // postorder
    if (!curr_root)
      return;

    solve(curr_root->left);
    solve(curr_root->right);

    BinTreeNode* tmp = curr_root->left;
    curr_root->left = curr_root->right;
    curr_root->right = tmp;
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

  cout << "Original binary tree:" << endl;
  prettyPrint(root);
  cout << "Mirror tree:" << endl;
  mirror(root);
  prettyPrint(root);

  return 0;
}
