#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <boost/shared_ptr.hpp>

#define MAGIC_NUMBER 0xBABEEBAB

template< typename T >
struct NodeT
{
   struct NodeT* next;
   uint64_t magic;
   T value;
};

// typedef NodeT<uint32_t> Node;

template< typename T >
void
swap( T* a, T* b )
{
   if( a != b ) { // compare a and b first to avoid alignment problems
      *a ^= *b;
      *b ^= *a;
      *a ^= *b;
   }
}

/**
 * Given the starting node of a link list, return the Nth element from
 * end of list.
 */
template< typename T >
NodeT<T>*
getNth2End( NodeT<T>* head, uint32_t N, bool debug )
{
   if( !head ) {
      if( debug )
         std::cout << "List is empty!" << std::endl;
      return NULL;
   }

   uint32_t index = 0;
   NodeT<T>* end = head;
   NodeT<T>* nth2End = head;

   /*
    * If magic number doesn't match, memory must be corrupted.
    */
   if( end->magic != MAGIC_NUMBER ) {
      std::cout << "Corrupted list!" << std::endl;
      return NULL;
   }

   /*
    * Progress the end_node to the nth node from the head first.
    */

   while( end->next && index < N ) {
      end = end->next;
      if( end->magic != MAGIC_NUMBER ) {
         std::cout << "Corrupted list!" << std::endl;
         return NULL;
      }
      ++index;
   }

   /*
    * Return if less than n element in the list.
    */
   if( index < N ) {
      if( debug ) {
         printf("\nThere are less than %d elements in the list\n", N);
      }

      return NULL;
   }

   /*
    * Now we know there are >= n elements in the list. Progress end_node
    * and nth to end together till the end of the list, so their
    * distance is always N.
    */

   while( end->next ) {
      end = end->next;
      if( end->magic != MAGIC_NUMBER ) {
         std::cout << "Corrupted list!" << std::endl;
         return NULL;
      }
      nth2End = nth2End->next;
   }

   return nth2End;
}

#if 0
/*
 * Given the starting node of a link list, return the Nth element from end of list.
 */
node*
get_Nth_to_end_2( node* head, int32_t n, bool debug )
{
   /*
    * Nothing in the list.
    */
   if( !head ) {
      if( debug ) {
         printf( "\nList is empty\n" );
      }
      return NULL;
   }

   uint32_t index = 0;
   node* node[n];

   /*
    * Savethe last n elements in an array.
    */

   while( head ) {
      /*
       * If magic number doesn't match, memory must be corrupted.
       */
      if( head->magic != MAGIC_NUMBER ) {
         printf( "\nCorrupted list\n" );
         return NULL;
      }

      node[index%n] = head;
      head = head->next;
      ++index;
   }

   /*
    * Return if less than n element in the list.
    */

   if( index < n ) {
      if( debug ) {
         printf( "\nLess than 5 elements in the list\n" );
      }
      return NULL;
   }

   return node[index%n];
}
#endif

template< typename T >
void
iterate( NodeT<T>* head, bool debug )
{
   if( !head ) {
      if( debug )
         std::cout << "Null head found!" << std::endl;
      return;
   }

   uint32_t i = 1;
   NodeT<T>* curr = head;
   while( curr ) {
      printf( "The value of node %d is: %d\n", i, curr->value );
      ++i;
      curr = curr->next;
   }
}

/**
 * Given a reference to the head of a list and an int, push
 * a new node on the front of the list, and finally change the
 * head to point to the new node
 */
template< typename T >
void
push( NodeT<T>** head, const T& newValue )
{
   NodeT<T>* newNode = new NodeT<T>;
   newNode->value = newValue;
   newNode->next = *head;
   newNode->magic = MAGIC_NUMBER;
   *head = newNode;
}

/**
 * Extract the data the head node, delete the node, advance the head
 * pointer to point at the next node in line
 */
template< typename T >
T
pop( NodeT<T>** head )
{
   uint32_t result;
   NodeT<T>* tmp = *head;

   assert( tmp );
   result = tmp->value;
   *head = tmp->next;
   delete tmp;
   return result;
}

#if 0
node*
getNth( node* head, uint32_t n )
{
   if (!n)
      return 0;

   node* current = head;
   uint32_t count = 0;

   while( current ) {
      if (count == n) {
         return current;
      }
      ++count;
      current = current->next;
   }

   return 0;                                      // less then N elements in list
}
#endif

