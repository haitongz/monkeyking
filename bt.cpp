#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <functional>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <cstring>

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
      : value(v), left(nullptr), right(nullptr) {
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
    uint cnt = q.size();
    if (!cnt)
      return ret;

    ++ret;

    // Dequeue all nodes of current level and Enqueue all nodes of next level
    while (cnt > 0) {
      const BinTreeNode* nd = q.front();
      q.pop_front();
      if (nd->left)
        q.push_back(nd->left);
      if (nd->right)
        q.push_back(nd->right);

      --cnt;
    }
  }
}

void prettyPrint(const BinTreeNode* root, uint spaces = 2) {
  deque<const BinTreeNode*> q{root};
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

bool bstInsert_recur(BinTreeNode** root, const int key) {
  if (!root)
    return false;

  function<bool(BinTreeNode**)> solve =
    [&](BinTreeNode** curr_root) {
    BinTreeNode*& ptr = *curr_root;
    if (!ptr) {
      ptr = new BinTreeNode(key);
      return true;
    } else if (ptr->value == key) {
      return false;
    } else if (ptr->value > key) {
      return solve(&(ptr->left));
    } else {
      return solve(&(ptr->right));
    }
  };

  return solve(root);
}

void delTree_iter(BinTreeNode** root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const BinTreeNode*> q{*root};

  while (!q.empty()) {
    const uint sz = q.size();
    for (uint i = 0; i < sz; ++i) {
      const BinTreeNode* nd = q.front();
      q.pop_front();
      if (nd->left)
        q.push_back(nd->left);
      if (nd->right)
        q.push_back(nd->right);

      delete nd;
      nd = nullptr;
    }
  }

  *root = nullptr;
}

void delTree_recur(BinTreeNode** root) {
  function<void(BinTreeNode**)> solve = [&](BinTreeNode** ndp) { // DFS, postorder
    if (!ndp) {
      return; //throw exception();
    } else if (*ndp) {
      BinTreeNode* nd = *ndp;
      solve(&(nd->left));
      solve(&(nd->right));
      delete nd;
      nd = nullptr;
    }
  };

  solve(root);
}

bool isLeaf(const BinTreeNode* nd) {
  return (nd && !nd->left && !nd->right);
}

/*
Find number of nodes in a binary tree
 */
uint count_recur(const BinTreeNode* root) {
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint { // postorder
    if (!curr_root)
      return 0;

    uint lcnt = solve(curr_root->left);
    uint rcnt = solve(curr_root->right);
    return lcnt+rcnt+1;
  };

  return solve(root);
}

/*
Two trees are identical when they have same data and arrangement of data is also same.

To identify if two trees are identical, we need to traverse both trees simultaneously,
and while traversing we need to compare data and children of the trees.
 */
bool areIdentical(const BinTreeNode* r1, const BinTreeNode* r2) {
  function<bool(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) {
    if (!curr_root1 && !curr_root2)
      return true;
    else if (!curr_root1 ||
             !curr_root2 ||
             curr_root1->value != curr_root2->value)
      return false;

    return solve(curr_root1->left, curr_root2->left) &&
           solve(curr_root1->right, curr_root2->right);
  };

  return solve(r1, r2);
}

/*
Given a binary tree, find its minimum/maximum depth.
The minimum/maximum depth is the number of nodes along
the shortest/longest path from the root node down to
the nearest/farest leaf node.
 */
uint minDepth_recur(const BinTreeNode* root) {
  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return 0;

    int lheight = curr_root->left ? solve(curr_root->left) : MAX_LMT;
    int rheight = curr_root->right ? solve(curr_root->right) : MAX_LMT;
    return min(lheight, rheight)+1;
  };

  return solve(root);
}

uint maxDepth_recur(const BinTreeNode* root) {
  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return 0;

    int lheight = curr_root->left ? solve(curr_root->left) : MIN_LMT;
    int rheight = curr_root->right ? solve(curr_root->right) : MIN_LMT;
    return max(lheight, rheight)+1;
  };

  return solve(root);
}

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

/*
Count leaf nodes
 */
uint leafCount(const BinTreeNode* root) {
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;
    if (!curr_root->left && !curr_root->right)
      return 1;

    return solve(curr_root->left)+solve(curr_root->right);
  };

  return solve(root);
}

/*
Given a binary tree (not a binary search tree) and two values say n1 and n2,
write a program to find the least common ancestor.
 */
const BinTreeNode* LCA(const BinTreeNode* root, const int n1, const int n2) {
  int target = MIN_LMT;
  vector<const BinTreeNode*> to_ext;

  function<bool(const BinTreeNode*)> solve = // backtracking
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return false;

    to_ext.push_back(curr_root);

    if (curr_root->value == target)
      return true;
    if (solve(curr_root->left) || solve(curr_root->right))
      return true;

    to_ext.pop_back();

    return false;
  };

  vector<const BinTreeNode*> path1, path2;
  target = n1;
  bool found = solve(root);
  if (!found)
    return nullptr;
  else
    path1 = to_ext;

  to_ext.clear();
  target = n2;
  found = solve(root);
  if (!found)
    return nullptr;
  else
    path2 = to_ext;

  uint i = 0;
  for (; i < path1.size() && path1[i] == path2[i]; ++i);

  return i > 0 ? path1[i-1] : nullptr;
}

/*
Given a binary tree and a sum, find all root-to-leaf paths
where each path's sum equals the given sum.

Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
 [5,4,11,2],
 [5,8,4,5]
]
 */
vector<vector<int>>
r2lPathsWithSum_recur(const BinTreeNode* root, const int sum) {
  vector<vector<int>> ret;
  vector<int> to_ext;

  // use backtracking here because we need to collect ALL paths, not just to
  // find out whether there is an existing path
  function<void(const BinTreeNode*,const int)> solve =
    [&](const BinTreeNode* curr_root, const int remain) {
    if (!curr_root)
      return;

    if (isLeaf(curr_root)) {
      if (curr_root->value == remain) {
        to_ext.push_back(curr_root->value);
        ret.push_back(to_ext); // to_ext doesn't pop back yet
      }
      return;
    }

    to_ext.push_back(curr_root->value);
    solve(curr_root->left, remain-curr_root->value);
    solve(curr_root->right, remain-curr_root->value);
    to_ext.pop_back();
  };

  solve(root, sum-0);
  return ret;
}

/*
Find the distance between two keys in a binary tree, no parent pointers are given.
 */
int distance(const BinTreeNode* root,
             const BinTreeNode* first,
             const BinTreeNode* second) {
  int d1 = -1, d2 = -1, ret = -1;

  // find possible lowest common ancestor in top-down style: start from root with
  // distance 0, update distances on the way till there's an LCA found
  function<const BinTreeNode*(const BinTreeNode*,const int)> lca =
    [&](const BinTreeNode* curr_root, const int curr_d) -> const BinTreeNode* {
    if (!curr_root)
      return nullptr;

    if (curr_root == first) {
      d1 = curr_d;
      return curr_root;
    } else if (curr_root == second) {
      d2 = curr_d;
      return curr_root;
    }

    auto left = lca(curr_root->left, curr_d+1);
    auto right = lca(curr_root->right, curr_d+1);
    if (left && right) {
      ret = d1+d2-2*curr_d;
      return curr_root;
    }

    return left ? left : right;
  };

  function<uint(const BinTreeNode*,const BinTreeNode*,const uint)> height =
    [&](const BinTreeNode* curr_root, const BinTreeNode* nd, const uint curr_h) -> uint {
    if (!curr_root)
      return 0;

    if (curr_root == nd)
      return curr_h;

    return max(height(curr_root->left, nd, curr_h+1),
               height(curr_root->right, nd, curr_h+1));
  };

  auto lowest = lca(root, 0);
  if (d1 != -1 && d2 != -1)
    return ret;
  else if (d1 != -1)
    return height(lowest, second, 0);
  else if (d2 != -1)
    return height(lowest, first, 0);
  else
    return -1;
}

/*
Find maximum path sum between 2 leaves
 */
int maxL2LPathSum(const BinTreeNode* root) {
  if (!root)
    throw exception();

  int ret = MIN_LMT;

  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) { // postorder
    if (!curr_root)
      return 0;

    // Find maximum sum in left and right subtree.
    // Also find maximum root to leaf sums in
    // left and right subtrees and store them
    int lsum = solve(curr_root->left);
    int rsum = solve(curr_root->right);

    // Find the maximum path sum passing through current root.
    // Note that every path will pass through some node and
    // recursive function is called for every node
    int curr_sum = lsum + rsum + curr_root->value;
    ret = max(ret, curr_sum);
    return curr_sum;
  };

  solve(root);
  return ret;
}

/*
Find diameter of a binary tree
 */
uint diameter(const BinTreeNode* root) { // O(n)
  function<uint(const BinTreeNode*,uint&)> solve =
    [&](const BinTreeNode* curr_root, uint& curr_height) -> uint {
    /* Get the heights of left and right subtrees in
       lheight and rheight store the returned values in ldiameter and rdiameter */
    if (!curr_root) {
      curr_height = 0;
      return 0;
    }

    uint lheight = 0, rheight = 0, ldiameter = 0, rdiameter = 0;
    ldiameter = solve(curr_root->left, lheight);
    rdiameter = solve(curr_root->right, rheight);

    /* Height of current node is max of heights of left and right subtrees plus 1 */
    curr_height = max(lheight, rheight)+1;
    return max(lheight+rheight+1, max(ldiameter, rdiameter));
  };

  uint height = 0;
  return solve(root, height);
}

/*
Given a binary tree where all the right nodes are either leaf nodes
with a sibling (a left node that shares the same parent node) or empty,
flip it upside down and turn it into a tree where the original right nodes
turned into left leaf nodes. Return the new root.

Given a binary tree [1,2,3,4,5],
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
    4
   / \
  5   2
 / \
3   1
 */
BinTreeNode* invert_recur(BinTreeNode* root) {
  function<BinTreeNode*(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) {
    if (!curr_root || !curr_root->left)
      return curr_root;

    auto ret = solve(curr_root->left);
    curr_root->left->left = curr_root->right;
    curr_root->left->right = curr_root;
    curr_root->left = nullptr;
    curr_root->right = nullptr;

    return ret;
  };

  return solve(root);
}

