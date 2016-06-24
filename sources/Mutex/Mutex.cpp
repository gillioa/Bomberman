
#include "Mutex.hpp"

Mutex::Mutex()
{
  pthread_mutex_init(&_l, NULL);
}

void			Mutex::lock()
{
  pthread_mutex_lock(&_l);
}

void			Mutex::unlock()
{
  pthread_mutex_unlock(&_l);
}

bool			Mutex::trylock()
{
  int	ret;

  ret = pthread_mutex_trylock(&_l);
  if (ret == 0)
    return (true);
  return (false);
}

pthread_mutex_t		&Mutex::getMutex()
{
  return (_l);
}