/*this is an O(n2) algorithm, any better ones? */
template< typename T >
void
sortList( NodeT<T>* head, bool debug )
{
   if( !head ) {
      if( debug )
         printf( "Null head found!\n" );
      return;
   }

   NodeT<T>* first = head;
   NodeT<T>* second = NULL;

   while( first ) {
      second = first->next;
      while( second ) {
         if( first->value > second->value ) { //sort in ascending
            swap( &(first->value), &(second->value) );
         }

         second = second->next;
      }

      first = first->next;
   }
}

// recursive sorting linked list
template< typename T >
NodeT<T>*
insert( NodeT<T>* head, NodeT<T>* node )
{
   NodeT<T>** p = NULL;
   for( p = &head; *p != NULL && (*p)->value > node->value; p = &(*p)->next );

   node->next = *p;
   *p = node;
   return head;
}

template< typename T >
NodeT<T>*
sortList2( NodeT<T>* head )
{
   return !head ? NULL : insert( sortList2( head->next ), head );
}

#if 0
node * reverse(node *);

node * recursive_reverse(node * n)
{
   node * next = n->next;
   if (!next) {                                   // if the list has only one node we don't need to reverse it
      return n;
   }

   if (!next) {                                   // if nextNode is the last node we terminate the recursion
      next->next = n;                             // reverse the link
      return next;                                // return the ptr to the last node
      // this will become the new head pointer
   }

   node * head = reverse(n->next);                //recursively call Reverse
   next->next = n;                                // reverse the link
   return head;
}

// Takes a pointer to the head node of a singly linked list
// and returns the new head pointer for the reversed list
node * reverse(node * head)
{
   node * newHead = recursive_reverse(head);
   head->next = NULL;                             // since the first node is the last node now
   // we need to set it's next pointer to NULL
   return newHead;
}

//Takes a pointer to the head of a linked list
//Returns the pointer to the new head (old tail) node
node * iterative_reverse(node * head)
{
   node * prev = NULL;                            //pointer to the previous node
   node * next = NULL;                            //pointer to the next node
   node * curr = head;                            //pointer to the current node

   while (curr) {
      next = curr->next;                          //save the pointer to the next node
      //otherwise we will lose it as we
      // overwrite it in the next step
      curr->next = prev;                          //reverse the link

      prev = curr;                                //set the current node as the previous node
      //for the next iteration

      curr = next;                                //advance the current pointer
   }

   return prev;
}
#endif

/**
 * Reverse the linked list, non-recursive
 */
template< typename T >
NodeT<T>*
reverseList( NodeT<T>* head )
{
   if( !head ) {
#ifdef _DEBUG_
         printf( "Null head!\n" );
#endif
      return head;
   }

   NodeT<T>* curr = head;
   NodeT<T>* prev = NULL;

   while( curr ) {
      NodeT<T>* next = curr->next; // save the next ptr in next
      curr->next = prev;           // change next to privous
      prev = curr;                 // set last node as previous node
      curr = next;                 // set next node as last node
   }

   return prev;
}

/**
 * reverse the linked list, recursive
 */
template< typename T >
NodeT<T>*
reverseList2( NodeT<T>* head )
{
   if( head && head->next ) {
      NodeT<T>* tmp = reverseList2( head->next );
      head->next->next = head;
      head->next = NULL;
      return tmp;
   }
   return head;
}

template< typename T >
void
insertNth( NodeT<T>** head, uint32_t index, T data )
{
   if( !index ) {
      push( head, data );
   } else {
      NodeT<T>* current = *head;

      for( uint32_t i = 0; i < index-1; ++i ) {
         assert( current ); // fails if index is too big
         current = current->next;
      }
      assert( current );    //check one last time
      push( &(current->next), data );
   }
}