BinTreeNode* invert_iter(BinTreeNode* root) {
  BinTreeNode* p = root, *parent = nullptr, *parent_right = nullptr;
  while (p) {
    auto left = p->left;
    p->left = parent_right;
    parent_right = p->right;
    p->right = parent;
    parent = p;
    p = left;
  }

  return parent;
}

/*
Check a binary tree is height balanced or not
 */
bool isHeightBalanced(const BinTreeNode* root) {
  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return 0;

    int left = solve(curr_root->left);
    if (left == -1)
      return -1;

    int right = solve(curr_root->right);
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

bool isSymmetric(const BinTreeNode* root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return true; // ?
  }

  deque<const BinTreeNode*> q{root};

  while (!q.empty()) {
    const uint sz = q.size();
    stack<int> values;

    for (uint i = 0; i < sz; ++i) {
      const BinTreeNode* nd = q.front();
      q.pop_front();

      if (values.empty()) {
        values.push(nd->value);
      } else {
        if (values.top() == nd->value) {
          values.pop();
        } else {
          values.push(nd->value);
        }
      }

      if (nd->left) {
        q.push_back(nd->left);
      }

      if (nd->right) {
        q.push_back(nd->right);
      }
    }

    if (!values.empty())
      return false;
  }

  return true;
}

bool isSymmetric2(const BinTreeNode* root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return true; // ?
  }

  stack<const BinTreeNode*> s1, s2;
  s1.push(root->left);
  s2.push(root->right);

  while (!s1.empty() && !s2.empty()) {
    const BinTreeNode* n1 = s1.top();
    s1.pop();
    const BinTreeNode* n2 = s2.top();
    s2.pop();

    if (!n1 && !n2)
      continue;

    if (!n1 || !n2 || n1->value != n2->value)
      return false;

    s1.push(n1->left);
    s1.push(n1->right);
    s2.push(n2->right);
    s2.push(n2->left);
  }

  return true;
}

/*
Check whether 2 binary trees are equal
 */
bool areBTsEqual(const BinTreeNode* r1, const BinTreeNode* r2) {
  function<bool(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) -> bool {
    if (!curr_root1 && !curr_root2)
      return true; // ?
    else if (!curr_root1 || !curr_root2 || curr_root1->value != curr_root2->value)
      return false;

    return solve(curr_root1->left, curr_root2->left) &&
           solve(curr_root1->right, curr_root2->right);
  };

  return solve(r1, r2);
}

/*
Given a Binary Tree, find the deepest leaf node that is left child of its parent.
For example:

     _______1______
    /              \
 ___2__             3
/      \
4       5
         \
          6
should return 6.
 */
int deepestLeft(const BinTreeNode* root) {
  uint max_lvl = 0, ret = 0;

  function<void(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;

    if (curr_lvl > max_lvl) {
      max_lvl = curr_lvl;
      ret = curr_root->value;
    }

    solve(curr_root->left, curr_lvl+1);
    solve(curr_root->right, curr_lvl+1);
  };

  solve(root, 1);
  return ret;
}

/*
Given a binary tree, write a function that returns true
if the tree is a Sum Tree: for every node, value must be equal to sum
of values in left and right children.

Tricky: use following rules to get the sum directly:
1) If the node is a leaf node then sum of subtree rooted with this node
is equal to value of this node.
2) If the node is not a leaf node then sum of subtree rooted with this node
is twice the value of this node
(Assuming that the tree rooted with this node is SumTree).
 */
bool isSumTree(const BinTreeNode* root) { // O(n)
  function<bool(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    /* If node is NULL or it's a leaf node then return true */
    if (!curr_root || isLeaf(curr_root))
      return true;

    int lsum, rsum; // left subtree and right subtree sums

    if (solve(curr_root->left) && solve(curr_root->right)) {
      // Get the sum of nodes in left subtree
      if (!curr_root->left)
        lsum = 0;
      else if (isLeaf(curr_root->left))
        lsum = curr_root->left->value;
      else
        lsum = 2*(curr_root->left->value);

      // Get the sum of nodes in right subtree
      if (!curr_root->right)
        rsum = 0;
      else if (isLeaf(curr_root->right))
        rsum = curr_root->right->value;
      else
        rsum = 2*(curr_root->right->value);

      /* If root's data is equal to sum of nodes in left and right subtrees then return 1 else return 0*/
      return (curr_root->value == lsum+rsum);
    }
  };

  return solve(root);
}

/*
Given an arbitrary binary tree, convert it to a binary tree that holds Children Sum Property.
You can only increment data values in any node (You cannot change structure of tree and cannot decrement value of any node).
 */
void convert2SumTree(BinTreeNode* root) {
  /* This function is used to increment subtree by diff */
  function<void(BinTreeNode*,const int)> increment =
    [&](BinTreeNode* curr_root, const int diff) {
    /* IF left child is not NULL then increment it */
    if (curr_root->left) {
      curr_root->left->value = curr_root->left->value+diff;
      // Recursively call to fix the descendants of node->left
      increment(curr_root->left, diff);
    } else if (curr_root->right) { // Else increment right child
      curr_root->right->value = curr_root->right->value+diff;
      // Recursively call to fix the descendants of node->right
      increment(curr_root->right, diff);
    }
  };

  function<void(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) {
    if (!curr_root || (!curr_root->left && !curr_root->right))
      return;
    else {
      int left = 0, right = 0, diff;
      // convert left and right subtrees
      solve(curr_root->left);
      solve(curr_root->right);

      if (curr_root->left)
        left = curr_root->left->value;
      if (curr_root->right)
        right = curr_root->right->value;

      /* get the diff of node's data and children sum */
      diff = left+right-curr_root->value;
      /* If node's children sum is greater than the node's data */
      if (diff > 0)
        curr_root->value = curr_root->value+diff;

      /* THIS IS TRICKY --> If node's data is greater than children sum,
        then increment subtree by diff */
      if (diff < 0)
        increment(curr_root, -diff);  // -diff is used to make diff positive
    }
  };

  return solve(root);
}

/*
Given a binary tree, write a function to get the maximum width of the given tree.
Width of a tree is maximum of widths of all levels.
 */
// A function that fills count array with count of nodes at every level of given binary tree
uint maxWidth(const BinTreeNode* root) { // preorder traversal, O(n)
  const uint h = maxHeight_recur(root);
  // Create an array that will store count of nodes at each level
  vector<uint> count(h, 0);

  function<void(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) {
    ++count[curr_lvl];
    solve(curr_root->left, curr_lvl+1);
    solve(curr_root->right, curr_lvl+1);
  };

  // Fill the count array using preorder traversal
  solve(root, 0);

  uint ret = 0;
  for (auto i : count)
    ret = max(i, ret);

  return ret;
}

/*
Write a program that converts a given tree to its Double Tree.
To create Double Tree of the given tree, create a new duplicate for each node,
and insert the duplicate as the left child of the original node.
 */

void doubleTree(BinTreeNode* root) {
  function<void(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) { // postorder, O(n)
    if (!curr_root)
      return;

    solve(curr_root->left);
    solve(curr_root->right);

    /* duplicate this node to its left */
    BinTreeNode* cp = curr_root->left;
    curr_root->left = new BinTreeNode(curr_root->value);
    curr_root->left->left = cp;
  };

  return solve(root);
}

/*
Question: Given a binary tree, find out if the tree can be folded or not.

A tree can be folded if left and right subtrees of the tree are structure
wise mirror image of each other. An empty tree is considered as foldable.
Consider the below trees:
(a) and (b) can be folded.
(c) and (d) cannot be folded.

(a)
       10
     /    \
    7      15
     \    /
      9  11

(b)
        10
       /  \
      7    15
     /      \
    9       11

(c)
        10
       /  \
      7   15
     /    /
    5   11

(d)
         10
       /   \
      7     15
    /  \    /
   9   10  12
 */
bool isFoldable(const BinTreeNode* root) {
  if (!root)
    return true;

  function<bool(const BinTreeNode*,const BinTreeNode*)> areSame =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) {
    if (!curr_root1 && !curr_root2) {
      return true;
    }

    if (curr_root1 && curr_root2 &&
        areSame(curr_root1->left, curr_root2->left) &&
        areSame(curr_root1->right, curr_root2->right)) {
      return true;
    }

    return false;
  };

  /* Change a tree so that the roles of the left and right pointers are swapped at every node. See http://geeksforgeeks.org/?p=662 for details */
  function<void(BinTreeNode*)> mirror =
    [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;
    else {
      /* do the subtrees */
      mirror(curr_root->left);
      mirror(curr_root->right);

      /* swap the pointers in this node */
      BinTreeNode* tmp = curr_root->left;
      curr_root->left = curr_root->right;
      curr_root->right = tmp;
    }
  };

  /* convert left subtree to its mirror */
  mirror(root->left);
  /* Compare the structures of the right subtree and mirrored left subtree */
  bool ret = areSame(root->left, root->right);
  /* Get the originial tree back */
  mirror(root->left);

  return ret;
}

/*
Given a root of a tree, and an integer k.
Collect all the nodes which are at k distance from root.
 */
vector<const BinTreeNode*> allKDistant(const BinTreeNode* root, const uint k) {
  if (!root) {
    return {};
  } else if (!k) {
    return vector<const BinTreeNode*>(1, root);
  }

  vector<const BinTreeNode*> ret;

  function<void(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint lvl) {
    if (!curr_root)
      return;

    if (!lvl) {
      ret.push_back(curr_root);
      return;
    } else {
      solve(curr_root->left, lvl-1);
      solve(curr_root->right, lvl-1);
    }
  };

  solve(root, k);
}

/*
Given a binary tree, a target node in the binary tree, and an integer value k,
print all the nodes that are at distance k from the given target node.
No parent pointers are available.
 */
