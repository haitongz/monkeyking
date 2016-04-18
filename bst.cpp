#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <stack>
#include <functional>
#include <algorithm>
#include <iomanip>

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

void delTree_iter(BinTreeNode** root) {
  if (!root) {
#ifdef _DEBUG_
    cerr << "Null root!" << endl;
#endif
    return;
  }

  deque<const BinTreeNode*> q{*root};

  while (!q.empty()) {
    const uint cp = q.size();
    for (uint i = 0; i < cp; ++i) {
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
  function<void(BinTreeNode**)> solve =
    [&](BinTreeNode** ndp) { // DFS, postorder
    if (!ndp)
      throw exception();
    else if (*ndp) {
      BinTreeNode* nd = *ndp;
      solve(&(nd->left));
      solve(&(nd->right));
      delete nd;
      nd = NULL;
    }
  };

  solve(root);
}

bool insert_recur(BinTreeNode** root, const int key) {
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

const BinTreeNode* search_recur(const BinTreeNode* root, const int target) {
  function<const BinTreeNode*(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root || curr_root->value == target)
      return curr_root;

    return (curr_root->value < target) ?
      solve(curr_root->right) : solve(curr_root->left);
  };

  return solve(root);
}

/*
Given values of two nodes in a Binary Search Tree, find the Lowest Common Ancestor (LCA). You may assume that both the values exist in the tree.
 */
const BinTreeNode* LCA_recur(const BinTreeNode* root, const int n1, const int n2) {
  function<const BinTreeNode*(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> const BinTreeNode* {
    if (!curr_root)
      return nullptr;

    // If both n1 and n2 are smaller than root, then LCA lies in left
    if (curr_root->value > n1 && curr_root->value > n2)
      return solve(curr_root->left);
    // If both n1 and n2 are greater than root, then LCA lies in right
    if (curr_root->value < n1 && curr_root->value < n2)
      return solve(root->right);

    return curr_root;
  };

  return solve(root);
}

const BinTreeNode* LCA_iter(const BinTreeNode* root, const int n1, const int n2) {
  if (!root) {
    return nullptr;
  }

  const BinTreeNode* curr = root;
  while (curr) {
    if (n1 < curr->value && n2 < curr->value) {
      curr = curr->left;
    } else if (n1 > curr->value && n2 > curr->value) {
      curr = curr->right;
    } else {
      return curr;
    }
  }

  return nullptr;
}

/*
Validate whether a binary tree is a BST
 */
/*
   this method is WRONG!
bool validate(const BinTreeNode* root) {
  function<bool(const BinTreeNode*)> solve = [](const BinTreeNode* curr_root) {
    if (!curr_root ||
        (curr_root->left && curr_root->left->value > curr_root->value)
        (curr_root->right && curr_root->right->value < curr_root->value))
      return false;

    return solve(curr_root->left) && solve(curr_root->right);
  };

  return solve(root);
}

Is this wrong too?

bool validate(const BinTreeNode* root) {
  const BinTreeNode* prev_root = nullptr;

  function<bool(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) { // O(n), traverse the tree in inorder fashion and keep track of prev node
    if (!curr_root)
      return true;
    else if (!solve(curr_root->left))
      return false;

    // Allows only distinct valued nodes
    if (prev_root && curr_root->value <= prev_root->value)
      return false;

    prev_root = curr_root;
    return solve(curr_root->right);
  };

  return solve(root);
}
 */
bool validate(const BinTreeNode* root) {
  function<bool(const BinTreeNode*,const int,const int)> solve =
    [&](const BinTreeNode* curr_root, const int left_min, const int right_max) {
    if (!curr_root)
      return true;

    if (curr_root->value <= left_min || curr_root->value > right_max)
      return false;

    if (!solve(curr_root->left, left_min, curr_root->value) ||
        !solve(curr_root->right, curr_root->value, right_max)) {
      return false;
    } else {
      return true;
    }
  };

  return solve(root, MIN_LMT, MAX_LMT);
}

/*
Given a target number, find closest number in a BST
 */
int closest_recur(const BinTreeNode* root, const int target) {
  function<const BinTreeNode*(const BinTreeNode*)> solve = // DFS
    [&](const BinTreeNode* curr_root) -> const BinTreeNode* {
    if (!curr_root)
      return nullptr;

    if (curr_root->value == target)
      return curr_root;
    else if (target < curr_root->value) {
      if (!curr_root->left)
        return curr_root;

      const BinTreeNode* left_res = solve(curr_root->left);
      if (left_res)
        return (abs(left_res->value-target) < abs(curr_root->value-target)) ? left_res : curr_root;
    } else {
      if (!curr_root->right)
        return curr_root;

      const BinTreeNode* right_res = solve(curr_root->right);
      if (right_res)
        return (abs(right_res->value-target) < abs(curr_root->value-target)) ? right_res : curr_root;
    }

    return nullptr;
  };

  const BinTreeNode* ret = solve(root);
  if (ret)
    return ret->value;
  else
    return MIN_LMT;
}

int closest_iter(const BinTreeNode* root, const int target) { // BFS
  if (!root)
    throw exception();

  deque<const BinTreeNode*> q = {root};
  const BinTreeNode* ret = nullptr;
  uint min_diff = MAX_LMT;

  while (!q.empty()) {
    const BinTreeNode* curr = q.front();
    q.pop_front();
    if (target == curr->value)
      return target;
    else {
      const uint diff = abs(target-curr->value);
      if (diff < min_diff) {
        ret = curr;
        min_diff = diff;
      }

      if (curr->left)
        q.push_back(curr->left);
      if (curr->right)
        q.push_back(curr->right);
    }
  }

  //assert(ret);
  return ret->value;
}

/*
Given k, find k-th smallest element in a BST
 */
int kthSmallest_recur(const BinTreeNode* root, const uint k) {
  if (!root || !k)
    throw exception();

  int ret = MAX_LMT, cntr = 0;

  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);

    if (++cntr == k) {
      ret = curr_root->value;
      return;
    }

    solve(curr_root->right);
  };

  solve(root);
  return ret;
}

/*
Given k, find k-th largest element in a BST.
 */
int kthLargest_recur(const BinTreeNode* root, const uint k) {
  if (!root || !k)
    throw exception();

  int ret = MIN_LMT, cntr = 0;

  function<void(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->right);

    if (++cntr == k) {
      ret = curr_root->value;
      return;
    }

    // Recur for left subtree
    solve(curr_root->left);
  };

  solve(root);
  return ret;
}

