#include <iostream>
#include <functional>
#include <stack>
#include <vector>

using namespace std;

ListNode* getNth(ListNode* head, const uint N) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  }

  auto ret = head;
  int count = N;
  while (ret && count >= 0) {
    ret = ret->next;
  }

  if (count >= 0)
    return nullptr;
  else
    return ret;
}

ListNode* nth2End(ListNode* head, const uint N) {
  if (!head) {
#ifdef _DEBUG_
    cerr << "Null head!" << endl;
#endif
    return nullptr;
  }

  uint i = 0;
  auto end = head;
  while (end->next && i < N-1) {
    end = end->next;
    ++i;
  }

  if (i < N-1) {
#ifdef _DEBUG_
    cerr << "There are less than " << N << " elements in the list!" << endl;
#endif
    return nullptr;
  }

  auto nth2End = head;
  while (end->next) {
    end = end->next;
    nth2End = nth2End->next;
  }

  return nth2End;
}

/*
Given a singly linked list, starting from the second node delete all alternate nodes of it.

Given linked list 1->2->3->4->5 then your function should convert it to 1->3->5;
if the given linked list is 1->2->3->4 then convert it to 1->3.
 */
void delAlt_iter(ListNode* head) {
  if (!head)
    return;

  /* Initialize prev and node to be deleted */
  auto prev = head;
  auto curr = head->next;

  while (prev && curr) {
    /* Change next link of previous node */
    prev->next = curr->next;
    delete curr;
    prev = prev->next;
    if (prev)
      curr = prev->next;
  }
}

void delAlt_recur(ListNode* head) {
  function<void(ListNode*)> solve =
    [&](ListNode* curr_head) {
    if (!curr_head)
      return;

    auto nd = curr_head->next;
    if (!nd)
      return;

    curr_head->next = nd->next;
    delete nd;

    /* Recursively call for the new next of head */
    solve(curr_head->next);
  };

  return solve(head);
}

/*
Write a function that takes one list and divides up its nodes to make two smaller lists 'a' and 'b'.
The sublists should be made from alternating elements in the original list.
So if the original list is 0->1->0->1->0->1 then one sublist should be 0->0->0 and the other should be 1->1->1.

Time Complexity: O(n)
 */
void alternatingSplit(ListNode* src, ListNode** aref, ListNode** bref) {
  ListNode adummy(-1), bdummy(-1);
  auto atail = &adummy; /* points to the last node in 'a' */
  auto btail = &bdummy; /* points to the last node in 'b' */
  auto curr = src;
  adummy.next = nullptr;
  bdummy.next = nullptr;

  while (curr) {
    move(&(atail->next), &curr); /* add at 'a' tail */
    atail = atail->next; /* advance the 'a' tail */
    if (curr) {
      move(&(btail->next), &curr);
      btail = btail->next;
    }
  }

  *aref = adummy.next;
  *bref = bdummy.next;
}

/*
Given a Linked List of integers, write a function to modify the linked list such that all even numbers appear
before all the odd numbers in the modified linked list. Also, keep the order of even and odd numbers same.

Input: 17->15->8->12->10->5->4->1->7->6->NULL
Output: 8->12->10->4->6->17->15->5->1->7->NULL
 */
void segregate(ListNode** head_ref) { // O(n)
  auto end = *head_ref;
  ListNode* prev = nullptr;
  auto curr = *head_ref;

  /* Get pointer to the last node */
  while (end->next)
    end = end->next;

  auto new_end = end;

  /* Consider all odd nodes before the first even node and move then after end */
  while (curr->value%2 && curr != end) {
    new_end->next = curr;
    curr = curr->next;
    new_end->next->next = nullptr;
    new_end = new_end->next;
  }

  // 10->8->17->17->15
  /* Do following steps only if there is any even node */
  if (!(curr->value%2)) {
    /* Change the head pointer to point to first even node */
    *head_ref = curr;
    /* now current points to the first even node */
    while (curr != end) {
      if (!(curr->value%2)) {
        prev = curr;
        curr = curr->next;
      } else { /* break the link between prev and current */
        prev->next = curr->next;
        /* Make next of curr as NULL  */
        curr->next = nullptr;
        /* Move curr to end */
        new_end->next = curr;
        /* make curr as new end of list */
        new_end = curr;
        /* Update current pointer to next of the moved node */
        curr = prev->next;
      }
    }
  } else
    prev = curr;

  /* We must have prev set before executing lines following this statement */
  /* If there are more than 1 odd nodes and end of original list is odd then move this node to end to maintain
     same order of odd numbers in modified list */
  if (new_end != end && end->value%2) {
    prev->next = end->next;
    end->next = nullptr;
    new_end->next = end;
  }
}

/*
Detect and remove loop
 */
/* Function to remove loop.
 loop_node --> Pointer to one of the loop nodes
 head -->  Pointer to the start node of the linked list */