// Prints all nodes at distance k from a given target node. The k distant nodes
// may be upward or downward.
// This function returns distance of root from target node.
// It returns -1 if target node is not present in tree rooted with root.
void kDistanceBinTreeNodes(const BinTreeNode* root,
                           const BinTreeNode* target,
                           const uint k) {
  if (!root || !target)
    return;

  vector<const BinTreeNode*> ret;

  function<void(const BinTreeNode*,const int)> downward =
    [&](const BinTreeNode* curr_root, const int d) {
    if (!curr_root || d < 0)
      return;

    // If we reach a k distant node, print it
    if (!d) {
      ret.push_back(curr_root);
      return;
    }

    // Recur for left and right subtrees
    downward(curr_root->left, d-1);
    downward(curr_root->right, d-1);
  };

  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return -1;

    // If target is same as current root,
    // use downward function to get all nodes at distance k
    // in subtree rooted with target or root
    if (curr_root == target) {
      downward(root, k);
      return 0;
    }

    // Recur for left subtree
    int dist = solve(curr_root->left);
    // Check if target node was found in left subtree
    if (dist != -1) {
      // If root is at distance k from target, collect root.
      // Note that dist is Distance of root's left child from target
      if (dist+1 == k)
        ret.push_back(curr_root);
      else // Else go to right subtree and print all k-dist-2 distant nodes.
           // Note that the right child is 2 edges away from left child
        downward(curr_root->right, k-dist-2);

      // Add 1 to the distance and return value for parent calls
      return 1+dist;
    }

    // Note that we reach here only when node was not found in left subtree
    dist = solve(curr_root->right);
    if (dist != -1) {
      if (dist+1 == k)
        ret.push_back(curr_root);
      else
        downward(curr_root->left, k-dist-2);
      return 1+dist;
    }

    // If target was neither present in left nor in right subtree
    return -1;
  };

  solve(root);
}

/*
Given a Binary Tree and a positive integer k, print all nodes that are distance k from a leaf node.
 */
#define MAX_HEIGHT 500

void kDistantFromLeaf(const BinTreeNode* root, const uint k) {
  int path[MAX_HEIGHT];
  bool visited[MAX_HEIGHT] = {false};

  function<void(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_pathlen) {
    if (!curr_root)
      return;

    /* append this BinTreeNode to the path array */
    path[curr_pathlen] = curr_root->value;
    visited[curr_pathlen] = false;

    /* it's a leaf, so print the ancestor at distance k only if the ancestor is not already printed */
    if (!curr_root->left && !curr_root->right &&
        curr_pathlen-k >= 0 &&
        visited[curr_pathlen-k] == false) {
      cout << path[curr_pathlen-k] << " ";
      visited[curr_pathlen-k] = true;
      return;
    }

    /* If not leaf node, recur for left and right subtrees */
    solve(curr_root->left, curr_pathlen+1);
    solve(curr_root->right, curr_pathlen+1);
  };

  return solve(root, 0);
}

/*
Given a Binary Tree and a number k,
remove all nodes that lie only on root to leaf path(s) of length smaller than k.
If a node X lies on multiple root-to-leaf paths and if any of the paths has path length >= k,
then X is not deleted from Binary Tree. In other words a node is deleted if
all paths going through it have lengths smaller than k.
 */
BinTreeNode* removeShortPathNodes(BinTreeNode* root, const uint k) {
  function<BinTreeNode*(BinTreeNode*,const uint)> solve =
    [&](BinTreeNode* curr_root, const uint curr_lvl) -> BinTreeNode* {
    if (!curr_root)
      return nullptr;

    // Traverse the tree in postorder fashion so that if a leaf node path length
    // is shorter than k, then that node and all of its descendants till the node
    // which are not on some other path are removed.
    curr_root->left = solve(curr_root->left, curr_lvl+1);
    curr_root->right = solve(curr_root->right, curr_lvl+1);

    // If root is a leaf node and it's level is less than k then remove this node.
    // This goes up and check for the ancestor nodes also for the same condition
    // till it finds a node which is a part of other path(s) too.
    if (!curr_root->left && !curr_root->right && curr_lvl < k) {
      delete curr_root;
      return nullptr;
    }

    return curr_root;
  };

  return solve(root, 1);
}

/* If target is present in tree then prints
 * the ancestors and returns true, otherwise returns false. */
bool ancestors_recur(const BinTreeNode* root, const int target) {
  vector<const BinTreeNode*> ancestors;

  function<bool(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return false;
    if (curr_root->value == target)
      return true;

    /* If target is present in either left or right subtree of this node, then print this node */
    if (solve(curr_root->left) || solve(curr_root->right)) {
      ancestors.push_back(curr_root);
      return true;
    }
    return false;
  };

  bool ret = solve(root);

  for (const auto& i : ancestors)
    cout << i << " ";
  cout << endl;

  return ret;
}

void ancestors_iter(const BinTreeNode* root, const int target) {
  if (!root)
    return;

  // Create a stack to hold ancestors
  stack<const BinTreeNode*> ancestors;

  while (1) { // Traverse the complete tree in postorder way till we find the key
    // Traverse the left side. While traversing, push the nodes into the stack so that their right subtrees can be traversed later
    while (root && root->value != target) {
      ancestors.push(root); // push current node
      root = root->left; // move to next node
    }

    // If the node whose ancestors are to be printed is found, then break the while loop.
    if (root && root->value == target)
      break;

    // Check if right sub-tree exists for the node at top. If not then pop that node because we don't need this node any more.
    if (!ancestors.top()->right) {
      root = ancestors.top();
      ancestors.pop();

      // If the popped node is right child of top, then remove the top as well. Left child of the top must have processed before. Consider the following tree for example and key = 3. If we remove the following loop, the program will go in an infinite loop after reaching 5.
      //          1
      //        /   \
      //       2     3
      //         \
      //           4
      //             \
      //              5
      while (!ancestors.empty() && ancestors.top()->right == root) {
        root = ancestors.top();
        ancestors.pop();
      }
    }
    // if stack is not empty then simply set the root as right child of top and start traversing right sub-tree.
    root = ancestors.empty() ? nullptr : ancestors.top()->right;
  }
  // If stack is not empty, print contents of stack. Assumption is that the key is there in tree
  while (!ancestors.empty()) {
    cout << ancestors.top()->value << " ";
    ancestors.pop();
  }
}

/*
Given a Binary Tree, find vertical sum of the nodes that are in same vertical line. Print all sums through different vertical lines.
 */
void verticalSums(const BinTreeNode* root) { // inorder, O(n)
  map<int,int> hM;

  function<void(const BinTreeNode*,const int)> solve =
    [&](const BinTreeNode* curr_root, const int hD) {
    if (!curr_root)
      return;

    // Store the values in hM for left subtree
    solve(curr_root->left, hD-1);
    // Update vertical sum for hD of this node
    int prevSum = !hM.count(hD) ? 0 : hM[hD];
    hM[hD] = prevSum+curr_root->value;
    // Store the values in hM for right subtree
    solve(curr_root->right, hD+1);
  };

  solve(root, 0);

  for (const auto& i : hM)
    cout << i.second << endl;
}

/*
Given a Binary Tree, write a function to check
whether the given Binary Tree is Complete Binary Tree or not.

A complete binary tree is a binary tree in which every level,
except possibly the last, is completely filled, and all nodes are as far left as possible.
See following examples.
 */
bool isComplete_iter(const BinTreeNode* root) {
  if (!root)
    return true;

  deque<const BinTreeNode*> q = {root};

  // Create a flag variable which will be set true
  // when a non full node is seen
  bool flag = false;

  while (!q.empty()) { // level-order traversal using queue.
    const BinTreeNode* tmp = q.front();
    q.pop_front();
    if (tmp->left) {
       // If we have seen a non full node, and we see a node
       // with non-empty left child, then the given tree is not
       // a complete Binary Tree
       if (flag)
         return false;

       q.push_back(tmp->left);  // Enqueue Left Child
    } else // If this a non-full node, set the flag as true
       flag = true;

    if (tmp->right) {
       // If we have seen a non full node, and we see a node
       // with non-empty left child, then the given tree is not
       // a complete Binary Tree
       if (flag)
         return false;

       q.push_back(tmp->right);
    } else // If this a non-full node, set the flag as true
       flag = true;
  }

  // If we reach here, then the tree is complete Bianry Tree
  return true;
}

bool isComplete_recur(const BinTreeNode* root) {
  const uint node_count = count_recur(root);
  function<bool(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint idx) {
    if (!curr_root)
      return true;

    // If index assigned to current node is more than number of nodes in tree, then tree is not complete
    if (idx >= node_count)
      return false;

    // Recur for left and right subtrees
    return (solve(curr_root->left, 2*idx+1) && solve(curr_root->right, 2*idx+2));
  };

  return solve(root, 0);
}

/*
A full binary tree is defined as a binary tree in which all nodes have either zero or two child nodes.
Conversely, there is no node in a full binary tree, which has one child node.
 */
bool isFull_recur(const BinTreeNode* root) {
  function<bool(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return true;

    // If leaf node
    if (!curr_root->left && !curr_root->right)
      return true;

    // If both left and right are not NULL, and left & right subtrees are full
    if (curr_root->left && curr_root->right)
      return (solve(curr_root->left) && solve(curr_root->right));

    // We reach here when none of the above if conditions work
    return false;
  };

  return solve(root);
}

/*
Given a binary tree, print boundary nodes of the binary tree Anti-Clockwise
starting from the root.
For example, boundary traversal of the following tree is "20 8 4 10 14 25 22"
 */