int kthSmallest_iter(const BinTreeNode* root, const uint k) {
  if (!root || !k)
    throw exception();

  // simply inorder traversal
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

  uint i = 0;
  for (; i < k && i < ret.size(); ++i);

  if (i < k) { // less than k elements in BST
  }

  return ret[i-1];
}

/*
Find common nodes of two BSTs.
Iterative inorder traversal, Time complexity: O(n)
Space complexity: O(h1+h2) where h1 and h2 are heights of first and second BSTs respectively.
 */
/*
vector<int> commonNodes(BinTreeNode* r1, BinTreeNode* r2) {
  if (!r1 || !r2)
    return {};

  vector<int> ret;
  stack<BinTreeNode*> p, q;
  BinTreeNode* n1 = r1, *n2 = r2;

  while (true) {
    if (n1) {
      p.push(n1);
      n1 = n1->left;
    } else if (n2) {
      q.push(n2);
      n2 = n2->left;
    } else if (!p.empty() && !q.empty()) {
      n1 = p.top();
      n2 = q.top();

      if (n1->value < n2->value) {
        p.pop();
        n1 = n1->right;
        n2 = nullptr;
      } else if (n2->value < n1->value) {
        q.pop();
        n2 = n2->right;
        n1 = nullptr;
      } else {
        ret.push_back(n1->value);
        p.pop();
        q.pop();
        n1 = n1->right;
        n2 = n2->right;
      }
    } else
      break;
  }

  return ret;
}
*/
vector<int>
commonNodes_recur(BinTreeNode* r1, BinTreeNode* r2) {
  set<int> ret;

  function<void(BinTreeNode*,BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root1, BinTreeNode* curr_root2) {
    if (!curr_root1 || !curr_root2)
      return;

    if (curr_root1->value == curr_root2->value) {
      ret.insert(curr_root1->value);
      solve(curr_root1->left, curr_root2->left);
      solve(curr_root1->right, curr_root2->right);
    } else if (curr_root1->value < curr_root2->value) {
      solve(curr_root1, curr_root2->left);
      solve(curr_root1->right, curr_root2);
    } else {
      solve(curr_root1, curr_root2->right);
      solve(curr_root1->left, curr_root2);
    }
  };

  solve(r1, r2);
  return {ret.begin(), ret.end()};
}

