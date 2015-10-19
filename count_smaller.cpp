/*
Write a function to count number of smaller elements on right of each element in an array. Given an unsorted array a[]
of distinct integers, construct another array countSmaller[] such that countSmaller[i] contains count of smaller elements
on right side of each element a[i] in array.
 */

/*
A Self Balancing Binary Search Tree (AVL, Red Black,.. etc) can be used to get the solution in O(nLogn) time complexity.
We can augment these trees so that every node N contains size the subtree rooted with N. We have used AVL tree in the
following implementation.

We traverse the array from right to left and insert all elements one by one in an AVL tree. While inserting a new key
in an AVL tree, we first compare the key with root. If key is greater than root, then it is greater than all the nodes
in left subtree of root. So we add the size of left subtree to the count of smaller element for the key being inserted.
 */
BinTreeNode* insert(const BinTreeNode* node, const int32_t key, uint32_t* count) {
  if (!node)
    return new BinTreeNode(key);
  if (key < node->value)
    node->left = insert(node->left, key, count);
  else {
    node->right = insert(node->right, key, count);
    // UPDATE COUNT OF SMALLER ELEMENTS FOR KEY
    *count += size(node->left)+1;
  }

  /* 2. Update height and size of this ancestor node */
  node->height = max(height(node->left), height(node->right))+1;
  node->size   = size(node->left)+size(node->right)+1;
  /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
  uint32_t balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 cases:

  // Left Left Case
  if (balance > 1 && key < node->left->value)
    return rightRotate(node);
  // Right Right Case
  if (balance < -1 && key > node->right->value)
    return leftRotate(node);
  // Left Right Case
  if (balance > 1 && key > node->left->value) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  // Right Left Case
  if (balance < -1 && key < node->right->value) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  /* return the (unchanged) node pointer */
  return node;
}

// The following function updates the countSmaller array to contain count of smaller elements on right side.
void constructLowerArray(int32_t a[], int32_t countSmaller[], const uint32_t n) {
  int i, j;
  struct node *root = NULL;
 
  // initialize all the counts in countSmaller array as 0
  for  (i = 0; i < n; i++)
     countSmaller[i] = 0;
 
  // Starting from rightmost element, insert all elements one by one in
  // an AVL tree and get the count of smaller elements
  for (i = n-1; i >= 0; i--)
  {
     root = insert(root, arr[i], &countSmaller[i]);
  }
}
