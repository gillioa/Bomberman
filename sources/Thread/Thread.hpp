
#ifndef THREAD_HPP_
# define THREAD_HPP_

#include <pthread.h>
#include "Except.hpp"

class Thread
{
private:
  bool		status;
  pthread_t	thread;
public:
  Thread();
  bool		getStatus() const;
  int		startThread(void *(*fn)(void*), void *);
  int		waitThread(void **);
  int cancel();
};
#endif