/*
Merge two balanced BSTs into a single balanced BST.
Your merge function should take O(M+N) time and O(1) space.
 */

/*
Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
 */
struct ListNode {
  ListNode(const int v)
      : value(v), next(NULL) {
  }

  int value;
  ListNode* next;
};

BinTreeNode* sortedList2BST(ListNode* head) {
  auto middle = [](ListNode* start, ListNode* end) {
    auto fast = start;
    auto slow = start;
    while (fast != end && fast->next != end) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  };

  function<BinTreeNode*(ListNode*,ListNode*)> solve =
    [&](ListNode* start, ListNode* end) -> BinTreeNode* {
    if (!start || start == end)
      return nullptr;

    if (start->next == end)
      return new BinTreeNode(start->value);

    auto mid = middle(start, end);
    auto root = new BinTreeNode(mid->value);
    root->left = solve(start, mid);
    root->right = solve(mid->next, end);
    return root;
  };

  return solve(head, nullptr);
}

/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 */
BinTreeNode* sortedArray2BST(const vector<int>& nums) {
  const uint n = nums.size();
  if (!n)
    return nullptr;

  function<BinTreeNode*(uint,uint)> solve =
    [&](const uint start, const uint end) -> BinTreeNode* {
    if (!start || start == end)
      return nullptr;

    if (start == end)
      return new BinTreeNode(nums[start]);

    auto mid = start + (end-start)>>1;
    auto root = new BinTreeNode(nums[mid]);
    root->left = solve(start, mid);
    root->right = solve(mid+1, end);
    return root;
  };

  return solve(0, n);
}

/*
How about convert a sorted doubly linked list to a binary search tree? You must do it in place without creating any new nodes.
 */
struct DListNode {
  int value;
  DListNode* prev;
  DListNode* next;

  DListNode(const int v)
      : value(v), prev(nullptr), next(nullptr) {
  }
};

DListNode* sortedDList2BST(DListNode* head) {
  auto middle = [](DListNode* start, DListNode* end) {
    auto fast = start;
    auto slow = start;
    while (fast != end && fast->next != end) {
      fast = fast->next->next;
      slow = slow->next;
    }

    return slow;
  };

  function<DListNode*(DListNode*,DListNode*)> solve =
    [&](DListNode* start, DListNode* end) -> DListNode* {
    if (!start || start == end)
      return nullptr;

    if (start->next == end) {
      start->prev = start->next = nullptr;
      return start;
    }

    auto mid = middle(start, end);
    mid->prev = solve(start, mid);
    mid->next = solve(mid->next, end);
    return mid;
  };

  return solve(head, nullptr);
}

DListNode* bst2SortedDList(BinTreeNode* root) {
  DListNode dummy(MIN_LMT);
  DListNode* curr = &dummy;

  function<void(BinTreeNode*)> solve = [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);
    auto new_node = new DListNode(curr_root->value);
    curr->next = new_node;
    new_node->prev = curr;
    curr = new_node;

    solve(curr_root->right);
  };

  solve(root);

  if (dummy.next)
    dummy.next->prev = nullptr;

  return dummy.next;
}

void bst2DLL_recur(BinTreeNode* root, BinTreeNode** head, BinTreeNode** tail) {
  function<void(BinTreeNode*)> solve = [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    // First convert the left subtree
    if (curr_root->left)
      solve(root->left);

    // Then change left of current root as last node of left subtree
    curr_root->left = *tail;

    // If tail is not NULL, then set right of tail as root, else current node is head
    if (*tail)
      (*tail)->right = curr_root;
    else
      *head = curr_root;

    // Update tail
    *tail = curr_root;

    // Finally, convert right subtree
    if (curr_root->right)
      solve(curr_root->right);
  };

  solve(root);
}

/*
Two BSTs were given, find the largest common BST exists between these two
 */
struct Item {
  const BinTreeNode* node1;
  const BinTreeNode* node2;
  uint count;

  Item() :
      node1 {nullptr}, node2 {nullptr}, count {0} {
  }
};

