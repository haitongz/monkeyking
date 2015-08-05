// A Huffman tree node
struct MinHeapNode {
  char data;  // One of the input characters
  uint32_t freq;  // Frequency of the character
  MinHeapNode* left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap {
  uint32_t size;    // Current size of min heap
  uint32_t capacity;   // capacity of min heap
  MinHeapNode** array;  // Attay of minheap node pointers
};

#if 0
// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 
// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
#endif
// A utility function to swap two min heap nodes
void swapNodes(MinHeapNode** a, MinHeapNode** b) {
  MinHeapNode* t = *a;
  *a = *b;
  *b = t;
}

// The standard minHeapify function.
void heapify_recur(MinHeap* minHeap, const uint32_t index) {
  function<void(const uint32_t)> solve = [&](const uint32_t idx) {
    uint32_t smallest = idx;
    uint32_t left = 2*idx+1;
    uint32_t right = 2*idx+2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;

    if (smallest != idx) {
      swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
      solve(smallest);
    }
  };

  return solve(index);
}

bool onlyOne(const MinHeap* minHeap) {
  return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
MinHeapNode* getMin(const MinHeap* minHeap) {
  MinHeapNode* tmp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size-1];
  --minHeap->size;
  heapify_recur(minHeap, 0);
  return tmp;
}

// A utility function to insert a new node to Min Heap
void insert(MinHeap* minHeap, const MinHeapNode* minHeapNode) {
  ++minHeap->size;
  uint32_t i = minHeap->size-1;

  while (i && minHeapNode->freq < minHeap->array[(i-1)/2]->freq) {
    minHeap->array[i] = minHeap->array[(i-1)/2];
    i = (i-1)/2;
  }

  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap) {
  uint32_t n = minHeap->size-1;

  for (int32_t i = (n-1)/2; i >= 0; --i)
    heapify_recur(minHeap, i);
}

// Utility function to check if this node is leaf
bool isLeaf(MinHeapNode* root) {
  return !(root->left) && !(root->right) ;
}

// Creates a min heap of capacity equal to size and inserts all character of data[] in min heap. Initially size of min heap is equal to capacity
MinHeap* createAndBuildMinHeap(char data[], const uint32_t freq[], const uint32_t size) {
  MinHeap* minHeap = createMinHeap(size);
  for (uint32 i = 0; i < size; ++i)
    minHeap->array[i] = new MinHeapNode(data[i], freq[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);
  return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
 
    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
 
    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);
 
        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert(minHeap, top);
    }

    // Step 4: The remaining node is the root node and the tree is complete.
    return extractMin(minHeap);
}
 
// Prints huffman codes from the root of Huffman Tree.  It uses arr[] to
// store codes
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
 
    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
 
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (isLeaf(root))
    {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
 
// The main function that builds a Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
   //  Construct Huffman Tree
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
 
   // Print Huffman codes using the Huffman tree built above
   int arr[MAX_TREE_HT], top = 0;
   printCodes(root, arr, top);
}
 
// Driver program to test above functions
int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
