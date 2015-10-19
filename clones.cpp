#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors. Nodes are labeled uniquely.

We use # as a separator for each node, and, as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/
*/
template <typename T>
struct UndirecteGraphNodeT {
  UndirecteGraphNodeT(const T& x) : label(x) {
  }
  T label;
  vector<UndirecteGraphNodeT*> neighbors;
};

template <typename T>
UndirecteGraphNodeT<T>* dfs(UndirecteGraphNodeT<T>* node, map<T, UndirecteGraphNodeT<T>*>& recs) {
  if (!node)
    return node;
  if (recs.count(node->label) > 0)
    return recs[node->label];

  UndirecteGraphNodeT<T>* res = new UndirecteGraphNodeT<T>(node->label);
  recs[node->label] = res; // nodes are labeled uniquely

  for (uint32_t i = 0; i < node->neighbors.size(); ++i) {
    (res->neighbors).push_back(dfs((node->neighbors[i]), recs));
  }

  return res;
}

template <typename T>
UndirecteGraphNodeT<T>* clone(UndirecteGraphNodeT<T>* root) {
  map<T, UndirecteGraphNodeT<T>*> recs;
  return dfs(root, recs);
}

/*
A linked list is given such that each node contains an additional random pointer which could point to
any node in the list or null. Return a deep copy of the list.
*/
struct ListNodeWithRandom {
  ListNodeWithRandom(const int32_t v)
      : value(v), next(NULL), random(NULL) {
  }
  int32_t value;
  ListNodeWithRandom* next;
  ListNodeWithRandom* random;
};
/*
ListNodeWithRandom* dfs(ListNodeWithRandom* h, map<ListNodeWithRandom*, ListNodeWithRandom*>& mp_ir) {
  if (!h)
    return NULL;
  if (mp_ir.count(h))
    return mp_ir[h];

  ListNodeWithRandom* nh = new ListNodeWithRandom(h->value);
  mp_ir[h] = nh;
  nh->next = dfs(h->next, mp_ir); // this shall insert all nodes to map
  if (!h->random)
    nh->random = NULL;
  else
    nh->random = mp_ir[h->random];

  return nh;
}

ListNodeWithRandom* deepcopy(ListNodeWithRandom* head) {
  map<ListNodeWithRandom*, ListNodeWithRandom*> mp_ir;
  return dfs(head, mp_ir);
}
*/
ListNodeWithRandom* copyRandomList(ListNodeWithRandom* head) {
  ListNodeWithRandom res(0);
  auto newpre = &res;

  unordered_map<ListNodeWithRandom*, ListNodeWithRandom*> record;
  auto dfs = [&](ListNodeWithRandom* pt) -> ListNodeWithRandom* {
    if (!pt)
      return nullptr;
    auto ex = record.find(pt);
    if (ex != record.end())
      return ex->second;

    auto newpt = new ListNodeWithRandom(pt->value);
    record[pt] = newpt;
    return newpt;
  };

  auto curr = head;
  while (curr) {
    newpre->next = dfs(curr);
    newpre->next->random = dfs(curr->random);
    curr = curr->next;
    newpre = newpre->next;
  }

  return res.next;
}

/*
Follow up:
Can you solve this question without using extra memory?

Step 1. Copy and insert the node after every node in the original link list;
Step 2. Build up the random connections among the new nodes.
Step 3. Divide the two link list and make the new one independent.
*/
ListNodeWithRandom* copyRandomListInplace(ListNodeWithRandom* head) {
  ListNodeWithRandom* curr = head;

  while (curr) {
    ListNodeWithRandom* copy = new ListNodeWithRandom(curr->value);
    copy->next = node->next;
    copy->random = nullptr;
    curr->next = copy;
    curr = copy->next;
  }

  // Copy the random link in the original linklist;
  curr = head;
  while (curr){
    ListNodeWithRandom* copy = curr->next;
    if (curr->random)
      copy->random = curr->random->next;
    curr = copy->next;
  }

  // Divide the linklist to two linklists
  ListNodeWithRandom dummy(0);
  ListNodeWithRandom* prev = &dummy;
  curr = head;

  while (curr) {
    prev->next = curr->next;
    prev = prev->next;
    curr->next = prev->next;
    curr = curr->next;
  }

  return dummy.next;
}

int main(int argc, char** argv) {
  UndirecteGraphNodeT<int32_t> zero(0);
  UndirecteGraphNodeT<int32_t> one(1);
  UndirecteGraphNodeT<int32_t> two(2);

  zero.neighbors.push_back(&one);
  zero.neighbors.push_back(&two);
  one.neighbors.push_back(&two);
  two.neighbors.push_back(&two);

  UndirecteGraphNodeT<int32_t>* res = clone(&one);
  return 0;
}