void boundaryTraversal(const BinTreeNode* root) {
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

/*
Therefore, following combination can uniquely identify a tree.

Inorder and Preorder.
Inorder and Postorder.
Inorder and Level-order.

And following do not.
Postorder and Preorder.
Preorder and Level-order.
Postorder and Level-order.
 */

/*
Given Inorder Traversal of a Special Binary Tree in which key of every node
is greater than keys in left and right children,
construct the Binary Tree and return root.
 */
BinTreeNode* spec_in(const int inorder[], const uint n) {
  if (!n)
    return nullptr;

  function<uint(const uint,const uint)> peakIndex =
    [&](const uint start, const uint end) {
    uint ret = start;
    int max_val = MIN_LMT;

    for (uint i = start; i < end+1; ++i) {
      if (max_val < inorder[i]) {
        ret = i;
        max_val = inorder[i];
      }
    }

    return ret;
  };

  function<BinTreeNode*(const uint,const uint)> solve =
    [&](const uint start, const uint end) -> BinTreeNode* {
    if (start > end)
      return nullptr;

    /* Find index of the maximum element from Binary Tree */
    uint idx = peakIndex(start, end);

    /* Pick the maximum value and make it root */
    BinTreeNode* root = new BinTreeNode(inorder[idx]);

    /* If this is the only element in inorder[start..end], then return it */
    if (start == end)
      return root;

    /* Using index in Inorder traversal, construct left and right subtress */
    root->left  = solve(start, idx-1);
    root->right = solve(idx+1, end);

    return root;
  };

  return solve(0, n-1);
}

/*
Given an array 'pre[]' that represents Preorder traversal of a spacial binary tree
where every node has either 0 or 2 children. One more array 'preLN[]' is given which
has only two possible values 'L' and 'N'. The value 'L' in 'preLN[]' indicates that
the corresponding node in Binary Tree is a leaf node and value 'N' indicates that
the corresponding node is non-leaf node.
Write a function to construct the tree from the given two arrays.
 */
BinTreeNode* spec_pre(const int pre[], char preLN[], const uint n) {
  if (!n)
    return nullptr;

  uint index = 0;

  function<BinTreeNode*(uint*)> solve =
    [&](uint* idx_ptr) -> BinTreeNode* {
    const uint idx = *idx_ptr;
    if (idx == n)
      return nullptr;

    // Allocate memory for this node and increment index for
    // subsequent recursive calls
    BinTreeNode* ret = new BinTreeNode(pre[idx]);
    ++(*idx_ptr);

    // If this is an internal node, construct left and right subtrees and link the subtrees
    if (preLN[idx] == 'N') {
      ret->left  = solve(idx_ptr);
      ret->right = solve(idx_ptr);
    }

    return ret;
  };

  return solve(&index);
}

/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
 */
BinTreeNode* pre_in_iter(const vector<int>& preorder, const vector<int>& inorder) {
  if (!preorder.size())
    return nullptr;

  uint ppre = 0, pin = 0;
  BinTreeNode* root = new BinTreeNode(preorder[ppre++]);
  BinTreeNode* p = nullptr;
  stack<BinTreeNode*> roots;

  roots.push(root);

  while (true) {
    if (inorder[pin] == roots.top()->value) {
      p = roots.top();
      roots.pop();
      if (++pin == inorder.size())
        break;
      if (roots.size() && inorder[pin] == roots.top()->value)
        continue;
      p->right = new BinTreeNode(preorder[ppre++]);
      roots.push(p->right);
    } else {
      p = new BinTreeNode(preorder[ppre++]);
      roots.top()->left = p;
      roots.push(p);
    }
  }

  return root;
}

BinTreeNode* prev_in_recur(const vector<int>& preorder, const vector<int>& inorder) {
  const uint m = preorder.size(), n = inorder.size();
  function<BinTreeNode*(const uint,const uint,const uint,const uint)> solve =
    [&](const uint pre_low, const uint pre_hi, const uint in_low, const uint in_hi) -> BinTreeNode* {
    if (pre_low > pre_hi)
      return nullptr;

    BinTreeNode* root = new BinTreeNode(preorder[pre_low]);
    uint offset = 0;
    for (; inorder[in_low+offset] != preorder[pre_low]; ++offset);

    root->left  = solve(pre_low+1, pre_low+offset, in_low, in_low+offset-1);
    root->right = solve(pre_low+offset+1, pre_hi, in_low+offset+1, in_hi);
    return root;
  };

  return solve(0, m-1, 0, n-1);
}

/*
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
 */
BinTreeNode* in_post_recur(const vector<int>& inorder, const vector<int>& postorder) {
  function<BinTreeNode*(const uint,const uint,const uint,const uint)> solve =
    [&](const uint in_low, const uint in_hi, const uint po_low, const uint po_hi) -> BinTreeNode* {
    if (in_low > in_hi)
      return nullptr;

    uint offset = 0;
    for (uint i = in_low; inorder[i+offset] != postorder[po_hi]; ++offset);

    BinTreeNode* lt = solve(in_low, in_low+offset-1, po_low, po_low+offset-1);
    BinTreeNode* root = new BinTreeNode(postorder[po_hi]);
    root->left = lt;
    root->right = solve(in_low+offset+1, in_hi, po_low+offset, po_hi-1);
    return root;
  };

  return solve(0, inorder.size()-1, 0, postorder.size()-1);
}

BinTreeNode* pre_post_recur(const int pre[], const int post[], const uint n) {
  if (!n)
    return nullptr;

  int pre_idx = 0;

  function<BinTreeNode*(const uint,const uint)> solve =
    [&](const uint low, const uint hi) -> BinTreeNode* {
    // Base case
    if (pre_idx >= n || low > hi)
        return nullptr;

    // The first node in preorder traversal is root. So take the node at
    // pre_idx from preorder and make it root, and increment pre_idx
    BinTreeNode* root = new BinTreeNode(pre[pre_idx]);
    ++pre_idx;

    // If the current subarry has only one element, no need to recur
    if (low == hi)
      return root;

    // Search the next element of pre[] in post[]
    int i;
    for (i = low; i <= hi; ++i)
      if (pre[pre_idx] == post[i])
        break;

    // Use the index of element found in postorder to divide postorder array in two parts. Left subtree and right subtree
    if (i <= hi) {
      root->left = solve(low, i);
      root->right = solve(i+1, hi);
    }

    return root;
  };

  return solve(0, n-1);
}

/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
 */
vector<vector<int>> zigzag(const BinTreeNode* root) {
  if (!root)
    return {{}};

  vector<vector<int>> ret;
  stack<const BinTreeNode*> stk[2];
  stk[0].push(root);
  uint idx = 0;

  while (!stk[idx].empty()) {
    ret.push_back(vector<int>());

    while (!stk[idx].empty()) {
      const BinTreeNode* nd = stk[idx].top();
      stk[idx].pop();
      ret.back().push_back(nd->value);
      if (idx) {
        if (nd->right)
          stk[!idx].emplace(nd->right);
        if (nd->left)
          stk[!idx].emplace(nd->left);
      } else {
        if (nd->left)
          stk[!idx].emplace(nd->left);
        if (nd->right)
          stk[!idx].emplace(nd->right);
      }
    }

    idx = !idx;
  }

  return ret;
}

/*
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
 */
vector<vector<int>> bottomupLevelorder(const BinTreeNode* root) {
  if (!root)
    return {};

  vector<vector<int>> ret;
  deque<const BinTreeNode*> q = {root};
  stack<string> output;

  while (!q.empty()) {
    ret.push_back(vector<int>());
    const uint sz = q.size();
    for (uint i = 0; i < sz; ++i) {
      const BinTreeNode* nd = q.front();
      q.pop_front();
      //ostringstream oss;
      ret.back().push_back(nd->value);
    //  output.push(oss.str()+", ");
      if (nd->left)
        q.push_back(nd->left);
      if (nd->right)
        q.push_back(nd->right);
    }
  }
/*
  while (!output.empty()) {
    cout << output.top();
    output.pop();
  }*/
  return ret;
}

/*
Given a binary tree, print it vertically.
 */
vector<vector<int>> vertical_recur(const BinTreeNode* root) {
  if (!root)
    return {};

  map<int,vector<int>> m;

  function<void(const BinTreeNode*,const int)> solve =
    [&](const BinTreeNode* curr_root, const int hdist) {
    if (!curr_root)
      return;

    m[hdist].push_back(curr_root->value);
    solve(curr_root->left, hdist-1);
    solve(curr_root->right, hdist+1);
  };

  solve(root, 0);

  vector<vector<int>> ret;
  for (map<int,vector<int>>::iterator it = m.begin(); it != m.end(); ++it)
    ret.push_back(it->second);

  return ret;
}

/*
Given a Binary Tree, print left view of it. Left view of a Binary Tree is set of nodes visible when tree is visited from left side. Left view of following tree is 12, 10, 25.
        12
       /  \
     10   30
         /  \
        25  40
 */
void leftView(const BinTreeNode* root) {
  int max_lvl = MIN_LMT;
  function<void(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;

    // If this is the first node of its level
    if (max_lvl < curr_lvl) {
      cout << curr_root->value << " ";
      max_lvl = curr_lvl;
    }

    // Recur for left and right subtrees
    solve(curr_root->left, curr_lvl+1);
    solve(curr_root->right, curr_lvl+1);
  };

  solve(root, 0);
}

/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].
 */
vector<int> rightView(const BinTreeNode* root) {
  if (!root)
    return {};

  vector<int> ret;
  deque<const BinTreeNode*> q = {root};
  const BinTreeNode* curr = root;

  while (!q.empty()) {
    const BinTreeNode* nd = q.front();
    q.pop_front();
    ret.push_back(nd->value);
    if (nd->right)
      q.push_back(nd->right);
  }

  return ret;
}

/*
Given a binary tree, we need to print the bottom view from left to right. A node x is there in output if x is the bottommost node at its horizontal distance. Horizontal distance of left child of a node x is equal to horizontal distance of x minus 1, and that of right child is horizontal distance of x plus 1.
                      20
                    /    \
                  8       22
                /   \      \
              5      3      25
                    / \
                  10    14

For the above tree the output should be 5, 10, 3, 14, 25.
 */
struct HDBinTreeNode {
  int hd;
  int value;
  HDBinTreeNode* left, *right;
};

void bottomView(HDBinTreeNode* root) {
  if (!root)
    return;

  int hd = 0;

  // TreeMap which stores key value pair sorted on key value
  map<int,int> recs;
  root->hd = hd;

  deque<const HDBinTreeNode*> q = {root};
  while (!q.empty()) {
    const HDBinTreeNode* tmp = q.front();
    q.pop_front();
    hd = tmp->hd;

    // Put the dequeued tree node to TreeMap having key as horizontal distance. Every time we find a node having same horizontal distance we need to replace the data in the map.
    recs[hd] = tmp->value;

    // If the dequeued node has a left child add it to the queue with a horizontal distance hd-1.
    if (tmp->left) {
      tmp->left->hd = hd-1;
      q.push_back(tmp->left);
    }

    // If the dequeued node has a left child add it to the queue with a horizontal distance hd+1.
    if (tmp->right) {
      tmp->right->hd = hd+1;
      q.push_back(tmp->right);
    }
  }
}

/*
Top view of a binary tree is the set of nodes visible when the tree is viewed from the top.
Given a binary tree, print the top view of it. The output nodes can be printed in any order.
Expected time complexity is O(n)
       1
    /     \
   2       3
  /  \    / \
 4    5  6   7
Top view of the above binary tree is
4 2 1 3 7

        1
      /   \
    2       3
      \
        4
          \
            5
             \
               6
Top view of the above binary tree is
2 1 3 6
 */
