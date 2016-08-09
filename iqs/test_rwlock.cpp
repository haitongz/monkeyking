
class ReadWriteLock
{
   public:
      ReadWriteLock( int maxReaders = 32 )
      : semaphore( maxReaders ) {
      }

      void lockRead() { semaphore++; }
      void unlockRead() { semaphore--; }
      void lockWrite() {
         Guard _( &mutex );
         for( int i = 0; i < maxReaders(); ++i )
            semaphore++;
      }

      void unlockWrite() { semaphore -= semaphore.total(); }
      int maxReaders() const { return semaphore.total(); }

   private:
      Semaphore semaphore;
      Mutex mutex;
};

// Here's how we can use it in applications:
//    ReadWriteLock rwlock;

void ReaderThread::run() {
   // ...
   rwlock.lockRead();
   read_file();
   rwlock.unlockRead();
   // ...
}

void WriterThread::run() {
   // ...
   rwlock.lockWrite();
   write_file();
   rwlock.unlockWrite();
   // ...
}
