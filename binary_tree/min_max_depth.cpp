#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

/*
Given a binary tree, find its minimum/maximum depth.
The minimum/maximum depth is the number of nodes along
the shortest/longest path from the root node down to
the nearest/farest leaf node.
 */
uint minDepth_recur(const BinTreeNode* root) {
  if (!root) {
    return 0;
  }

  uint ret = UNSIGNED_MAX;

  function<void(const BinTreeNode*,uint)> solve =
    [&](const BinTreeNode* currRoot, uint curr_depth) {
    ++curr_depth;
    if (!currRoot->left && !currRoot->right) {
      ret = min(curr_depth, ret);
    }
    if (currRoot->left) {
      solve(currRoot->left, curr_depth);
    }
    if (currRoot->right) {
      solve(currRoot->right, curr_depth);
    }
  };

  solve(root, 0);
  return ret;
}

/*
   doesn't work
uint minDepth_recur2(const BinTreeNode* root) {
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* currRoot) -> uint {
    if (!currRoot)
      return 0;

    uint lheight = currRoot->left ? solve(currRoot->left) : UNSIGNED_MAX;
    uint rheight = currRoot->right ? solve(currRoot->right) : UNSIGNED_MAX;
    return min(lheight, rheight)+1;
  };

  return solve(root);
}
 */
uint maxDepth_recur(const BinTreeNode* root) {
  if (!root) {
    return 0;
  }

  uint ret = 0;

  function<void(const BinTreeNode*,uint)> solve =
    [&](const BinTreeNode* currRoot, uint curr_depth) {
    ++curr_depth;
    if (!currRoot->left && !currRoot->right) {
      ret = max(curr_depth, ret);
    }
    if (currRoot->left) {
      solve(currRoot->left, curr_depth);
    }
    if (currRoot->right) {
      solve(currRoot->right, curr_depth);
    }
  };

  solve(root, 0);
  return ret;
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
  cout << "Min depth of tree is " << minDepth_recur(root) << endl;
  cout << "Max depth of tree is " << maxDepth_recur(root) << endl;

  return 0;
}