Item LCBST_recur(const BinTreeNode* root1, const BinTreeNode* root2) {
  function<Item(const BinTreeNode*,const BinTreeNode*)> solve =
    [&](const BinTreeNode* nd1, const BinTreeNode* nd2) {
    if (!nd1 || !nd2) {
      Item it;
      it.node1 = nullptr;
      it.node2 = nullptr;
      it.count = 0;
      return it;
    }

    if (nd1->value < nd2->value) {
      Item i1 = solve(nd1, nd2->left);
      Item i2 = solve(nd1->right, nd2);
      Item it = i1;
      return (i1.count < i2.count) ? i2 : i1;
    }
    if (nd1->value > nd2->value) {
      Item i1 = solve(nd1->left, nd2);
      Item i2 = solve(nd1, nd2->right);
      return (i1.count < i2.count) ? i2 : i1;
    }

    Item left = solve(nd1->left, nd2->left);
    Item right = solve(nd1->right, nd2->right);
    Item it = (left.count < right.count) ? right : left;

    if (left.node1 == nd1->left &&
        left.node2 == nd2->left &&
        right.node1 == nd1->right &&
        right.node2 == nd2->right) {
      it.node1 = nd1;
      it.node2 = nd2;
      it.count = left.count + right.count + 1;
    }

    return it;
  };

  return solve(root1, root2);
}

/*
Finds predecessor and successor of key in BST.
 */
pair<const BinTreeNode*,const BinTreeNode*>
predecessorAndSuccessor(const BinTreeNode* root, const int key) {
  pair<const BinTreeNode*,const BinTreeNode*> ret;

  function<void(const BinTreeNode*)> solve = [&](const BinTreeNode* curr_root) {
    if (!curr_root)
      return;
    else if (curr_root->value == key) {
      if (curr_root->left) { // the maximum value in left subtree is predecessor
        const BinTreeNode* tmp = curr_root->left;
        while (tmp->right)
          tmp = tmp->right;

        ret.first = tmp;
      }

      if (curr_root->right) { // the minimum value in right subtree is successor
        const BinTreeNode* tmp = curr_root->right;
        while (tmp->left)
          tmp = tmp->left;
        ret.second = tmp;
      }

      return;
    } else if (curr_root->value > key) {
      ret.second = curr_root;
      solve(curr_root->left);
    } else { // go to right subtree
      ret.first = curr_root;
      solve(curr_root->right);
    }
  };

  solve(root);
  return ret;
}

/*
Given a BST, transform it into greater sum tree where each node contains sum of all nodes greater than that node.
 */
void transformBST2GST(BinTreeNode* root) { // reverse inorder traversal to get decreasing ordered elements
  int sum = 0;

  function<void(BinTreeNode*)> solve = [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    // Recur for right subtree
    solve(curr_root->right);

    // Update sum
    sum += curr_root->value;

    // Store old sum in current node
    curr_root->value = sum;

    // Recur for left subtree
    solve(curr_root->left);
  };

  solve(root);
  prettyPrint(root);
}

/*
Given two arrays which represent a sequence of keys. Imagine we make a BST from each array.
We need to tell whether two BSTs will be identical or not without actually constructing the tree.
 */
/*
The main function that checks if two arrays a[] and b[] of size n construct same BST. The two values 'min' and 'max' decide whether the call is made for left subtree or right subtree of a parent element. The indecies idx1 and idx2 are the indecies in (a[] and b[]) after which we search the left or right child. Initially, the call is made for INT_MIN and INT_MAX as 'min' and 'max' respectively, because root has no parent. idx1 and idx2 are just after the indecies of the parent element in a[] and b[].
 */
bool identicalBSTs(const int a[], const int b[], const uint n) { // O(n)
  function<bool(const int,const int,const int,const int)> solve =
    [&](const int idx1, const int idx2, const int min, const int max) {
    uint i, j;

    /* Search for a value satisfying the constraints of min and max in a[] and b[]. If the parent element is a leaf node then there must be some elements in a[] and b[] satisfying constraint. */
    for (i = idx1; i < n; ++i)
      if (a[i] > min && a[i] < max)
        break;

    for (j = idx2; j < n; ++j)
      if (b[j] > min && b[j] < max)
        break;

    /* If the parent element is leaf in both arrays */
    if (i == n && j == n)
      return true;

    /* Return false if any of the following is true
      a) If the parent element is leaf in one array, but non-leaf in other.
      b) The elements satisfying constraints are not same. We either search
         for left child or right child of the parent element (decinded by min
         and max values). The child found must be same in both arrays */
    if (((i == n)^(j == n)) || a[i] != b[j])
      return false;

    /* Make the current child as parent and recursively check for left and right
      subtrees of it. Note that we can also pass a[k] in place of a[i] as they
      are both are same */
    return solve(i+1, j+1, a[i], max) && // Right Subtree
           solve(i+1, j+1, min, a[i]);   // Left Subtree
  };

  return solve(0, 0, MIN_LMT, MAX_LMT);
}

