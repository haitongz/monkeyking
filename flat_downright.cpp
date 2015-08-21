/*
Given a linked list where every node represents a linked list and contains two pointers of its type:
(i) Pointer to next node in the main list (we call it 'right' pointer in below code)
(ii) Pointer to a linked list where this node is head (we call it 'down' pointer in below code).
All linked lists are sorted. See the following example

       5 -> 10 -> 19 -> 28
       |    |     |     |
       V    V     V     V
       7    20    22    35
       |          |     |
       V          V     V
       8          50    40
       |                |
       V                V
       30               45
Write a function flatten() to flatten the lists into a single linked list. The flattened linked list should also be sorted. For example, for the above input list, output list should be 5->7->8->10->19->20->22->28->30->35->40->45->50.
 */
struct ListNode2 {
  ListNode2* right;
  ListNode2* down;
  int32_t value;
};

ListNode2* merge(ListNode2* a, ListNode2* b) {
  function<ListNode2*(ListNode2*,ListNode2)> solve =
    [&](ListNode2* curr_head1, ListNode2* curr_head2) {
    // If first list is empty, the second list is result
    if (!curr_head1)
      return curr_head2;
    // If second list is empty, the second list is result
    if (!curr_head2)
      return curr_head1;

    // Compare the data members of head nodes of both lists and put the smaller one in result
    ListNode2* ret;
    if (curr_head1->value < curr_head2->value) {
      ret = a;
      ret->down = solve(curr_head1->down, curr_head2);
    } else {
      ret = curr_head2;
      ret->down = solve(curr_head1, curr_head2->down);
    }

    return ret;
  };

  return solve(a, b);
}

ListNode2* flatten(ListNode2* head) {
  function<ListNode2*(ListNode2*)> solve =
    [&](ListNode2* curr_head) {
    if (!curr_head || !curr_head->right)
      return curr_head;

    // Merge this list with the list on right side
    return merge(curr_head, flatten(curr_head->right));
  };

  return solve(head);
}
