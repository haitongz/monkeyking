#define _REENTRANT                                /* This is required for reentrant code */

#include <stdio.h>
#include "MyThread.hpp"

int     ret[5];

void * thread_func(void * arg)                    /* One of the threads demonstrated. Computes square of the integer argument */
{
   int in;

   in = *(int*)arg;

   printf("Inside thread.Thread received argument: %d. Computing square and ",in );
   ret[in] = in * in;
   printf("returning: %d\n", ret[in] );

   return (void*) &ret[in];

}

void * thread_func2(void * arg)                   /* The second thread demonstrated. */
{
   printf("Iam another thread. I was yielded to by the main thread.\n");
   return NULL;
}

void * thread_func3(void * arg)                   /* One more demonstration thread */
{

   printf("\nIam the last created thread\n");
   return NULL;
}

int main()
{
   MyThread      thr[6];                          /* Demonstrating with 6 threads */
   int             arg[6]= { 0,1,2,3,4,5 },
   *ret_status[6],i ;

   printf("\nTesting mythread.a for functionality...\n");
   printf("Testing mythread_create... attempting to create 4 threads...\n");
   for (i = 0; i < 4; ++i) {
      if (MyThread::mythread_create(&thr[i], NULL, thread_func, &arg[i]) < 0) {
         perror("THREAD CREATION FAILED:");
         exit(1);
      }
   }
   printf("(:-) MYTHREAD_CREATE PASS. 4 threads created successfully...\n");

   printf("Testing mythread_join...attempting to join newly created threads with main thread...\n");

   for (i = 0; i < 4; ++i) {
      if (MyThread::mythread_join(thr[i],(void**)&ret_status[i]) < 0) {
         perror("THREAD JOIN FAILED:");
         exit(1);
      }
   }

   printf("\n(:-) MYTHREAD_JOIN PASS. Joined successfully with 4 threads...\n");
   printf("\n\nReturn status as returned by the terminated threads,\n");

   for (i = 0; i < 4; ++i)
      printf("Return status of thread: %d, = %d\n",thr[i].getThreadId(), *ret_status[i] );

   printf("\nTesting thread creation again with new thread function....\n");

   if (MyThread::mythread_create(&thr[4],NULL,thread_func2,NULL) < 0) {
      perror("THREAD CREATION FAILED");
      exit(1);
   }
   printf("(:-) MYTHREAD_CREATE PASS....\n");

   printf("\nTesting mythread_yield. Attempting to yield to newly created thread...\n");
   MyThread::mythread_yield();
   printf("(:-) MYTHREAD_YIELD PASS. Execution proceeding after yielding...\n");

   printf("\nTesting mythread_create again...\n");

   if (MyThread::mythread_create(&thr[5],NULL,thread_func3,NULL) < 0) {
      perror("THREAD CREATION FAILED");
      exit(1);
   }

   printf("(:-) MYTHREAD_CREATE PASS...\n");
   MyThread::mythread_yield();
   printf("\n\n(:-) ALL TESTS PASSED. Thread library functioning fine....End of tests.\n");
}