void topView(HDBinTreeNode* root) {
  if (!root)
    return;

  set<int> st;
  root->hd = 0;
  // Create a queue and add root to it
  deque<const HDBinTreeNode*> q = {root};
  while (!q.empty()) {
    const HDBinTreeNode* curr = q.front();
    q.pop_front();

    int hd = curr->hd;
    // If this is the first node at its horizontal distance, then this node is in top view
    if (!st.count(hd)) {
      st.insert(hd);
      cout << curr->value + " ";
    }

    if (curr->left) {
      curr->left->hd = hd-1;
      q.push_back(curr->left);
    }

    if (curr->right) {
      curr->right->hd = hd+1;
      q.push_back(curr->right);
    }
  }
}

/*
Using Morris Traversal, we can traverse the tree without using stack and recursion.
The algorithm for Preorder is almost similar to Morris traversal for Inorder.

1. If left child is null, print the current node data. Move to right child.
   Else, make the right child of the inorder predecessor point to the current node.
   Two cases arise:
     a) The right child of the inorder predecessor already points to the current node.
        Set right child to NULL. Move to right child of current node.
     b) The right child is NULL. Set it to current node.
        Print current node's data and move to left child of current node.
2. Iterate until current node is not NULL.
 */
void morrisTraversalPreorder(BinTreeNode* root) {
  while (root) {
    // If left child is null, print the current node data. Move to right child.
    if (!root->left) {
      cout << root->value << " ";
      root = root->right;
    } else {
      // Find inorder predecessor
      BinTreeNode* curr = root->left;
      while (curr->right && curr->right != root)
        curr = curr->right;

      // If the right child of inorder predecessor already points to this node
      if (curr->right == root) {
        curr->right = nullptr;
        root = root->right;
      } else { // If right child doesn't point to this node, then print this node and make right child point to this node
        cout << root->value << " ";
        curr->right = root;
        root = root->left;
      }
    }
  }
}

/*
Given a Binary Tree, find size of the Largest Independent Set(LIS) in it.
A subset of all tree nodes is an independent set if there is no edge between any two nodes of the subset.
 */
uint LISSize(const BinTreeNode* root) { // O(n*n)
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;

    // Caculate size excluding the current node
    uint size_excl = solve(curr_root->left)+solve(curr_root->right);

    // Calculate size including the current node
    uint size_incl = 1;
    if (curr_root->left)
      size_incl += solve(curr_root->left->left)+solve(curr_root->left->right);
    if (curr_root->right)
      size_incl += solve(curr_root->right->left)+solve(curr_root->right->right);

    // Return the maximum of two sizes
    return max(size_incl, size_excl);
  };

  return solve(root);
}

// A memoization function returns size of the largest independent set in a given binary tree
struct MemoBinTreeNode {
  uint liss;
  BinTreeNode* node;
};

uint LISSize_dp(MemoBinTreeNode* root) { // O(n)
  function<uint(MemoBinTreeNode*)> solve =
    [&](MemoBinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;
    if (curr_root->liss)
      return curr_root->liss;
    if (!curr_root->node->left && !curr_root->node->right) {
      curr_root->liss = 1;
      return curr_root->liss;
    }

    // Calculate size excluding the current node
    MemoBinTreeNode lsub;
    lsub.liss = 0;
    lsub.node = curr_root->node->left;
    MemoBinTreeNode rsub;
    rsub.liss = 0;
    rsub.node = curr_root->node->right;

    uint liss_excl = solve(&lsub)+solve(&rsub);
    // Calculate size including the current node
    uint liss_incl = 1;
    if (lsub.node) {
      MemoBinTreeNode llsub;
      llsub.liss = 0;
      llsub.node = lsub.node->left;
      MemoBinTreeNode rlsub;
      rlsub.liss = 0;
      rlsub.node = lsub.node->right;

      liss_incl += solve(&llsub)+solve(&rlsub);
    }
    if (rsub.node) {
      MemoBinTreeNode lrsub;
      lrsub.liss = 0;
      lrsub.node = rsub.node->left;
      MemoBinTreeNode rrsub;
      rrsub.liss = 0;
      rrsub.node = rsub.node->right;

      liss_incl += solve(&lrsub)+solve(&rrsub);
    }
    // Maximum of two sizes is LIS size, store it for future uses.
    curr_root->liss = max(liss_incl, liss_excl);
    return curr_root->liss;
  };

  return solve(root);
}

/*
Wirte a function which extracts all leaves from given Binary Tree.
 */
// The function returns new root of Binary Tree (Note that root may change if Binary Tree has only one node).  The function also sets head_ref as head of doubly linked list. left pointer of tree is used as prev in DLL and right pointer is used as next
const BinTreeNode* extractLeafList(BinTreeNode* root) {
  BinTreeNode* head_ref = root;

  function<BinTreeNode*(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) -> BinTreeNode* {
    if (!curr_root)
      return nullptr;

    if (!curr_root->left && !curr_root->right) { // This node is going to be added to doubly linked list of leaves, set right pointer of this node as previous head of DLL. We don't need to set left pointer as left is already NULL
      curr_root->right = head_ref;

      // Change left pointer of previous head
      if (head_ref)
        head_ref->left = curr_root;

      // Change head of linked list
      head_ref = curr_root;
      return nullptr;  // Return new root
    }

    // Recur for right and left subtrees
    curr_root->right = solve(curr_root->right);
    curr_root->left  = solve(curr_root->left);
    return curr_root;
  };

  return solve(root);
}

/*
Given a binary tree, convert it to a cricular doubly linked list.
 */
BinTreeNode* bt2CDList(BinTreeNode* root) { // O(n)
  BinTreeNode* head = nullptr; // this pointer should have the address of in-order predecessor of root
  BinTreeNode* prev = nullptr; // this denoted head of final link list

  function<void(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);

    // current node's left points to previous node
    curr_root->left = prev;
    if (prev)
      prev->right = curr_root; // previous node's right points to current node
    else
      head = curr_root; // if previous is NULL that current node is head

    BinTreeNode* right = curr_root->right; // saving right node
    // we need to make list created till now as circular
    head->left = curr_root;
    curr_root->right = head;

    //For right-subtree/parent, current node is in-order predecessor
    prev = curr_root;
    solve(right);
  };

  solve(root);
  return head;
}

/*
Write a function to detect if two trees are isomorphic. Two trees are called isomorphic if one of them can be obtained from other by a series of flips, i.e. by swapping left and right children of a number of nodes. Any number of nodes at any level can have their children swapped. Two empty trees are isomorphic.
 */
bool isIsomorphic(const BinTreeNode* r1, const BinTreeNode* r2) {
  function<bool(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) {
    // Both roots are NULL, trees isomorphic by definition
    if (!curr_root1 && !curr_root2)
      return true;

    // Exactly one of the n1 and n2 is NULL, trees not isomorphic
    if (!curr_root1 || !curr_root2)
      return false;

    if (curr_root1->value != curr_root2->value)
      return false;

    // There are two possible cases for curr_root1 and curr_root2 to be isomorphic
    // Case 1: The subtrees rooted at these nodes have NOT been "Flipped". Both of these subtrees have to be isomorphic, hence the &&
    // Case 2: The subtrees rooted at these nodes have been "Flipped"
    return (solve(curr_root1->left, curr_root2->left) && solve(curr_root1->right, curr_root2->right)) ||
           (solve(curr_root1->left, curr_root2->right) && solve(curr_root1->right, curr_root2->left));
  };

  return solve(r1, r2);
}

/*
Given a a Binary Tree, find the difference between the sum of nodes at odd level and the sum of nodes at even level. Consider root as level 1, left and right children of root as level 2 and so on.
 */
int levelDiff(const BinTreeNode* root) {
  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return 0;

    // Difference for root is root's value - difference for left subtree difference for right subtree
    return curr_root->value-solve(curr_root->left)-solve(curr_root->right);
  };

  return solve(root);
}

/*
Write a C code to get the depth of the deepest odd level leaf node in a binary tree. Consider that level starts with 1. Depth of a leaf node is number of nodes on the path from root to leaf (including both leaf and root).
 */
uint deepestOddLevelLeafDepth(const BinTreeNode* root) {
  function<uint(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) -> uint {
    if (!curr_root)
      return 0;

    // If this node is a leaf and its level is odd, return its level
    if (!curr_root->left && !curr_root->right && (curr_lvl&1))
      return curr_lvl;

    // If not leaf, return the maximum value from left and right subtrees
    return max(solve(curr_root->left, curr_lvl+1), solve(curr_root->right, curr_lvl+1));
  };

  return solve(root, 1);
}

/*
Given a Binary Tree, check if all leaves are at same level or not.
 */
bool onSameLevel(const BinTreeNode* root) {
  vector<uint> recs;

  function<void(const BinTreeNode*, const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;

    if (!curr_root->left && !curr_root->right)
      recs.push_back(curr_lvl);
    else {
      solve(curr_root->left, curr_lvl+1);
      solve(curr_root->right, curr_lvl+1);
    }
  };

  solve(root, 0);
  return (recs.size() > 1) ? false : true;
}

/*
Find all root-to-leaf paths of a binary tree
 */
vector<vector<const BinTreeNode*>> allR2LPaths_recur(const BinTreeNode* root) {
  if (!root)
    return {};

  vector<vector<const BinTreeNode*>> ret;

  function<void(const BinTreeNode*,vector<const BinTreeNode*>)> solve =
    [&](const BinTreeNode* curr_root, vector<const BinTreeNode*> curr_path) {
    if (!curr_root)
      return;

    curr_path.push_back(curr_root);
    if (!curr_root->left && !curr_root->right) { /* it's a leaf, so print the path that led to here  */
      ret.push_back(curr_path);
      return;
    } else {
      solve(curr_root->left, curr_path);
      solve(curr_root->right, curr_path);
    }
  };

  vector<const BinTreeNode*> path;
  solve(root, path);
  return ret;
}

