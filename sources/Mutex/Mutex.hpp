
#ifndef MUTEX_H__
# define MUTEX_H__

#include <pthread.h>

class Mutex
{
  pthread_mutex_t _l;
 public:
  Mutex();
  void lock();
  void unlock();
  bool trylock();
  pthread_mutex_t & getMutex();
};


#endif
