template <typename T>
T*
Singleton<T>::instance() {
   T* tmp = instance_; // First check

   // Insert the CPU-specific memory barrier instruction
   // to synchronize the cache lines on multi-processor.
   asm("memoryBarrier");

   if (!tmp) {
      // Ensure serialization (guard constructor acquires lock_).
      Guard guard(lock_);

      // Double check.
      tmp = instance_;
      if (!tmp) {
	 tmp = new TYPE;

	 // Insert CPU-specific memory barrier instruction to synchronize the cache lines on multi-processor.
         asm("memoryBarrier");
	 instance_ = tmp;
      }

      return tmp;
   }
}