/*
Two elements of a BST are swapped by mistake. Recover the tree without changing its structure.

Note:
Devise a constant space solution
 */
void recoverBST(BinTreeNode* root) {
  vector<BinTreeNode*> nodes;
  BinTreeNode* prev = nullptr;

  function<void(BinTreeNode*)> solve =
    [&](BinTreeNode* curr_root) {
    if (!curr_root)
      return;

    solve(curr_root->left);

    if (prev && prev->value > curr_root->value) {
      nodes.push_back(prev);
      nodes.push_back(curr_root);
    }

    prev = curr_root;
    solve(curr_root->right);
  };

  solve(root);
  swap(nodes.front()->value, nodes.back()->value);
}

/*
Given a Binary Search Tree (BST) of integer values and a range [low, high],
return count of nodes where all the nodes under that node
(or subtree rooted with that node) lie in the given range.
 */
uint inRangeSubtreeNum(const BinTreeNode* root, const pair<int,int>& range) {
  function<uint(const BinTreeNode*)> getCount =
    [&](const BinTreeNode* curr_root) -> uint {
    if (!curr_root)
      return 0;

    return getCount(curr_root->left)+getCount(curr_root->right)+1;
  };

  uint ret = 0;

  function<void(const BinTreeNode*,int,int)> solve =
    [&](const BinTreeNode* curr_root, int low, int high) { // returns true if nodes in subtree rooted under 'root' are in range.
    if (!curr_root)
      return;

    if (range.first > high || range.second < low)
      return;

    if (range.first <= low && range.second >= high) {
      ret += getCount(curr_root);
      return;
    }

    if (curr_root->left)
      solve(curr_root->left, low, curr_root->value);
    if (curr_root->right)
      solve(curr_root->right, curr_root->value, high);

    if (!curr_root->left && !curr_root->right &&
        (curr_root->value >= range.first && curr_root->value <= range.second))
      ret += 1;
  };

  solve(root, MIN_LMT, MAX_LMT);
  return ret;
}

/*
Given a BST, modify it so that all greater values in the given BST are added to every node.
For example:
              50
           /      \
         30        70
        /   \      /  \
      20    40    60   80

The above tree should be modified to following
              260
           /      \
         330        150
        /   \       /  \
      350   300    210   80
 */
// Recursive function to add all greater values in every node
void modifyBST(BinTreeNode* root) {
  function<void(BinTreeNode*,int&)> solve =
    [&](BinTreeNode* curr_root, int& curr_sum) {
    if (!curr_root)
      return;

    // Recur for right subtree
    solve(curr_root->right, curr_sum);

    // Now sum has sum of nodes in right subtree, add curr_root->value to sum
    // and update curr_root->value

    curr_sum += curr_root->value;
    curr_root->value = curr_sum;

    solve(curr_root->left, curr_sum);
  };

  int x = 0;
  solve(root, x);
}

/*
Given a Balanced Binary Search Tree and a target sum, write a function that returns true if there is a pair with sum equals to target sum, otherwise return false. Expected time complexity is O(n) and only O(Logn) extra space can be used. Any modification to Binary Search Tree is not allowed. Note that height of a Balanced BST is always O(Logn).
 */
