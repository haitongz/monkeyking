#include <iostream>
#include <functional>
#include <stack>
#include <vector>
#include <queue>

#include "bintree_node.h"

using namespace std;

/*
Given a binary tree, print boundary nodes of the binary tree Anti-Clockwise
starting from the root.
For example, boundary traversal of the following tree is "20 8 4 10 14 25 22"
 */
void boundary_recur(const BinTreeNode* root) {
  if (!root)
    return;

  cout << root->value << " ";

  function<void(const BinTreeNode*)> leaves =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    leaves(curr_root->left);
    if (!curr_root->left && !curr_root->right)
      cout << curr_root->value << " ";

    leaves(curr_root->right);
  };

  function<void(const BinTreeNode*)> leftBoundary =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;
    if (curr_root->left) {
      // to ensure top down order,
      // print the node before calling itself for left subtree
      cout << curr_root->value << " ";
      leftBoundary(curr_root->left);
    } else if (curr_root->right) {
      cout << curr_root->value << " ";
      leftBoundary(curr_root->right);
    }
    // do nothing if it is a leaf node, this way we avoid
    // duplicates in output
  };

  // Print the nodes in BOTTOM UP manner
  function<void(const BinTreeNode*)> rightBoundary =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;
    if (curr_root->right) {
      // to ensure bottom up order, first call for right subtree, then print this node
      rightBoundary(curr_root->right);
      cout << root->value << " ";
    } else if (curr_root->left) {
      rightBoundary(curr_root->left);
      cout << root->value << " ";
    }
    // do nothing if it is a leaf node, this way we avoid
    // duplicates in output
  };

  // Print the left boundary in top-down manner.
  leftBoundary(root->left);
  // Print all leaf nodes
  leaves(root->left);
  leaves(root->right);
  // Print the right boundary in bottom-up manner
  rightBoundary(root->right);
}

/*
Note: in case of binary search trees (BST), Inorder traversal gives nodes in non-decreasing order.
To get nodes of BST in non-increasing order, a variation of Inorder traversal
where Inorder itraversal s reversed, can be used.
 */
vector<int> inorder_recur(const BinTreeNode* root) {
  vector<int> ret;

  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);
    ret.push_back(curr_root->value);
    solve(curr_root->right);
  };

  solve(root);
  return ret;
}

// it's all about when to pop from stack...
vector<int> inorder_iter(BinTreeNode* root) {
  if (!root)
    return {};

  vector<int> ret;
  stack<const BinTreeNode*> stk;
  const BinTreeNode* curr = root;

  while (!stk.empty() || curr) {
    if (curr) {
      stk.emplace(curr);
      curr = curr->left;
    } else {
      curr = stk.top();
      stk.pop();
      ret.push_back(curr->value);
      curr = curr->right;
    }
  }

  return ret;
}

/*
Preorder traversal is used to create a copy of the tree.
Preorder traversal is also used to get prefix expression on of an expression tree.
Please see http://en.wikipedia.org/wiki/Polish_notation
to know why prefix expressions are useful.
 */
vector<int> preorder_recur(const BinTreeNode* root) {
  vector<int> ret;

  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    ret.push_back(curr_root->value);
    solve(curr_root->left);
    solve(curr_root->right);
  };

  solve(root);
  return ret;
}

vector<int> preorder_iter(const BinTreeNode* root) {
  if (!root)
    return {};

  vector<int> ret;
  stack<const BinTreeNode*> stk;
  stk.push(root);

  while (!stk.empty()) {
    const BinTreeNode* curr = stk.top();
    ret.push_back(curr->value);
    stk.pop();

    if (curr->right)
      stk.push(curr->right);
    if (curr->left)
      stk.push(curr->left);
  }

  return ret;
}

/*
Postorder traversal is used to delete the tree. Please see the question for deletion of tree for details. Postorder traversal is also useful to get the postfix expression of an expression tree. Please see http://en.wikipedia.org/wiki/Reverse_Polish_notation to for the usage of postfix expression.
 */
vector<int> postorder_recur(const BinTreeNode* root) {
  vector<int> ret;

  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);
    solve(curr_root->right);
    ret.push_back(curr_root->value);
  };

  solve(root);
  return ret;
}

vector<int> postorder_iter(const BinTreeNode* root) {
  if (!root)
    return {};

  vector<int> ret;
  stack<const BinTreeNode*> stk;
  stk.push(root);
  const BinTreeNode* prev = nullptr;

  while (!stk.empty()) {
    const BinTreeNode* curr = stk.top();
    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left)
        stk.push(curr->left);
      else if (curr->right)
        stk.push(curr->right);
    } else if (curr->left == prev) {
      if (curr->right)
        stk.push(curr->right);
    } else {
      ret.push_back(curr->value);
      stk.pop();
    }

    prev = curr;
  }

  return ret;
}

vector<int> postorder_iter_2stacks(const BinTreeNode* root) {
  if (!root)
    return {};

  stack<const BinTreeNode*> stk;
  stk.push(root);
  stack<const BinTreeNode*> output;

  while (!stk.empty()) {
    const BinTreeNode* curr = stk.top();
    output.push(curr);
    stk.pop();
    if (curr->left)
      stk.push(curr->left);
    if (curr->right)
      stk.push(curr->right);
  }

  vector<int> ret;
  while (!output.empty()) {
    ret.push_back(output.top()->value);
    output.pop();
  }

  return ret;
}

/*
Level order traversal
 */
vector<vector<int>> levelorder(const BinTreeNode* root) { // a.k.a., BFS
  if (!root)
    return {};

  vector<vector<int>> ret;
  deque<const BinTreeNode*> q = {root};

  while (!q.empty()) {
    const uint sz = q.size();
    ret.push_back(vector<int>());
    for (uint i = 0; i < sz; ++i) {
      const BinTreeNode* node = q.front();
      q.pop_front();
      ret.back().push_back(node->value);
      if (node->left)
        q.push_back(node->left);
      if (node->right)
        q.push_back(node->right);
    }
  }

  return ret;
}
#if 0
/*
 */
void reverseLevelOrder(const BinTreeNode* root) {
  uint h = height(root);

  function<void(const BinTreeNode*,const uint)> solve =
    [&](BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;
    else if (curr_lvl == 1) {
      cout << curr_root->value << " ";
      return;
    }// else if (curr_lvl > 1) {

    solve(curr_root->left, curr_lvl-1);
    solve(curr_root->right, curr_lvl-1);
    // }
  };

  for (uint i = h; i >= 1; --i) //THE ONLY LINE DIFFERENT FROM NORMAL LEVEL ORDER
    solve(root, i);
}
#endif

/*
Spiral level order traversal
 */
vector<vector<int>> spiralLevelOrder(const BinTreeNode* root) {
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