vector<vector<const BinTreeNode*>> allR2LPaths_iter(const BinTreeNode* root) {
  if (!root)
    throw exception();

  vector<vector<const BinTreeNode*>> paths = {{root}};
  uint idx = 0;
  while (true) {
    const uint n = paths.size();
    uint added = 0;

    for (; idx < n; ++idx) {
      //auto& path = paths[idx];
      auto nd = paths[idx].back();
      if (nd->left) {
        vector<const BinTreeNode*> ext(paths[idx]);
        ext.push_back(nd->left);
        paths.push_back({nd->left});
        paths.push_back(ext);
        ++added;
      }
      if (nd->right) {
        vector<const BinTreeNode*> ext(paths[idx]);
        ext.push_back(nd->right);
        paths.push_back({nd->right});
        paths.push_back(ext);
        ++added;
      }
    }

    if (!added)
      break;
  }

/*  int res = min_lmt;
  vector<const BinTreeNode*> maxsum_path;

  for (auto& path : paths) {
    int path_sum = 0;
    for (auto nd : path) {
      path_sum += nd->value;
    }

    if (res < path_sum) {
      res = path_sum;
      maxsum_path = path;
    }
  }

  cout << "Max path sum is: " << res << endl;
  for (auto nd : maxsum_path)
    cout << nd->value << "->";
  cout << endl;

  return res;*/
  return paths;
}

/*
Given a binary tree, how do you remove all the half nodes (which has only one child)? Note leaves should not be touched as they have both children as NULL.
 */
const BinTreeNode* removeHalfNodes(BinTreeNode* root) {
  function<BinTreeNode*(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) -> BinTreeNode* {
    if (!curr_root)
      return nullptr;

    curr_root->left = solve(curr_root->left);
    curr_root->right = solve(curr_root->right);

    if (!curr_root->left && !curr_root->right)
      return curr_root;

    /* if current nodes is a half node with NULL left child, then it's right child is returned and replaces it in the given tree */
    if (!curr_root->left) {
      BinTreeNode* new_root = curr_root->right;
      delete curr_root; //  curr_root = nullptr;
      return new_root;
    }
    /* if current nodes is a half node with NULL right child, then it's right child is returned and replaces it in the given tree  */
    if (!curr_root->right) {
      BinTreeNode* new_root = curr_root->left;
      delete curr_root; // curr_root = nullptr
      return new_root;
    }

    return curr_root;
  };

  return solve(root);
}

/*
Given a Binary Tree, find sum of all left leaves in it.
 */
int leftLeavesSum(const BinTreeNode* root) {
  int ret = 0;

  function<int(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return 0;

    if (isLeaf(curr_root->left))
      ret += curr_root->left->value;
    else // Else recur for left child of root
      ret += solve(curr_root->left);

    // Recur for right child of root and update result
    ret += solve(curr_root->right);
  };

  solve(root);
  return ret;
}

/*
Given a binary tree and a key 'k', find distance of the closest leaf from 'k'.
 */
uint closestLeaf(const BinTreeNode* root, const int k) {
  function<uint(const BinTreeNode*)> closestDown =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return MAX_LMT;
    if (!curr_root->left && !curr_root->right)
      return 0;

    return 1+min(closestDown(curr_root->left), closestDown(curr_root->right));
  };

  const BinTreeNode* ancestors[count_recur(root)];
  function<uint(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint idx) -> uint {
    if (!curr_root)
      return MAX_LMT;

    if (curr_root->value == k) {
      // Find the cloest leaf under the subtree rooted with given key
      uint ret = closestDown(curr_root);

      // Traverse all ancestors and update result if any parent node gives smaller distance
      for (int i = idx-1; i >= 0; --i)
        ret = min(ret, idx-i+closestDown(ancestors[i]));

      return ret;
    }

    // If key node found, store current node and recur for left and right childrens
    ancestors[idx] = curr_root;
    return min(solve(curr_root->left, idx+1), solve(curr_root->right, idx+1));
  };

  return solve(root, 0);
}

/*
Given a Binary Tree and a key, write a function that returns level of the key.
 */
uint levelNum(const BinTreeNode* root, const int target) {
  function<uint(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_lvl) -> uint {
    if (!curr_root)
      return 0;
    if (curr_root->value == target)
        return curr_lvl;

    uint ret = solve(curr_root->left, curr_lvl+1);
    if (!ret)
      ret = solve(curr_root->right, curr_lvl+1);

    return ret;
  };

  return solve(root, 1);
}

/*
A perfect binary tree is a binary tree with all leaf nodes at the same depth. All internal nodes have degree 2.
Print nodes in level order but nodes should be from left and right side alternatively.
 */
void specificLevelOrder(const BinTreeNode* root) {
  if (!root)
    return;

  cout << root->value;
  if (root->left)
    cout << " " << root->left->value << " " << root->right->value;

  // Do anything more if there are nodes at next level in given perfect Binary Tree
  if (!root->left->left)
    return;

  // Create a queue and enqueue left and right children of root
  deque<const BinTreeNode*> q;
  q.push_back(root->left);
  q.push_back(root->right);

  // We process two nodes at a time, so we need two variables to store two front items of queue
  const BinTreeNode* first = nullptr, *second = nullptr;

  while (!q.empty()) {
    // Pop two items from queue
    first = q.front();
    q.pop_front();
    second = q.front();
    q.pop_front();

    cout << " " << first->left->value << " " << second->right->value;
    cout << " " << first->right->value << " " << second->left->value;

    // If first and second have grandchildren, enqueue them in reverse order
    if (first->left->left) {
      q.push_back(first->left);
      q.push_back(second->right);
      q.push_back(first->right);
      q.push_back(second->left);
    }
  }
}

/*
Given a Perfect Binary Tree, reverse the alternate level nodes of the binary tree.
               a
            /     \
           b       c
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
       h  i j  k l  m  n  o

Modified tree:
               a
            /     \
           c       b
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
      o  n m  l k  j  i  h

A tricky solution is to do two inorder traversals. Following are steps to be followed.
1) Traverse the given tree in inorder fashion and store all odd level nodes in an auxiliary array. For the above example given tree, contents of array become {h, i, b, j, k, l, m, c, n, o}

2) Reverse the array. The array now becomes {o, n, c, m, l, k, j, b, i, h}

3) Traverse the tree again inorder fashion. While traversing the tree, one by one take elements from array and store elements from array to every odd level traversed node.
 */
#define MAX 500

void reverseAlternate(BinTreeNode* root) {
  char A[MAX];
  uint idx = 0;

  function<void(BinTreeNode*,const uint)> storeAlternate =
    [&](BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;

    // Store elements of left subtree
    storeAlternate(curr_root->left, curr_lvl+1);
    // Store this node only if this is a odd level node
    if (curr_lvl%2) {
      A[idx++] = curr_root->value;
    }

    // Store elements of right subtree
    storeAlternate(curr_root->right, curr_lvl+1);
  };

  // First store nodes of alternate levels
  storeAlternate(root, 0);

  // utility function to reverse an array from index 0 to n-1
  function<void(const uint)> reverse = [&](const uint n) {
    uint left = 0, right = n-1;
    while (left < right) {
      char tmp = A[left];
      A[left] = A[right];
      A[right] = tmp;
      ++left;
      --right;
    }
  };
  // Reverse the array
  reverse(idx);

  // Update tree by taking elements from array
  idx = 0;

  // Function to modify Binary Tree (All odd level nodes are updated by taking elements from array in inorder fashion)
  function<void(BinTreeNode*,const uint)> modifyTree =
    [&](BinTreeNode* curr_root, const uint curr_lvl) {
    if (!curr_root)
      return;

    // Update nodes in left subtree
    modifyTree(curr_root->left, curr_lvl+1);
    // Update this node only if this is an odd level node
    if (curr_lvl%2) {
      curr_root->value = A[idx++];
    }

    // Update nodes in right subtree
    modifyTree(curr_root->right, curr_lvl+1);
  };

  modifyTree(root, 0);
}

/*
Print all nodes between two levels
 */
void twoLevels(const BinTreeNode* root, const uint low, const uint high) {
  BinTreeNode* marker = new BinTreeNode(MIN_LMT); // Marker node to indicate end of level
  uint level = 1;

  // Enqueue the only first level node and marker node for end of level
  deque<const BinTreeNode*> q = {root, marker};
//  q.push_back(marker);

  while (!q.empty()) {
    const BinTreeNode* curr = q.front();
    q.pop_front();

    // Check if end of level is reached
    if (curr == marker) {
      // print a new line and increment level number
      cout << endl;
      ++level;

      // Check if marker node was last node in queue or level number is beyond the given upper limit
      if (q.empty() || level > high)
        break;

      // Enqueue the marker for end of next level
      q.push_back(marker);

      // If this is marker, then we don't need print it and enqueue its children
      continue;
    }

    // If level is equal to or greater than given lower level, print it
    if (level >= low)
      cout << curr->value << " ";

    // Enqueue children of non-marker node
    if (curr->left)
      q.push_back(curr->left);
    if (curr->right)
      q.push_back(curr->right);
  }
}

/*
Given the binary Tree and the two nodes say 'a' and 'b', determine whether the two nodes are cousins of each other or not.

Two nodes are cousins of each other if they are at same level and have different parents.
 */
bool areCousins(const BinTreeNode* root, const BinTreeNode* a, const BinTreeNode* b) {
  function<bool(const BinTreeNode*)> areSiblings = [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return false;

    return ((curr_root->left == a && curr_root->right == b) ||
            (curr_root->left == b && curr_root->right == a) ||
            areSiblings(curr_root->left) ||
            areSiblings(curr_root->right));
  };

  // Recursive function to find level of BinTreeNode 'ptr' in a binary tree
  function<uint(const BinTreeNode*,const uint,const BinTreeNode*)> level =
    [&](const BinTreeNode* curr_root, const uint curr_lvl, const BinTreeNode* target) -> uint {
    if (!curr_root)
      return 0;
    if (curr_root == target)
      return curr_lvl;

    // Return level if BinTreeNode is present in left subtree
    uint ret = level(curr_root->left, curr_lvl+1, target);
    if (ret)
      return ret;

    return level(curr_root->right, curr_lvl+1, target);
  };

  // 1. The two BinTreeNodes should be on the same level in the binary tree.
  // 2. The two BinTreeNodes should not be siblings (means that they should not have the same parent Node).
  uint lvl1 = level(root, 1, a);
  uint lvl2 = level(root, 1, b);

  return (lvl1 == lvl2 && !areSiblings(root)) ? true : false;
}