void removeLoop(ListNode* loop_node, ListNode* head) {
  auto ptr1 = head;
  auto ptr2 = loop_node;

  /* Set a pointer to the beging of the Linked List and move it one by one to find the first node which is
      part of the Linked List */
  while (true) {
    /* Now start a pointer from loop_node and check if it ever reaches ptr2 */
    ptr2 = loop_node;
    while (ptr2->next != loop_node && ptr2->next != ptr1) {
      ptr2 = ptr2->next;
    }

    /* If ptr2 reahced ptr1 then there is a loop. So break the loop */
    if (ptr2->next == ptr1)
      break;
    else /* If ptr2 did't reach ptr1 then try the next node after ptr1 */
      ptr1 = ptr1->next;
  }

  /* After the end of loop ptr2 is the last node of the loop. So make next of ptr2 as NULL */
  ptr2->next = nullptr;
}

uint detectAndRemoveLoop(ListNode* head) {
  auto slow_p = head, fast_p = head;

  while (slow_p && fast_p && fast_p->next) {
    slow_p = slow_p->next;
    fast_p  = fast_p->next->next;

    /* If slow_p and fast_p meet at some point then there is a loop */
    if (slow_p == fast_p) {
      removeLoop(slow_p, head);

      /* Return 1 to indicate that loop is found */
      return 1;
    }
  }

  /* Return 0 to indeciate that ther is no loop*/
  return 0;
}

/*
Given three linked lists, say a, b and c, find one node from each list such that the sum of the values of the nodes
is equal to a given number.

1) Sort list b in ascending order, and list c in descending order.
2) After the b and c are sorted, one by one pick an element from list a and find the pair by traversing both b and c.

Time complexity: linked lists b and c can be sorted in O(nLogn) time using Merge Sort. Step 2 takes O(n*n) time.
So the overall time complexity is O(nlogn)+O(nlogn)+O(n*n) = O(n*n)
 */
bool isSumSorted(ListNode* ahead, ListNode* bhead,
                 ListNode* chead, const int target) {
  ListNode* a = ahead;

  // Traverse through all nodes of a
  while (a) {
    ListNode* b = bhead;
    ListNode* c = chead;

    // For every node of list a, prick two nodes from lists b abd c
    while (b && c) {
      // If this a triplet with given sum, print it and return true
      int sum = a->value+b->value+c->value;
      if (sum == target) {
        cout << "Triplet Found: " << a->value << " " << b->value << " " << c->value << endl;
        return true;
      } else if (sum < target) // If sum of this triplet is smaller, look for greater values in b
        b = b->next;
      else // If sum is greater, look for smaller values in c
        c = c->next;
    }

    a = a->next; // Move ahead in list a
  }

  cout << "No such triplet!" << endl;
  return false;
}

/*
Given a list, rotate the list to the right by k places, where k is non-negative.
For example, given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.
 */
ListNode* rightRotateByK(ListNode* head, uint k) {
  if (!head || !head->next || !k)
    return head;

  ListNode dummy(-1);
  dummy.next = head;
  const uint n = length_iter(head);
  k %= n; // note: k can become 0
  while (k > 1 && head->next) {
    head = head->next;
    --k;
  }

  auto prev = &dummy;
  while (head->next) {
    head = head->next;
    prev = prev->next;
  }

  auto ret = prev->next;
  prev->next = nullptr;
  head->next = dummy.next;
  return ret;
}

/*
Given two linked lists, insert nodes of second list into first list at alternate positions of first list.

Given first list 5->7->17->13->11 and second list 12->10->2->4->6, the first list should become
5->12->7->10->17->2->13->4->11->6 and second list should become empty.
The nodes of second list should only be inserted when there are positions available.
Given the first list 1->2->3 and second list 4->5->6->7->8, then first list should become 1->4->2->5->3->6 and
second list to 7->8.

Use of extra space is not allowed (Not allowed to create additional nodes), i.e., insertion must be done in-place.
Expected time complexity is O(n) where n is number of nodes in first list.
 */
void mergeAlt(ListNode* p, ListNode** q) {
  auto p_curr = p;
  auto q_curr = *q;

  // While therre are avialable positions in p
  while (p_curr && q_curr) {
    auto p_next = p_curr->next;
    auto q_next = q_curr->next;

    // Make q_curr as next of p_curr
    q_curr->next = p_next; // Change next pointer of q_curr
    p_curr->next = q_curr; // Change next pointer of p_curr

    // Update current pointers for next iteration
    p_curr = p_next;
    q_curr = q_next;
  }

  *q = q_curr;
}

/*
Given two sorted linked lists, construct a linked list that contains maximum sum path from start to end.
The result list may contain nodes from both input lists. When constructing the result list,
we may switch to the other input list only at the point of intersection
(which mean the two node with the same value in the lists). You are allowed to use O(1) extra space.
 */