template< typename T >
void
sortedInsert( NodeT<T>** head, NodeT<T>* newNode, bool debug )
{
   if( !*head ) {
      if( debug )
         printf( "Null head found!\n" );
      return;
   }

   if( !newNode ) {
      if( debug )
         printf( "Cannot insert null node!\n" );
      return;
   }

   if( (*head)->value < newNode->value ) { //add new node as head
      newNode->next = *head;
      *head = newNode;
   } else {
      NodeT<T>* current = *head;

      while( current->next && newNode->value < current->value ) {
         current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
   }
}

/**
 * Append a list to the end of another, handle empty list case
 */
template< typename T >
void
appendList( NodeT<T>** aList, NodeT<T>** bList )
{
   if( !*aList ) {
      *aList = *bList;
   } else {
      NodeT<T>* current = *aList;
      while( current->next )
         current = current->next;
      current->next = *bList;
   }

   *bList = NULL; // Null the original b
}

/**
 * Split list, use fast/slow pinter strategy
 */
template< typename T >
void
frontBackSplit( NodeT<T>* source, NodeT<T>** front, NodeT<T>** back )
{
   if( !source || !source->next ) { //length < 2
      *front = source;
      *back  = NULL;
   } else {
      NodeT<T>* slow = source;
      NodeT<T>* fast = source->next;

      //advance fast two nodes, and advance slow one node
      while( fast ) {
         fast = fast->next;
         if( fast ) {
            slow = slow->next;
            fast = fast->next;
         }
      }

      //slow is before the midpoint in the list, so split it in two
      *front = source;
      *back  = slow->next;
      slow->next = NULL;
   }
}

/**
 * When the list is sorted, remove duplicates
 */
template< typename T >
void
removeDuplicates( NodeT<T>* head )
{
   if( !head )
      return;

   NodeT<T>* current = head;
   while( current->next ) {
      if( current->value == current->next->value ) {
         NodeT<T>* nextNext = current->next->next;
         free( current->next );
         current->next = nextNext;
      } else {
         current = current->next;
      }
   }
}

/**
 * Move node, short but complex
 */
template< typename T >
void
moveNode( NodeT<T>** destRef, NodeT<T>** sourceRef )
{
   NodeT<T>* newNode = *sourceRef; //the front source node
   assert( newNode );

   *sourceRef = newNode->next; //advance the source pointer

   newNode->next = *destRef;   //link the old dest off the new node
   *destRef = newNode;         //move dest to point to the new node
}

/**
 * ShuffleMerge -- Recursive approach
 */
template< typename T >
NodeT<T>*
shuffleMerge( NodeT<T>* a, NodeT<T>* b )
{
   if( !a ) //see if either list is empty
      return b;
   if( !b )
      return a;

   NodeT<T>* result = NULL;
   NodeT<T>* recur = NULL;
   recur = shuffleMerge( a->next, b->next );

   result = a;
   a->next = b;
   b->next = recur;
   return result;
}

template< typename T >
int
findListCycle( NodeT<T>* head, bool debug )
{
   if( !head ) {
      if( debug ) {
         printf( "Null head found!\n" );
      }
   }

   NodeT<T>* first = head;
   NodeT<T>* second = head;

   while( first->next ) {
      first = first->next;
      second = second->next->next;
      if( first == second )
         return 1;
   }
   return 0;
}

/**
 * Delete whole list and set the head pointer to NULL
 */
template< typename T >
void
deleteWholeList( NodeT<T>** headRef )
{
   if( !(*headRef) ) {
      printf("Empty list!\n");
      return;
   }

   NodeT<T>* curr = (*headRef);
   NodeT<T>* next;

   while( curr ) {
      next = curr->next;
      delete curr;
      curr = next;
   }
   *headRef = NULL;
}

/**
 * Delete all nodes with value n, return number of deleted nodes
 */
template< typename T >
uint32_t
deleteFromList( NodeT<T>** headRef, NodeT<T>* prev, const T& v, bool debug )
{
   static uint32_t count = 0;
   NodeT<T>* curr = *headRef;

   if( !headRef ) {
      if( debug )
         printf( "Invalid head of linked list!\n" );
      return 0;
   } else if( !curr ) {
      return count;
   } else {
      if( curr->value == v ) {
         NodeT<T>* todel = curr;
         if( !prev ) { // head
            curr = *headRef = curr->next;
         } else {
            curr = curr->next;
            prev->next = curr;
         }
         delete todel;
         ++count;
      } else {
         prev = curr;
         curr = curr->next;
      }
   }

   return deleteFromList( &curr, prev, v, debug );
}

// non-recursive version
template< typename T >
uint32_t
deleteFromList2( NodeT<T>** headRef, const T& v, bool debug )
{
   uint32_t count = 0;
   if( !(*headRef) ) {
      if( debug )
         printf("Null head found!\n");
   }

   NodeT<T>* temp = NULL;
   while( (*headRef)->value == v ) {
      temp = *headRef;
      *headRef = temp->next;
      delete temp;
      ++count;
      if( !(*headRef) ) //single node list case
         return count;
   }

   NodeT<T>* prev = *headRef;
   NodeT<T>* curr = (*headRef)->next;
   while( curr ) {
      if( curr->value == v ) {
         prev->next = curr->next;
         delete curr;
         ++count;
         curr = prev->next;
      } else {
         prev = curr;
         curr = curr->next;
      }
   }
   return count;
}

// head and tail point to the first and last node of the linked list
// delete node elem
template< typename T >
uint32_t
deleteNode( NodeT<T>** head, NodeT<T>** tail, NodeT<T>* elem )
{
   if( !elem )
      return 0;

   NodeT<T>* curr = *head;
   if( elem == *head ) {
      *head = elem->next;
      delete elem;

      if( !*head )
	 *tail = NULL; //1 element list case
   }

   while( curr )
   {
      if( curr->next == elem ) {
         curr->next = elem->next;
         delete elem;
         if( !curr->next ) {
	   *tail = curr;
	   return 1;
	 }
      }
      curr = curr->next;
   }

   return 0;
}

#include "TickBuffer.H"

class DummyTick : public hfe::TickBuffer
{
   public:
      DummyTick( unsigned long key )
	 : _key( key )
      {
      }

      //! ordering key of current item in buffer
      virtual unsigned long getKey()
      {
	 return _key;
      }

      //! process current item in buffer and return true
      //! if item is the last in the buffer (for this date)
      virtual bool processNext()
      {
	 return true;
      }

   private:
      unsigned long _key;
};

int main ()
{
   NodeT<uint32_t>* head = NULL;
   NodeT<uint32_t>* fifth2End = NULL;

   //seed random number generator
   srand( getpid() );

   for( uint32_t i = 0; i < 10; ++i ) {
      uint32_t newVal = rand();
      push( &head, newVal );
   }

   printf("Iterating through list!\n");
   iterate( head, true );
   fifth2End = getNth2End( head, 5, true );
   if( fifth2End )
      printf("TEST: 5th from end is %d\n", fifth2End->value);

   printf("\nReversing list!\n");
   head = reverseList( head );
   // head = iterative_reverse(head);

   iterate( head, 1 );

   printf("\nReversing the list back!\n");
   head = reverseList2( head );
   // head = recursive_reverse(head);
   iterate( head, 1 );
   fifth2End = getNth2End( head, 5, true );
   if( fifth2End )
      printf("TEST: 5th from end is %d\n", fifth2End->value);

   printf("\nSorting the list ascendingly!\n");
   sortList( head, true );
   iterate( head, 1 );

   printf("\nSorting the list descendingly!\n");
   head = sortList2( head );
   iterate( head, 1 );

   printf("\nInserting a new node into sorted list!\n");
   NodeT<uint32_t>* n = new NodeT<uint32_t>;
   n->value = 15;
   n->magic = MAGIC_NUMBER;
   sortedInsert( &head, n, true );
   iterate( head, true );

   // printf("The head is at:%ul\n", head);
   fifth2End = getNth2End( head, 5, true );
   if( fifth2End )
      printf("TEST: 5th from end is %d\n", fifth2End->value);

   //	printf("The head is at:%ul\n", head);
   printf("\nDeleting nodes with value 15\n");
   uint32_t num = deleteFromList2( &head, (uint32_t)15, true );
   printf("%d nodes were deleted!\n", num);
   printf("Review the list after deletion!\n");
   iterate( head, true );

   boost::shared_ptr<DummyTick> prev;
   boost::shared_ptr<DummyTick> head1;
   for( uint32_t i = 0; i < 100; ++i ) {
      boost::shared_ptr<DummyTick> next( new DummyTick( (unsigned long)rand() ) );
      if( !prev ) {
	 head1 = next;
      } else {
	 prev->setNext( &(*next) );
      }

      next->setNext( NULL );
      next->setPrev( prev.get() );
      prev = next;
   }

   /*
   boost::shared_ptr<DummyTick> head2;
   for( uint32_t i = 0; i < 100; ++i ) {
      boost::shared_ptr<DummyTick> node( new DummyTick( (unsigned long)rand() ) );
      if( !prev ) {
	 head2 = node;
      }
      node->setNext( NULL );
      prev->setNext( node.get() );
      node->setPrev( prev.get() );
      prev = node;
   }
*/
   uint64_t currTime;
   hfe::TickBuffer* tick = dynamic_cast<hfe::TickBuffer*>(&(*head1));
   hfe::TickBuffer::merge( tick, &currTime );
   /*
      if (findcycle(head, 1))
      printf("Cycle in list found!\n");
      else
      printf("No cycles in linked list!\n");
      */
   return 1;
}