/*
Given two binary trees, check if the first tree is subtree of the second one. A subtree of a tree T is a tree S consisting of a node in T and all of its descendants in T.
 */
bool isSubtree(const BinTreeNode* T, const BinTreeNode* S) { // O(n2)
  function<bool(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root1, const BinTreeNode* curr_root2) {
    if (!curr_root2)
      return true;
    if (!curr_root1)
      return false;

    /* Check the tree with root as current node */
    if (areIdentical(curr_root1, curr_root2))
      return true;

    /* If the tree with root as current node doesn't match then try left and right subtrees one by one */
    return solve(curr_root1->left, curr_root2) || solve(curr_root1->right, curr_root2);
  };

  return solve(T, S);
}

/*
This is an O(n) solution. The idea is based on the fact that inorder and preorder/postorder uniquely identify a binary tree. Tree S is a subtree of T if both inorder and preorder traversals of S are substrings of inorder and preorder traversals of T respectively.
 */
bool isSubtree_2(const BinTreeNode* T, const BinTreeNode* S) {
  if (!S)
    return true;
  if (!T)
    return false;

  function<void(const BinTreeNode*,char [],uint&)> storeInorder =
    [&](const BinTreeNode* curr_root, char A[], uint& idx) {
    if (!curr_root) {
      A[idx++] = '$';
      return;
    }
    storeInorder(curr_root->left, A, idx);
    A[idx++] = curr_root->value;
    storeInorder(curr_root->right, A, idx);
  };

  // Store Inorder traversals of T and S in inT[0..m-1] and inS[0..n-1] respectively
  uint m = 0, n = 0;
  char inT[MAX], inS[MAX];
  storeInorder(T, inT, m);
  storeInorder(S, inS, n);
  inT[m] = '\0', inS[n] = '\0';

  // If inS[] is not a substring of preS[], return false
  if (!strstr(inT, inS))
    return false;

  function<void(const BinTreeNode*,char [],uint&)> storePreOrder =
    [&](const BinTreeNode* curr_root, char A[], uint& idx) {
    if (!curr_root) {
      A[idx++] = '$';
      return;
    }
    A[idx++] = curr_root->value;
    storePreOrder(curr_root->left, A, idx);
    storePreOrder(curr_root->right, A, idx);
  };

  // Store Preorder traversals of T and S in inT[0..m-1] and inS[0..n-1] respectively
  m = 0;
  n = 0;
  char preT[MAX], preS[MAX];
  storePreOrder(T, preT, m);
  storePreOrder(S, preS, n);
  preT[m] = '\0', preS[n] = '\0';

  // If inS[] is not a substring of preS[], return false else return true
  return strstr(preT, preS);
}

/*
Given a Binary Tree, print all nodes that don't have a sibling (a sibling is a node that has same parent. In a Binary Tree, there can be at most one sibling). Root should not be printed as root cannot have a sibling.
 */
void allSingles(const BinTreeNode* root) {
  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    // If this is an internal node, recur for left and right subtrees
    if (curr_root->left && curr_root->right) {
      solve(curr_root->left);
      solve(curr_root->right);
    } else if (curr_root->right) { // If left child is NULL and right is not, print right child and recur for right child
      cout << curr_root->right->value << " ";
      solve(curr_root->right);
    } else if (curr_root->left) { // If right child is NULL and left is not, print left child and recur for left child
      cout << curr_root->left->value << " ";
      solve(curr_root->left);
    }
  };

  return solve(root);
}

/*
Find next right of given key k, it returns NULL if k is not present in tree or k is the rightmost node of its level
 */
const BinTreeNode* nextRight(const BinTreeNode* root, const int target) {
  if (!root)
    return 0;

  deque<const BinTreeNode*> q = {root};

  while (!q.empty()) {
    const uint sz = q.size();
    for (uint i = 0; i < sz; ++i) {
      const BinTreeNode* curr = q.front();
      q.pop_front();
      if (curr->value == target)
        return q.empty() ? nullptr : q.front();
      else {
        if (curr->left)
          q.push_back(curr->left);
        if (curr->right)
          q.push_back(curr->right);
      }
    }
  }

  return nullptr;
}

/*
Given a Binary Tree, find the maximum sum path from a leaf to root.
 */
int maxR2LPathSum(const BinTreeNode* root) {
  int ret = MIN_LMT;
  const BinTreeNode* leaf = nullptr;

  function<void(const BinTreeNode*,const int)> solve =
    [&](const BinTreeNode* curr_root, const int curr_pathsum) {
    if (!curr_root)
      return;

    const int new_pathsum = curr_pathsum+curr_root->value;

    if (isLeaf(curr_root)) {
      ret = max(ret, new_pathsum);
      leaf = curr_root;
    }

    solve(curr_root->left, new_pathsum);
    solve(curr_root->right, new_pathsum);
  };

  solve(root, 0);
  // we also have max-sum path's leaf node...
  return ret;
}

/*
Given a binary tree, a complete path is defined as a path from root to a leaf. The sum of all nodes on that path is defined as the sum of that path. Given a number k, you have to remove (prune the tree) all nodes which don't lie in any path with sum >= k.
 */
BinTreeNode* prune(BinTreeNode* root, const int k) {
  function<BinTreeNode*(BinTreeNode*,int&)> solve =
    [&](BinTreeNode* curr_root, int& curr_pathsum) -> BinTreeNode* {
    if (!curr_root)
      return nullptr;

    const int new_sum = curr_pathsum+curr_root->value;
    // Initialize left and right sums as sum from root to this node (including this node)
    int lsum = new_sum, rsum = new_sum;

    // Recursively prune left and right subtrees
    curr_root->left = solve(curr_root->left, lsum);
    curr_root->right = solve(curr_root->right, rsum);

    // Get the maximum of left and right sums
    curr_pathsum = max(lsum, rsum);
    // If maximum is smaller than k, then this node must be deleted
    if (curr_pathsum < k) {
      delete curr_root;
      curr_root = nullptr;
    }

    return curr_root;
  };

  int x = 0;
  return solve(root, x);
}

/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Return the sum = 12 + 13 = 25.
 */
uint r2lNumsSum_iter(const BinTreeNode* root) {
  if (!root)
    throw exception();

  deque<pair<const BinTreeNode*,uint>> paths;
  paths.push_back({root, root->value});
  uint ret = 0;

  while (!paths.empty()) {
    const BinTreeNode* curr = paths.front().first;
    const uint tmp = paths.front().second;
    paths.pop_front();
    if (curr->left) {
      paths.push_back({curr->left, tmp*10+curr->left->value});
    }
    if (curr->right) {
      paths.push_back({curr->right, tmp*10+curr->right->value});
    }
    if (!curr->left && !curr->right)
      ret += tmp;
  }

  return ret;
}

uint r2lNumsSum_recur(const BinTreeNode* root) {
  if (!root)
    throw exception();

  function<uint(const BinTreeNode*,const uint)> solve =
    [&](const BinTreeNode* curr_root, const uint curr_pathnum) -> uint {
    if (!curr_root)
      return 0;

    const uint new_num = 10*curr_pathnum + curr_root->value;
    return (!curr_root->left && !curr_root->right) ? new_num :
            (solve(curr_root->left, new_num)+solve(curr_root->right, new_num));
  };

  return solve(root, 0);
}

/*
Given a binary tree and a sum, determine if the tree has a root-to-leaf path
such that adding up all the values along the path equals the given sum.
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
 */
bool r2lPathWithSum_recur(const BinTreeNode* root, const int sum) {
  function<bool(const BinTreeNode*,const int)> solve =
    [&](const BinTreeNode* curr_root, const int remain) -> bool {
    if (!curr_root)
      return false;

    if (curr_root->value == remain && !curr_root->left && !curr_root->right)
      return true;

    return solve(curr_root->left, remain-curr_root->value) ||
           solve(curr_root->right, remain-curr_root->value);
  };

  return solve(root, sum-0);
}

/*
Given a binary tree, flatten it to a linked list in-place.
         1
        / \
       2   5
      / \   \
     3   4   6

The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
 */
void flatten_recur(BinTreeNode* root) {
  function<void(BinTreeNode*)> solve = // DFS
    [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->right);
    solve(curr_root->left);

    if (curr_root->left) {
      BinTreeNode* p = curr_root->left;
      while (p->right)
        p = p->right;

      p->right = curr_root->right;
      curr_root->right = curr_root->left;
      curr_root->left = nullptr;
    }
  };

  return solve(root);
}

void flatten_recur2(BinTreeNode* root) {
  function<BinTreeNode*(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) -> BinTreeNode* {
    if (!curr_root)
      return nullptr;
    if (!curr_root->left && !curr_root->right)
      return curr_root;

    if (curr_root->left) {
      BinTreeNode* mostleft = solve(curr_root->left);
      BinTreeNode* old = curr_root->right;
      curr_root->right = curr_root->left;
      if (mostleft)
        mostleft->right = old;

      curr_root->left = nullptr;
      return old ? solve(old) : mostleft;
    } else {
      return solve(curr_root->right);
    }
  };

  solve(root);
}

void flatten_iter(BinTreeNode* root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  stack<BinTreeNode*> stk;
  stk.push(root);

  while (!stk.empty()) {
    BinTreeNode* curr = stk.top();
    stk.pop();
    if (curr->right)
      stk.push(curr->right);
    if (curr->left)
      stk.push(curr->left);

    curr->left = nullptr;
    curr->right = stk.empty() ? nullptr : stk.top();
  }
}
/*
void serialize_recur(const BinTreeNode* root, ostream& out) { // pre-order traversal does it all!
  function<void(const BinTreeNode*,ostream&)> solve =
    [&](const BinTreeNode* curr_root, ostream& out) {
    if (!curr_root) {
      out << "# ";
    } else {
      out << curr_root->value << " ";
      solve(curr_root->left, out);
      solve(curr_root->right, out);
    }
  };

  return solve(root, out);
}

void deserialize_recur(BinTreeNode*& root, ifstream& fin) {
  function<void(BinTreeNode*&,ifstream&)> solve =
    [&](BinTreeNode*& curr_root, ifstream& fin) {
    int value;
    bool isNumber;

    if (!readNextToken(value, fin, isNumber))
      return;
    if (isNumber) {
      curr_root = new BinTreeNode(value);
      solve(curr_root->left, fin);
      solve(curr_root->right, fin);
    }
  };

  return solve(root, fin);
}
*/
/*
Consider lines of slope -1 passing between nodes (dotted lines in below diagram). Diagonal sum in a binary tree is sum of all node's data lying between these lines. Given a Binary Tree, print all diagonal sums.
 */