ListNode* finalMaxSumList(ListNode* a, ListNode* b) {
  ListNode* ret = nullptr;
  auto prev1 = a, curr1 = a;
  auto prev2 = b, curr2 = b;

  // Till either of the current pointers is not NULL execute the loop
  while (curr1 || curr2) {
    // Keeping 2 local variables at the start of every loop run to keep track
    // of the sum between prev and curr pointer elements.
    int sum1 = 0, sum2 = 0;

    // Calculating sum by traversing the nodes of linked list as the merging of two linked list.
    // The loop stops at a common node
    while (curr1 && curr2 && curr1->value != curr2->value) {
      if (curr1->value < curr2->value) {
        sum1 += curr1->value;
        curr1 = curr1->next;
      } else { // (curr2->data < curr1->data)
        sum2 += curr2->value;
        curr2 = curr2->next;
      }
    }

    // If either of current pointers becomes NULL carry on the sum calculation for other one.
    if (!curr1) {
      while (curr2) {
        sum2 += curr2->value;
        curr2 = curr2->next;
      }
    }
    if (!curr2) {
      while (curr1) {
        sum1 += curr1->value;
        curr1 = curr1->next;
      }
    }

    if (prev1 == a && prev2 == b)
      ret = (sum1 > sum2) ? prev1 : prev2;
    else { // If pre1 and pre2 don't contain the head pointers of lists adjust the next pointers of previous pointers.
      if (sum1 > sum2)
        prev2->next = prev1->next;
      else
        prev1->next = prev2->next;
    }

    // Adjusting previous pointers
    prev1 = curr1;
    prev2 = curr2;

    // If curr1 is not NULL move to the next.
    if (curr1)
      curr1 = curr1->next;
    // If curr2 is not NULL move to the next.
    if (curr2)
      curr2 = curr2->next;
  }

 /* while (ret) {
        cout << result->data << " ";
        result = result->next;
    } */
  return ret;
}

/*
Given a singly linked list L: L0->L1...Ln-1->Ln, reorder it to: L0->Ln->L1->Ln-1...L2->Ln-2
You must do this in-place without altering the nodes' values.

Given {1,2,3,4}, reorder it to {1,4,2,3}.
 */
void reverseList(ListNode* prev) {
  ListNode* tail = prev->next;

  while (tail->next) {
    ListNode* t = tail->next;
    tail->next = t->next;
    t->next = prev->next;
    prev->next = t;
  }
}

void intertwinedList(ListNode* h1, ListNode* h2) {
  while (h2) {
    ListNode* t = h2;
    h2 = h2->next;
    t->next = h1->next;
    h1->next = t;
    h1 = t->next;
  }
}

void reorderList(ListNode* head) {
  if (!head || !head->next || !head->next->next)
    return;

  ListNode* prev = head->next;
  ListNode* tail = prev->next;
  while (tail && tail->next) {
    prev = prev->next;
    tail = tail->next->next;
  }
  reverseList(prev);

  tail = prev->next;
  prev->next = NULL;
  intertwinedList(head, tail);
}

int main(int argc, char** argv) {
  ListNode fir(1);
  ListNode sec(2);
  ListNode thi(3);
  ListNode fou(4);
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  ListNode* head = &fir;
  ListNode* p = reverse_recur(head);
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  fir.value = 1;
  sec.value = 2;
  thi.value = -3;
  fou.value = 4;
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = nullptr;

  ListNode* curr = mergeSort_recur(&fir);
  while (curr) {
    cout << curr->value << " ";
    curr = curr->next;
  }
  cout << endl;

  ListNode h1(2), f1(4), s1(3), h2(5), f2(6), s2(4);
  h1.next = &f1;
  f1.next = &s1;
  h2.next = &f2;
  f2.next = &s2;

  const ListNode* l1 = &h1;
  const ListNode* l2 = &h2;
  const ListNode* res = addTwoNums(&h1, &h2);
  while (res) {
    cout << res->value << " -> ";
    res = res->next;
  }
  cout << endl;

  const ListNode* i = intersection(const_cast<const ListNode*>(&h1),
                                   const_cast<const ListNode*>(&h2));
  cout << "Two lists ";
  if (i) {
    cout << "intersect at " << i->value;
  } else {
    cout <<"don't intersect.";
  }
  cout << endl;

  fir.value = 1;
  sec.value = 2;
  thi.value = 3;
  fou.value = 4;
  fir.next = &sec;
  sec.next = &thi;
  thi.next = &fou;
  fou.next = NULL;

  reorderList(&fir);

  p = &fir;
  while (p) {
    cout << p->value << " ";
    p = p->next;
  }
  cout << endl;

  ListNode a1(1), a2(2), c1(3), c2(4), c3(5);
  a1.next = &a2;
  a2.next = &c1;
  c1.next = &c2;
  c2.next = &c3;
  c3.next = nullptr;
  ListNode b1(6), b2(7), b3(8);
  b1.next = &b2;
  b2.next = &b3;
  b3.next = &c1;
  fou.next = nullptr;

  i = intersection(const_cast<const ListNode*>(&a1),
                   const_cast<const ListNode*>(&b1));
  cout << "Two lists ";
  if (i) {
    cout << "intersect at " << i->value;
  } else {
    cout <<"don't intersect.";
  }
  cout << endl;

  cout << "Union of two lists are: " << endl;
  i = unionList(&a1, &b1);
  while (i) {
    cout << i->value << " ";
    i = i->next;
  }
  cout << endl;

  return 0;
}
