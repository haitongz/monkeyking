/*
Given a linked list of co-ordinates where adjacent points either form a vertical line or a horizontal line.
Delete points from the linked list which are in the middle of a horizontal or vertical line.

Examples:

Input:  (0,10)->(1,10)->(5,10)->(7,10)
                                  |
                                (7,5)->(20,5)->(40,5)
Output: Linked List should be changed to following
        (0,10)->(7,10)
                  |
                (7,5)->(40,5) 
The given linked list represents a horizontal line from (0,10) 
to (7, 10) followed by a vertical line from (7, 10) to (7, 5), 
followed by a horizontal line from (7, 5) to (40, 5).

Input:     (2,3)->(4,3)->(6,3)->(10,3)->(12,3)
Output: Linked List should be changed to following
    (2,3)->(12,3) 
There is only one vertical line, so all middle points are removed.
Source: Microsoft Interview Experience

We strongly recommend to minimize the browser and try this yourself first.

The idea is to keep track of current node, next node and next-next node.
While the next node is same as next-next node, keep deleting the next node.
In this complete procedure we need to keep an eye on shifting of pointers and checking for NULL values.
 */
// remove intermediate points in a linked list that represents horizontal and vertical line segments
#include <stdio.h>
#include <stdlib.h>
 
// Node has 3 fields including x, y coordinates and a pointer to next node
struct node
{
    int x, y;
    struct node *next;
};
 
/* Function to insert a node at the beginning */
void push(struct node ** head_ref, int x,int y)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->x  = x;
    new_node->y  = y;
    new_node->next = (*head_ref);
    (*head_ref)  = new_node;
}
 
/* Utility function to print a singly linked list */
void printList(struct node *head)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("(%d,%d)-> ", temp->x,temp->y);
        temp = temp->next;
    }
    printf("\n");
 
}
 
// Utility function to remove Next from linked list and link nodes
// after it to head
void deleteNode(struct node *head, struct node *Next)
{
    head->next = Next->next;
    Next->next = NULL;
    free(Next);
}
 
// This function deletes middle nodes in a sequence of horizontal and
// vertical line segments represented by linked list.
struct node* deleteMiddle(struct node *head)
{
    // If only one node or no node...Return back
    if (head==NULL || head->next ==NULL || head->next->next==NULL)
        return head;
 
    struct node* Next = head->next;
    struct node *NextNext = Next->next ;
 
    // Check if this is a vertical line or horizontal line
    if (head->x == Next->x)
    {
        // Find middle nodes with same x value, and delete them
        while (NextNext !=NULL && Next->x==NextNext->x)
        {
            deleteNode(head, Next);
 
            // Update Next and NextNext for next iteration
            Next = NextNext;
            NextNext = NextNext->next;
        }
    }
    else if (head->y==Next->y) // If horizontal line
    {
        // Find middle nodes with same y value, and delete them
        while (NextNext !=NULL && Next->y==NextNext->y)
        {
            deleteNode(head, Next);
 
            // Update Next and NextNext for next iteration
            Next = NextNext;
            NextNext = NextNext->next;
        }
    }
    else  // Adjacent points must have either same x or same y
    {
        puts("Given linked list is not valid");
        return NULL;
    }
 
    // Recur for next segment
    deleteMiddle(head->next);
 
    return head;
}
 
// Driver program to tsst above functions
int main()
{
    struct node *head = NULL;
 
    push(&head, 40,5);
    push(&head, 20,5);
    push(&head, 10,5);
    push(&head, 10,8);
    push(&head, 10,10);
    push(&head, 3,10);
    push(&head, 1,10);
    push(&head, 0,10);
    printf("Given Linked List: \n");
    printList(head);
 
    if (deleteMiddle(head) != NULL);
    {
        printf("Modified Linked List: \n");
        printList(head);
    }
    return 0;
}