struct VDBinTreeNode {
  int value;
  int vd; // vertical distance
  VDBinTreeNode* left, *right;
};

int diagonalSum(VDBinTreeNode* root) {
  if (!root)
    return 0;

  // Map to store sum of node's data lying diagonally
  map<int,int> recs;

  // Assign the root's vertical distance as 0.
  root->vd = 0;
  // Add root node to the queue
  deque<VDBinTreeNode*> q = {root};

  while (!q.empty()) {
    // Remove the front tree node from queue.
    VDBinTreeNode* curr = q.front();
    q.pop_front();

    // Get the vertical distance of the dequeued node.
    int vd = curr->vd;

    // Sum over this node's right-child, right-of-right-child and so on
    while (curr) {
      int prevSum = recs.count(vd) ? recs[vd] : 0;
      recs[vd] = prevSum+curr->value;

      // If for any node the left child is not null add it to the queue for future processing.
      if (curr->left) {
        curr->left->vd = vd+1;
        q.push_back(curr->left);
      }

      // Move to the current node's right child.
      curr = curr->right;
    }
  }

  for (auto& i : recs) {
  }
}

/*
Left-Right representation of a binary tree is standard representation
where every node has a pointer to left child and another pointer to right child.
Down-Right representation is an alternate representation where every node
has a pointer to left (or first) child and another pointer to next sibling.
So siblings at every level are connected from left to right.
The conversion should happen in-place, i.e., left child pointer should be used
as down pointer and right child pointer should be used as right sibling pointer.
 */

void convert2DownRight(BinTreeNode* root) {
  if (!root)
    return;

  deque<BinTreeNode*> q = {root};
  BinTreeNode* first = root;

  while (1) {
        // nodeCount (queue size) indicates number of nodes
        // at current lelvel.
    uint node_cnt = q.size();
    if (!node_cnt)
      break;

    BinTreeNode* prev = nullptr;  // Stores link of previously dequeued node.

    // Dequeue all nodes of current level and Enqueue all nodes of next level
    while (node_cnt > 0) {
      // Dequeue a node and enqueue its children for next iteration of outer loop
      BinTreeNode* node = q.front();
      q.pop_front();
      if (node->left)
        q.push_back(node->left);
      if (node->right)
        q.push_back(node->right);

      // If prev exists, then connect this node as right sibling of prev.
      if (prev) {
        prev->right = node;
        // Since prev is not NULL, this is not the first node of its level,
        // so make the down (or left) pointer NULL
        node->left = nullptr;
      } else { // If previous doesn't exist then link this node as down
               // to first node of previous level. And set the first node
        first->left = node;
        first = node;
      }

      // Update prev and nodecount
      prev = node;
      --node_cnt;
    }

    prev->right = nullptr; // For last node in current level
  }
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

  cout << "Size of binary tree: " << count_recur(root) << endl;
  cout << "Max leaf-to-leaf path sum: " << maxL2LPathSum(root) << endl;
//  cout << "Distance between nodes with max leaf-to-leaf path sum: " << distance(root, root->right->left, root->right->right->right->right->left) << endl;
  cout << "Distance between " << root->left->left->left << " and " << root->right->right->right->right->left << ": " << distance(root, root->left->left->left, root->right->right->right->right->left) << endl;

  cout << "Max leaf-to-leaf path length: " << diameter(root) << endl;

  int a1[] = {5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12, 15};
  root = nullptr;

  for (uint i = 0; i < 13; ++i) {
    bstInsert_recur(&root, a1[i]); // construct a BST; we just use it for convenience
  }

  cout << "Tree is " << (isHeightBalanced(root) ? "" : "not ") << "height balanced!" << endl;
  cout << "Tree is " << (isSymmetric(root) ? "" : "not ") << "symmetric!" << endl;
  cout << "Tree is " << (isSymmetric2(root) ? "" : "not ") << "symmetric!" << endl;

  vector<int> a = {5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12, 15};
  root = nullptr;

  for (uint i = 0; i < a.size(); ++i) {
    bstInsert_recur(&root, a[i]); // construct a BST; we just use it for convenience
  }

  cout << "Inorder traversal iterative:" << endl;
  vector<int> res = inorder_iter(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Inorder traversal recursive:" << endl;
  res = inorder_recur(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Preorder traversal iterative:" << endl;
  res = preorder_iter(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Preorder traversal recursive:" << endl;
  res = preorder_recur(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Postorder traversal iterative:" << endl;
  res = postorder_iter(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Postorder traversal iterative with 2 stacks:" << endl;
  res = postorder_iter_2stacks(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Postorder traversal recursive:" << endl;
  res = postorder_recur(root);
  for (auto i : res) {
    cout << i << " ";
  }
  cout << endl;

  prettyPrint(root);
 /*
  vector<int> li = {8, 4, 2, 5, 1, 6, 3, 7};
  vector<int> ri = {8, 4, 5, 2, 6, 7, 3, 1};

  root = in_post_recur(li, ri);
  bfsPrint(root);
  cout << endl;

  li.clear();
  ri.clear();
  BinTreeNode* re = in_post_recur(li, ri);
  bfsPrint(re);
  cout << endl;
 */
  BinTreeNode root2(3), fir(9), sec(20), thr(15), four(7);
  root2.left = &fir;
  root2.right = &sec;
  sec.left = &thr;
  sec.right = &four;
  cout << "Zigzag traversal:" << endl;
  vector<vector<int>> res2 = zigzag(&root2);
  for (auto& i : res2) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  root = new BinTreeNode(1);
  root->left = new BinTreeNode(2);
  root->right = new BinTreeNode(3);
  root->left->left = new BinTreeNode(4);
  root->left->right = new BinTreeNode(5);
  root->right->left = new BinTreeNode(6);
  root->right->right = new BinTreeNode(7);
  root->right->left->right = new BinTreeNode(8);
  root->right->right->right = new BinTreeNode(9);

  cout << "Vertical order traversal is \n";
  res2 = vertical_recur(root);
  for (auto& i : res2) {
    for (auto j : i)
      cout << j << " ";
    cout << endl;
  }

  delete root->left->left;
  root->left->left = nullptr;
  root->left->right = new BinTreeNode(5);
  delete root->right->left;
  root->right->left = nullptr;
  root->right->right = new BinTreeNode(4);
  vector<int> res3 = rightView(root);
  for (auto i : res3)
    cout << i << " ";
  cout << endl;

  root = new BinTreeNode(5);
  BinTreeNode l1(4);
  BinTreeNode l2(11);
  BinTreeNode l3(7);
  BinTreeNode l4(2);
  BinTreeNode r1(8);
  BinTreeNode r2(13);
  BinTreeNode r3(4);
  BinTreeNode r4(5);
  BinTreeNode r5(1);

  BinTreeNode* rt = root;
  rt->right = &r1;
  rt->left = &l1;
  l1.left = &l2;
  l2.left = &l3;
  l2.right = &l4;
  r1.right = &r2;
  r2.right = &r3;
  r3.left = &r4;
  r3.right = &r5;
  cout << "Max path sum: " << maxR2LPathSum(rt) << endl;

  int n = 22;
  if (r2lPathWithSum_recur(rt, n))
    cout << "There are path(s) that have sum " << n << endl;

  BinTreeNode root1(0);
  BinTreeNode l11(6);
  BinTreeNode l21(2);
  BinTreeNode r11(4);
  BinTreeNode r21(5);

  const BinTreeNode* rt1 = &root1;
  root1.right = &r11;
  r11.right = &r21;
  root1.left = &l11;
  l11.left = &l21;
  cout << r2lNumsSum_recur(rt1) << endl;

  a = {5, 3, 8, 1, -4, 7, 10, 2, -6, 9, 11, 12, 15};
  root = nullptr;

  for (uint i = 0; i < a.size(); ++i) {
    bstInsert_recur(&root, a[i]); // construct a BST here: we just use it for convenience
  }
  flatten_recur(root);
  delTree_iter(&root);

  for (uint i = 0; i < a.size(); ++i) {
    bstInsert_recur(&root, a[i]); // reconstruct the BST
  }
  flatten_iter(root);
  delTree_iter(&root);

  for (uint i = 0; i < a.size(); ++i) {
    bstInsert_recur(&root, a[i]); // reconstruct the BST
  }
  flatten_recur2(root);
  delTree_iter(&root);

  root = new BinTreeNode(1);
  root->left = new BinTreeNode(2);
  root->right = new BinTreeNode(3);
  root->left->left = new BinTreeNode(4);
  root->left->right = new BinTreeNode(5);
  root->right->left = new BinTreeNode(6);
  root->right->right = new BinTreeNode(7);
  const BinTreeNode* nd = LCA(root, 4, 5);
  if (nd)
    cout << "LCA(4, 5) = " << nd->value << endl;
  else
    cout << "Keys are not present." << endl;

  nd = LCA(root, 4, 10);
  if (nd)
    cout << "LCA(4, 10) = " << nd->value << endl;
  else
    cout << "Keys are not present." << endl;

  delTree_iter(&root);

  root = new BinTreeNode(5);
  l1.value = 4;
  l2.value = 11;
  l3.value = 7;
  l4.value = 2;
  r1.value = 8;
  r2.value = 13;
  r3.value = 4;
  r4.value = 5;
  r5.value = 1;

  rt = root;
  rt->right = &r1;
  rt->left = &l1;
  l1.left = &l2;
  l2.left = &l3;
  l2.right = &l4;
  r1.right = &r2;
  r2.right = &r3;
  r3.left = &r4;
  r3.right = &r5;

  vector<vector<int>> paths = r2lPathsWithSum_recur(rt, n);
  for (uint i = 0; i < paths.size(); ++i) {
    for (uint j = 0; j < paths[i].size(); ++j) {
      cout << paths[i][j] << ",";
    }
    cout << endl;
  }

  return 0;
}
