#include <iostream>
#include <vector>
#include <functional>

#include "bintree_node.h"

using namespace std;

vector<string> allR2LPaths(const BinTreeNode* root) {
  vector<string> ret;

  function<void(const BinTreeNode*,const string&)> solve =
    [&](const BinTreeNode* currRoot, const string& currPath) {
    if (!currRoot) {
      return;
    }

    string newPath = currPath;
    if (!newPath.empty()) {
      newPath += "->";
    }
    newPath += to_string(currRoot->value);

    if (isLeaf(currRoot)) {
      ret.push_back(newPath);
    } else {
      solve(currRoot->left, newPath);
      solve(currRoot->right, newPath);
    }
  };

  solve(root, "");
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

  vector<string> res = allR2LPaths(root);
  for (const auto& s : res) {
    cout << s << endl;
  }

  return 0;
}
