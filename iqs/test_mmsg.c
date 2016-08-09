#include "linux/arch/x86/include/asm/unistd.h"

#include <stdlib.h>
#include <syscall.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/mman.h>

struct mmsghdr
{
   struct msghdr msg_hdr;
   unsigned      msg_len;
};

#ifndef NSEC_PER_MSEC
#define NSEC_PER_MSEC   1000000UL
#endif

/* Set a fd into nonblocking mode. */
int set_nonblocking( int fd )
{
   int val;

   if( (val = fcntl( fd, F_GETFL )) == -1 )
      return -1;

   if( !(val & O_NONBLOCK) ) {
      val |= O_NONBLOCK;
      return fcntl( fd, F_SETFL, val );
   }

   return 0;
}

static int
recvmmsg( int fd,
          struct mmsghdr* mmsg,
	  unsigned vlen,
	  unsigned flags,
	  struct timespec* timeout )
{
   return syscall( __NR_recvmmsg, fd, mmsg, vlen, flags, timeout );
}

static int
reg_recvmsg( int fd,
             struct mmsghdr* mmsg,
	     unsigned vlen,
	     unsigned flags,
	     struct timespec* timeout )
{
   int i;
   int ret = -1;

   for( i = 0; i < vlen; ++i ) {
      int tmp = recvmsg( fd, &mmsg[i].msg_hdr, flags );
      if( tmp < 0 )
         break;
      mmsg[i].msg_len = tmp;
      ++ret;
   }
   return ret;
}

static int reg_sendmsg(int fd, struct mmsghdr *mmsg,
unsigned vlen, unsigned flags,
struct t
imespec *timeout)
{
   int i;
   int ret = 0;

   for (i=0; i<vlen; i++) {
      int tmp = sendmsg(fd, &mmsg[i].msg_hdr, flags);
      if (tmp <= 0) {
         ret = tmp;
         break;
      }
      mmsg[i].msg_len = tmp;
      ret++;
   }
   return ret;
}

static unsigned long long micro_time()
{
   struct timeval tv;
   gettimeofday(&tv, NULL);
   return tv.tv_sec*NSEC_PER_MSEC+tv.tv_usec;
}

typedef int (*send_packets_f)(int fd, struct mmsghdr *mmsg, unsigned vlen,
unsigned flags, struct timespec *timeout);
typedef int (*recv_packets_f)(int fd, struct mmsghdr *mmsg, unsigned vlen,
unsigned flags, struct timespec *timeout);

//sockets must be bound/connected
static void producer(const int batch_size,
const int packet_size,
int send_sock,
send_packets_f send_f)
{
   char buf[batch_size][packet_size];
   struct iovec iovec[batch_size];
   struct mmsghdr datagrams[batch_size];
   int i;

   for (i = 0; i < batch_size; ++i) {
      memset(&datagrams[i].msg_hdr, 0, sizeof(datagrams[i].msg_hdr));
      iovec[i].iov_base = buf[i];
      iovec[i].iov_len  = sizeof(buf[i]);
      datagrams[i].msg_hdr.msg_iov   = &iovec[i];
      datagrams[i].msg_hdr.msg_iovlen   = 1;
   }

   while (1) {
      //generate batch_size packets of packet_size, stamp them, and send
      int send_num = 0;
      for (i = 0; i < batch_size; ++i) {
         unsigned long long *stamp =
            (unsigned long long *) &buf[i][0];
         *stamp = micro_time();
      }

      send_num = send_f(send_sock, datagrams, batch_size, 0, 0);
      if (send_num < batch_size) {
         printf("could not send entire batch: %d %m\n", send_num);
         continue;
      }
   }
}