bool foundPairWithSum(const BinTreeNode* root, const int sum) {
  // Create two stacks. stk1 is used for normal inorder traversal and stk2 is used for reverse inorder traversal
  stack<const BinTreeNode*> stk1; //MAX_SIZE);
  stack<const BinTreeNode*> stk2; //MAX_SIZE);

  // Note the sizes of stacks is MAX_SIZE, we can find the tree size and fix stack size as O(Logn) for balanced trees like AVL and Red Black tree. We have used MAX_SIZE to keep the code simple

  // done1, val1 and curr1 are used for normal inorder traversal using s1
  // done2, val2 and curr2 are used for reverse inorder traversal using s2
  bool done1 = false, done2 = false;
  int val1 = 0, val2 = 0;
  const BinTreeNode* curr1 = root, *curr2 = root;

  // The loop will break when we either find a pair or one of the two traversals is complete
  while (true) {
    while (!done1) { // Find next node in normal Inorder traversal. See following post
      if (curr1) {
        stk1.push(curr1);
        curr1 = curr1->left;
      } else {
        if (stk1.empty())
          done1 = true;
        else {
          curr1 = stk1.top();
          stk1.pop();
          val1 = curr1->value;
          curr1 = curr1->right;
          done1 = true;
        }
      }
    }

    // Find next node in REVERSE Inorder traversal. The only difference between above and below loop is, in below loop right subtree is traversed before left subtree
    while (!done2) {
      if (curr2) {
        stk2.push(curr2);
        curr2 = curr2->right;
      } else {
        if (stk2.empty())
          done2 = true;
        else {
          curr2 = stk2.top();
          stk2.pop();
          val2 = curr2->value;
          curr2 = curr2->left;
          done2 = true;
        }
      }
    }

    if ((val1 != val2) && (val1+val2 == sum))
      // printf("\n Pair Found: %d + %d = %d\n", val1, val2, target);
      return true;
    else if (val1+val2 < sum) // If sum of current values is smaller, then move to next node in normal inorder traversal
      done1 = false;
    else if (val1+val2 > sum) // If sum of current values is greater, then move to next node in reverse inorder traversal
      done2 = false;

    // If any of the inorder traversals is over, then there is no pair so return false
    if (val1 >= val2)
      return false;
  }
}

/*
Given a Balanced Binary Search Tree (BST), find out whether there is a triplet in given BST with sum equals to 0. Expected time complexity is O(n^2) and only O(Logn) extra space can be used. You can modify given Binary Search Tree. Note that height of a Balanced BST is always O(Logn)
 */
bool foundTripletWithSum(BinTreeNode* root) {
  if (!root)
    return false;

  // Convert given BST to doubly linked list: head and tail store the pointers
  // to first and last nodes in DLL
  BinTreeNode* head = nullptr;
  BinTreeNode* tail = nullptr;

  bst2DLL_recur(root, &head, &tail);

  function<bool(BinTreeNode*,BinTreeNode*,const int)> foundPairWithSum =
    [&](BinTreeNode* head, BinTreeNode* tail, const int sum) {
    while (head != tail) {
      int curr = head->value + tail->value;
      if (curr == sum)
        return true;
      else if (curr > sum)
        tail = tail->left;
      else
        head = head->right;
    }

    return false;
  };

  // Now iterate through every node and find if there is a pair with sum equal to -1 * heaf->key where head is current node
  while ((head->right != tail) && (head->value < 0)) {
    // If there is a pair with sum equal to  -1*head->key, then return true else move forward
    if (foundPairWithSum(head->right, tail, -1*head->value))
      return true;
    else
      head = head->right;
  }

  // If we reach here, then there was no 0 sum triplet
  return false;
}

/*
Given an array that stores a complete Binary Search Tree, write a function that efficiently prints the given array in ascending order.
 */
void printSorted(int A[], const uint n) {
  if (!n)
    throw exception();

  function<void(const uint,const uint)> solve =
    [&](const uint start, const uint end) { // inorder, O(n)
    if (start > end)
      return;

    // print left subtree
    solve(start*2+1, end);

    // print root
    cout << A[start] << " ";
    // print right subtree
    solve(start*2+2, end);
  };

  return solve(0, n-1);
}

/*
Given a Binary Tree, write a function that returns the size of the largest subtree which is also a Binary Search Tree (BST). If the complete Binary Tree is BST, then return the size of whole tree.
 */
