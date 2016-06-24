
#include <iostream>
#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex & m) : _m(m)
{
  _m.lock();
}

ScopedLock::~ScopedLock()
{
  _m.unlock();
}