//sockets must be bound/connected
static void consumer(const int batch_size,
const int packet_size,
int recv_sock,
recv_packets_f recv_f)
{
   char buf[batch_size][packet_size];
   struct iovec iovec[batch_size];
   struct mmsghdr datagrams[batch_size];
   int i;
   unsigned long long start_time = micro_time();
   unsigned long long max = 0;
   double mean = 0;
   double m2 = 0;
   int n = 0;

   if (set_nonblocking(recv_sock) != 0)
      printf("recv socket is in blocking mode\n");
   else
      printf("recv socket is in non-blocking mode\n");

   for (i = 0; i < batch_size; ++i) {
      memset(&datagrams[i].msg_hdr, 0, sizeof(datagrams[i].msg_hdr));
      iovec[i].iov_base = buf[i];
      iovec[i].iov_len  = sizeof(buf[i]);
      datagrams[i].msg_hdr.msg_iov   = &iovec[i];
      datagrams[i].msg_hdr.msg_iovlen   = 1;
   }

   struct pollfd pfds[1] = {
      [0] = {
         .fd = recv_sock,
         .events = POLLIN,
      },
   };

   while (1) {
      unsigned long long now;

      if (poll(pfds, 1, -1) < 0) {
         perror("poll: ");
         exit(0);
      }

      int ret = recv_f(recv_sock, &datagrams[0], batch_size, 0, 0);
      if (ret < 0) {
         perror("consumer recv: ");
         exit(0);
      }

      //go over all received packets, and count latency:
      now = micro_time();
      for (i = 0; i < ret; ++i) {
         double delta;
         unsigned long long *stamp =
            (unsigned long long *) &buf[i];
         unsigned long long sample =
            now - *stamp;
         n++;
         delta = sample - mean;
         mean += delta/n;
         m2 += delta*(sample-mean);

         if (max < sample)
            max = sample;
      }

      if (micro_time() - start_time >= 5000000) {
         printf("packets num: %d, mean: %.2f, max: %llu, stddev: %.2f\n",
            n, mean, max, sqrt(m2/(n-1)));
         printf("packets per second: %.2f, bytes per second: %lld\n",
            n / ((micro_time() - start_time)/1000000.0),
            n*packet_size / ((micro_time() - start_time)/1000000));

         start_time = micro_time();
         n = 0;
         mean = 0;
         m2 = 0;
         max = 0;
      }
   }
}

//sockets must be bound/connected
static void mirror(const int batch_size,
const int packet_size,
int send_sock,
int recv_sock,
send_packets_f send_f,
recv_packets_f recv_f)
{
   char buf[batch_size][packet_size];
   struct iovec iovec[batch_size];
   struct mmsghdr datagrams[batch_size];
   int i;

   if (set_nonblocking(recv_sock) != 0)
      printf("recv socket is in blocking mode\n");
   else
      printf("recv socket is in non-blocking mode\n");

   for (i = 0; i < batch_size; ++i) {
      memset(&datagrams[i].msg_hdr, 0, sizeof(datagrams[i].msg_hdr));
      iovec[i].iov_base = buf[i];
      iovec[i].iov_len  = sizeof(buf[i]);
      datagrams[i].msg_hdr.msg_iov   = &iovec[i];
      datagrams[i].msg_hdr.msg_iovlen   = 1;
      datagrams[i].msg_hdr.msg_name  = NULL;
   }

   while (1) {
      int send_num = 0;
      int recv_num = 0;

      struct pollfd pfds[1] = {
         [0] = {
            .fd = recv_sock,
            .events = POLLIN,
         },
      };

      if (poll(pfds, 1, -1) < 0) {
         perror("poll: ");
         exit(0);
      }

      //printf("slave recv...\n");
      recv_num = recv_f(recv_sock, &datagrams[recv_num],
         batch_size-recv_num, 0, 0);
      if (recv_num < 0) {
         perror("mirror recv");
         exit(0);
      }
      //printf("recv %d packets\n", recv_num);

      while (send_num < recv_num) {
         int ret = send_f(send_sock, &datagrams[send_num], recv_num-send_num, 0, 0);
         if (ret < 0) {
            perror("mirror send");
            exit(0);
         }
         send_num += ret;
         //printf("sent %d packets\n", ret);
      }
   }
}

static void usage(char *app)
{
   printf("Usage: %s\n"
      "	-n do not use recvmmsg\n"
      "	-r producer/consumer/mirror [producer]\n"
      "	-b recv_batch_size          [8]\n"
      "	-l master_listen_port       [5001]\n"
      "	-t send_to_host             [localhost]\n"
      "	-p slave_listen_port        [5002]\n"
      "	-s packet_size              [256]\n"
      "	-f run in sched fifo\n"
      "	-m use mlockall\n"
      "	-h this help\n",
      app);
}

int create_recv_sock(const char *port)
{
   struct addrinfo *host;
   struct addrinfo hints;
   int fd = -1;
   int err;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_flags = AI_PASSIVE;                   /* For wildcard IP address */
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_DGRAM;                /* Datagram socket */
   hints.ai_protocol = 0;                         /* Any protocol */
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;

   err = getaddrinfo(NULL, port, &hints, &host);
   if (err != 0) {
      fprintf(stderr, "error using getaddrinfo: %s\n",
         gai_strerror(err));
      goto out;
   }

   fd = socket(host->ai_family, host->ai_socktype, host->ai_protocol);
   if (fd < 0) {
      perror("recv_sock: ");
      goto out_freeaddrinfo;
   }

   if (bind(fd, host->ai_addr, host->ai_addrlen) < 0) {
      perror("recv_sock bind");
      close(fd);
   }

   out_freeaddrinfo:
   freeaddrinfo(host);
   out:
   return fd;
}

