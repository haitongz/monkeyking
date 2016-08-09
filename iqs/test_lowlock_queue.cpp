#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <iostream>
#include <sstream>

#include "lowlock_queue.h"

typedef void* (*thr_routine)( void* arg );
typedef bearcat::lowlock_queue<int> queue_type;

pthread_mutex_t output_mutex;

queue_type g_queue;

pid_t gettid()
{
   return syscall( __NR_gettid );
}

void*
produce_routine( void* arg )
{
   int i;
   int proc_num = (int)(long)arg;
   cpu_set_t set;

   CPU_ZERO( &set );
   CPU_SET( proc_num, &set );

   //   pid_t tid = (pid_t) syscall( SYS_gettid );
   pid_t tid = gettid();

   if( sched_setaffinity( tid, sizeof(cpu_set_t), &set ) ) {
      perror( "sched_setaffinity" );
      return nullptr;
   }

   for( i = 5000/*queue_type::INC_TO*/*proc_num; i < 5000/*queue_type::INC_TO*/*(proc_num+1); ++i ) {
      // __sync_fetch_and_add( &global_int, 1 ); // one of atomic builtins since GCC 4.1.2 ( http://gcc.gnu.org/onlinedocs/gcc-4.5.0/gcc/Atomic-Builtins.html )
      g_queue.produce( i );

      PTHREAD_CALL( pthread_mutex_lock( &output_mutex ) );
      std::cout << "thread " << tid << ": produced " << i << std::endl;
      PTHREAD_CALL( pthread_mutex_unlock( &output_mutex ) );
   }

   PTHREAD_CALL( pthread_mutex_lock( &output_mutex ) );
   printf( "thread %d on processor %d is done\n", tid, proc_num );
   PTHREAD_CALL( pthread_mutex_unlock( &output_mutex ) );

   // __sync_fetch_and_or( &shall_stop, true );

   if( !proc_num ) {
      sleep( 5 );
      #ifdef TRACING
      g_queue.report();
      #endif
   }

   return nullptr;
}

void*
consume_routine( void* arg )
{
   int i;
   int proc_num = (int)(long)arg;
   cpu_set_t set;

   CPU_ZERO( &set );
   CPU_SET( proc_num, &set );

   pid_t tid = gettid();

   if( sched_setaffinity( tid, sizeof(cpu_set_t), &set ) ) {
      perror( "sched_setaffinity" );
      return nullptr;
   }

   while( true ) {
      int val = -1;
      g_queue.consume( val );
   }

   PTHREAD_CALL( pthread_mutex_lock( &output_mutex ) );
   printf( "thread %d on processor %d is done\n", tid, proc_num );
   PTHREAD_CALL( pthread_mutex_unlock( &output_mutex ) );

   pthread_exit( nullptr );
   return nullptr;
}

// I only have a dual core machine, so set the number of producer and consumer
// to 1 for now...
int main()
{
   // getting number of CPUs
   int procs = (int)sysconf( _SC_NPROCESSORS_ONLN );
   if( procs < 0 ) {
      perror( "sysconf" );
      return -1;
   }

   int i = 0;
   thr_routine rtns[procs];
   for( i = 0; i < 1/*PRODUCERS*/; ++i )
      rtns[i] = &produce_routine;
   for( i = 1/*PRODUCERS*/; i < procs; ++i )
      rtns[i] = &consume_routine;

   pthread_t thrs[procs];
   if( !thrs ) {
      perror( "malloc" );
      return -1;
   }

   PTHREAD_CALL( pthread_mutex_init( &output_mutex, nullptr ) );

   for( i = 0; i < procs; ++i ) {
      if( PTHREAD_CALL( pthread_create( &thrs[i], nullptr, rtns[i], (void *)(long)i ) ) ) {
         perror( "pthread_create" );
         procs = i;
         break;
      }
   }

   for( int i = 0; i < procs/*PRODUCERS*/; ++i )
      PTHREAD_CALL( pthread_join( thrs[i], nullptr ) );

   /*  for ( i = PRODUCERS; i < procs; ++i )
        PTHREAD_CALL( pthread_detach( thrs[i] ) );*/

   sleep( 10 );
   #ifdef TRACING
   g_queue.report();
   #endif
   //	printf( "Calculated value is: %d\n", global_int );
   //	printf( "Expected value is: %d\n", INC_TO * procs );

   PTHREAD_CALL( pthread_mutex_destroy( &output_mutex ) );
   return 0;
}
