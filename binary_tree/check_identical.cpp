#include <iostream>
#include <functional>

#include "bintree_node.h"

using namespace std;

/*
Two trees are identical when they have same data and arrangement of data is also same.

To identify if two trees are identical, we need to traverse both trees simultaneously,
and while traversing we need to compare data and children of the trees.
 */
uint areIdentical_recur(const BinTreeNode* root1, const BinTreeNode* root2) {
  function<bool(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) {
    if (!curr_root1 && !curr_root2)
      return true;
    else if ((curr_root1 && !curr_root2) ||
             (!curr_root1 && curr_root2) ||
             (curr_root1->value != curr_root2->value)) {
      return false;
    }

    return solve(curr_root1->left, curr_root2->left) &&
           solve(curr_root1->right, curr_root2->right);
  };

  return solve(root1, root2);
}

int main(int argc, const char** argv) {
  BinTreeNode* root1 = new BinTreeNode(-15);
  root1->left = new BinTreeNode(5);
  root1->right = new BinTreeNode(6);
 // prettyPrint(root1);

  BinTreeNode* root2 = new BinTreeNode(-15);
  root2->left = new BinTreeNode(5);
  root2->right = new BinTreeNode(6);
 // prettyPrint(root2);

  cout << "Two empty trees are " << (areIdentical_recur(nullptr, nullptr) ? "identical." : "not identical.") << endl;
  cout << "Two trees are " << (areIdentical_recur(nullptr, root2) ? "identical." : "not identical.") << endl;
  cout << "Two trees are " << (areIdentical_recur(root1, root2) ? "identical." : "not identical.") << endl;

  root2->left->left = new BinTreeNode(2);
  cout << "Two trees are " << (areIdentical_recur(root1, root2) ? "identical." : "not identical.") << endl;

  return 0;
}