int create_send_sock(const char *host, const char *port)
{
   int fd = -1;
   struct addrinfo *send_host;
   struct addrinfo hints;
   int err;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_flags = AI_PASSIVE;                   /* For wildcard IP address */
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_DGRAM;                /* Datagram socket */
   hints.ai_protocol = 0;                         /* Any protocol */
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;

   err = getaddrinfo(host, port, &hints, &send_host);
   if (err != 0) {
      fprintf(stderr, "error using getaddrinfo: %s\n",
         gai_strerror(err));
      goto out;
   }

   fd = socket(send_host->ai_family, send_host->ai_socktype,
      send_host->ai_protocol);
   if (fd < 0) {
      perror("send_sock");
      goto out_freeaddrinfo;
   }

   if (connect(fd, send_host->ai_addr, send_host->ai_addrlen) != 0) {
      perror("send_sock connect");
      close(fd);
   }

   out_freeaddrinfo:
   freeaddrinfo(send_host);
   out:
   return fd;
}

int main(int argc, char *argv[])
{
   const char *master_listen_port = "5001";
   const char *slave_listen_port = "5002";
   const char *listen_port;
   const char *send_port;
   const char *target_host = "localhost";
   const char *role = "producer";
   int batch_size = 8;
   int packet_size = 256;
   int use_mmsg = 1;
   int s_fifo = 0;
   int lock_mem = 0;
   char c;

   while ( (c=getopt(argc, argv, "mfhr:b:nl:t:p:s:")) != -1) {
      switch(c) {
         case 'r':
            role = optarg;
            break;
         case 'b':
            batch_size = atoi(optarg);
            break;
         case 'l':
            master_listen_port = optarg;
            break;
         case 't':
            target_host = optarg;
            break;
         case 'p':
            slave_listen_port = optarg;
            break;
         case 'n':
            use_mmsg = 0;
            break;
         case 'm':
            lock_mem = 1;
            break;
         case 'f':
            s_fifo = 1;
            break;
         case 's':
            packet_size = atoi(optarg);
            break;
         case 'h':
         default:
            usage(argv[0]);
            exit(0);
      }
   }
   //set scheduling to SCHED_FIFO
   struct sched_param params;
   params.sched_priority = 99;

   if (s_fifo && sched_setscheduler(getpid(), SCHED_FIFO, &params) != 0) {
      perror("sched_setscheduler");
   }

   if (sched_getscheduler(getpid()) != SCHED_FIFO)
      printf("not running in SCHED_FIFO\n");
   else
      printf("running in SCHED_FIFO\n");

   if (lock_mem) {
      if (mlockall(MCL_CURRENT|MCL_FUTURE) != 0)
         perror("mlockall failed");
      else
         printf("memory is locked\n");
   }

   if (strcmp(role, "producer") == 0 ||
   strcmp(role, "consumer") == 0) {
      listen_port = master_listen_port;
      send_port = slave_listen_port;
   }
   else {
      listen_port = slave_listen_port;
      send_port = master_listen_port;
   }

   if (strcmp(role, "producer") == 0) {
      int send_sock = create_send_sock(target_host, send_port);
      if (send_sock < 0) {
         perror("send sock");
         goto out;
      }
      if (use_mmsg) {
         printf("starting producer with mmsg\n");
         producer(batch_size,
            packet_size,
            send_sock,
            reg_sendmsg);
      }
      else {
         printf("starting producer without mmsg\n");
         producer(batch_size,
            packet_size,
            send_sock,
            reg_sendmsg);
      }
   }
   else if (strcmp(role, "consumer") == 0) {
      int recv_sock = create_recv_sock(listen_port);
      if (recv_sock < 0) {
         perror("recv_sock ");
         goto out;
      }
      if (use_mmsg) {
         printf("starting consumer with mmsg\n");
         consumer(batch_size,
            packet_size,
            recv_sock,
            recvmmsg);
      }
      else {
         printf("starting consumer without mmsg\n");
         consumer(batch_size,
            packet_size,
            recv_sock,
            reg_recvmsg);
      }
   }
   else if (strcmp(role, "mirror") == 0) {
      int recv_sock = create_recv_sock(listen_port);
      int send_sock = create_send_sock(target_host, send_port);
      if (send_sock < 0) {
         perror("send sock");
         goto out;
      }
      if (recv_sock < 0) {
         perror("recv_sock ");
         goto out;
      }
      if (use_mmsg) {
         printf("starting mirror with mmsg\n");
         mirror(batch_size,
            packet_size,
            send_sock,
            recv_sock,
            reg_sendmsg,
            recvmmsg);

      }
      else {
         printf("starting mirror without mmsg\n");
         mirror(batch_size,
            packet_size,
            send_sock,
            recv_sock,
            reg_sendmsg,
            reg_recvmsg);
      }

   }
   else {
      printf("please specify role as either master or slave\n");
   }

   out:
   return 0;
}