/*
uint largestBSTSize(const BinTreeNode* root) { // O(n2)
  if (validate(root))
    return size(root);
  else
    return max(largestBSTSize(root->left), largestBSTSize(root->right));
}
*/
uint largestBSTSize_recur(const BinTreeNode* root) { // O(n)
  int gmin = MAX_LMT;  // For minimum value in right subtree
  int gmax = MIN_LMT;  // For maximum value in left subtree
  bool is_bst = false;
  uint ret = 0;

  /* solve updates the size of the largest BST subtree. Also, if the tree rooted with node is non-empty and a BST then returns size of the tree. Otherwise returns 0. */
  function<uint(const BinTreeNode*)> solve =
    [&](const BinTreeNode* curr_root) -> uint {//, int *min_ref, int *max_ref, int *max_size_ref, bool *is_bst_ref)
    if (!curr_root) {
      is_bst = true; // An empty tree is BST
      return 0;    // Size of the BST is 0
    }

 //   int lmin = MAX_LMT;
    /* Following tasks are done by recursive call for left subtree
    a) Get the maximum value in left subtree (Stored in *max_ref)
    b) Check whether Left Subtree is BST or not (Stored in *is_bst_ref)
    c) Get the size of maximum size BST in left subtree (updates *max_size) */

    gmax = MIN_LMT;
    uint left = solve(curr_root->left); //, min_ref, max_ref, max_size_ref, is_bst_ref);
    /* A flag variable for left subtree property i.e., max(root->left) < root->data */
    bool left_flag = false;
    if (is_bst && curr_root->value > gmax)
      left_flag = true;

    /* Before updating *min_ref, store the min value in left subtree. So that we have the correct minimum value for this subtree */
    int lmin = gmin;
    /* The following recursive call does similar (similar to left subtree) task for right subtree */
    gmin = MAX_LMT;
    uint right = solve(curr_root->right); //, min_ref, max_ref, max_size_ref, is_bst_ref);
    /* A flag variable for right subtree property i.e., min(root->right) > root->data */
    bool right_flag = false;
    if (is_bst && curr_root->value < lmin)
      right_flag = true;

    // Update min and max values for the parent recursive calls
    gmin = min(lmin, gmin);
    gmin = min(curr_root->value, gmin); // For leaf nodes
    gmax = max(curr_root->value, gmax);

    /* If both left and right subtrees are BST. And left and right subtree properties hold for this node, then this tree is BST. So return the size of this tree */
    if (left_flag && right_flag) {
      ret = max(left+right+1, ret);
      return (uint)left+right+1;
    } else {
      //Since this subtree is not BST, set is_bst flag for parent calls
      is_bst = false;
      return 0;
    }
  };

  solve(root); //, node, &min, &max, &max_size, &is_bst);
  return ret;
}

/*
Get inorder successor in a binatry search tree
 */
const BinTreeNode* inOrderSuccessor(const BinTreeNode* root, const BinTreeNode* nd) {
  function<const BinTreeNode*(const BinTreeNode*)> minValue =
    [&](const BinTreeNode* n) {
    const BinTreeNode* curr = n;
    while (curr->left)
      curr = curr->left;

    return curr;
  };

  if (nd->right)
    return minValue(nd->right);

  const BinTreeNode* ret = nullptr;
  while (root) {
    if (nd->value < root->value) {
      ret = root;
      root = root->left;
    } else if (nd->value > root->value) {
      root = root->right;
    } else
      break;
  }

  return ret;
}

BinTreeNode* construct_pre_recur(const int pre[], const uint n) { // from preorder traversal: O(n)
  if (!n)
    return nullptr;

  uint pre_idx = 0;

  function<BinTreeNode*(const int,const uint,const uint)> solve =
    [&](const int key, const uint min, const uint max) -> BinTreeNode* {
    if (pre_idx >= n)
      return nullptr;

    BinTreeNode* ret = nullptr;

    // If current element of pre[] is in range, then only it is part of current subtree
    if (key > min && key < max) {
      // Allocate memory for root of this subtree and increment *preIndex
      ret = new BinTreeNode(key);
      if (++pre_idx < n) {
        // Contruct the subtree under root
        // All nodes which are in range {min .. key} will go in left
        // subtree, and first such node will be root of left subtree.
        ret->left = solve(pre[pre_idx], min, key);
        // All nodes which are in range {key..max} will go in right
        // subtree, and first such node will be root of right subtree.
        ret->right = solve(pre[pre_idx], key, max);
      }
    }

    return ret;
  };

  return solve(pre[0], MIN_LMT, MAX_LMT);
}

/*
Construct all possible BSTs for keys 1 to N
 */
