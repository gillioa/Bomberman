
#ifndef SCOPEDLOCK_H__
# define SCOPEDLOCK_H__

#include "Mutex.hpp"

class ScopedLock
{
  Mutex & _m;
public:
  ScopedLock(Mutex &);
  ~ScopedLock();
};


#endif