vector<BinTreeNode*> construct_1ToN(const uint N) {
  function<vector<BinTreeNode*>(const uint,const uint)> solve =
    [&](const uint start, const uint end) {
    vector<BinTreeNode*> ret;

    if (start > end) {
      ret.push_back(nullptr);
      return ret;
    }

    /* iterating through all values from start to end
       for constructing left and right subtree recursively */
    for (uint i = start; i < end+1; ++i) {
      vector<BinTreeNode*> left = solve(start, i-1);
      vector<BinTreeNode*> right = solve(i+1, end);
      /* now loop through all left and right subtrees
         and connect them to i-th root below */
      for (uint j = 0; j < left.size(); ++j) {
        BinTreeNode* l_root = left[j];
        for (uint k = 0; k < right.size(); ++k) {
          BinTreeNode* r_root = right[k];
          BinTreeNode* nd = new BinTreeNode(i); // making value i as root
          nd->left = l_root; // connect left subtree
          nd->right = r_root; // connect right subtree
          ret.push_back(nd); // add this tree to list
        }
      }
    }

    return ret;
  };

  return solve(1, N);
}

int main(int argc, char** argv) {
  int a[] = {5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12, 15};
  BinTreeNode* r = nullptr;

  for (uint i = 0; i < 13; ++i) {
    insert_recur(&r, a[i]);
  }

  cout << "The tree just built is" << (validate(r) ? " " : " not ") << "a BST!" << endl;

  int t = 16;
  cout << "Closet node to " << t << " is " << closest_recur(r, t) << endl;
  cout << "Closet node to " << t << " is " << closest_iter(r, t) << endl;

  const uint k = 2;
  const string s = (k == 1) ? "st" : ((k == 2) ? "nd" : (k == 3 ? "rd" : "th"));
  cout << k << s << " smallest node in BST: " << kthSmallest_recur(r, k) << endl;
  cout << k << s << " smallest node in BST: " << kthSmallest_iter(r, k) << endl;
  cout << k << s << " largest node in BST: " << kthLargest_recur(r, k) << endl;

  int a1[] = {5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12, 15};

  cout << "BSTs are" << (identicalBSTs(a, a1, 13) ? " " : " not ") << "identical!" << endl;

  BinTreeNode* r2 = nullptr;
  for (uint i = 0; i < 13; ++i) {
    insert_recur(&r2, a1[i]);
  }
  prettyPrint(r);
  prettyPrint(r2);

  Item it = LCBST_recur(r, r2);
  cout << "Largest common BST size: " << it.count << endl;
  cout << "Largest common BST root in tree 1: " << it.node1 << ", in tree 2: " << it.node2 << endl;

  //BinTreeNode* r3 = mergeBSTs(r, r2);
  //prettyPrint(r3);

  swap(r2->right->value, r2->value);
  recoverBST(r2);
  prettyPrint(r2);

  delTree_recur(&r);
  delTree_recur(&r2);


  /* constructed BST
        10
       / \
      5	 50
     /  / \
    1  40 100
   */
  insert_recur(&r, 10);
  insert_recur(&r, 5);
  insert_recur(&r, 50);
  insert_recur(&r, 1);
  insert_recur(&r, 40);
  insert_recur(&r, 100);
  insert_recur(&r, 10);
  insert_recur(&r, 10);

  int l = 5, h = 50;
  cout << "LCA of " << l << " and " << h << " is " << LCA_recur(r, l, h)->value << endl;
  cout << "LCA of " << l << " and " << h << " is " << LCA_iter(r, l, h)->value << endl;

  //int l = 5;
  //int h = 45;

  cout << "Count of subtrees in [" << l << ", " << h << "] is "
    << inRangeSubtreeNum(r, make_pair(l, h)) << endl;
  delTree_recur(&r);

  r = nullptr;
  r2 = nullptr;

  insert_recur(&r, 5);
  insert_recur(&r, 1);
  insert_recur(&r, 10);
  insert_recur(&r, 0);
  insert_recur(&r, 4);
  insert_recur(&r, 7);
  insert_recur(&r, 9);

  insert_recur(&r2, 10);
  insert_recur(&r2, 7);
  insert_recur(&r2, 20);
  insert_recur(&r2, 4);
  insert_recur(&r2, 9);

  vector<int> res = commonNodes_recur(r, r2);
  for (const auto& i : res)
    cout << i << " ";
  cout << endl;

 /* vector<BinTreeNode*> res2 = construct_1ToN(3);
 */
  return 0;
}
