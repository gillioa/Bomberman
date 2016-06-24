#include <iostream>

#include "Thread.hpp"

bool g_GameIsPaused = true;

Thread::Thread()
{
  this->status = false;
}

bool	Thread::getStatus() const
{
  return this->status;
}

int	Thread::startThread(void *(*fn)(void*), void *arg)
{
  int	ret;

  ret = pthread_create(&this->thread, NULL, fn, arg);
  if (ret == 0) {
    this->status = true;
    return (0);
  }
  throw (ThreadExcept());
  return (-1);
}

int	Thread::waitThread(void **thread_return)
{
  int	ret;

  ret = pthread_join(this->thread, thread_return);
  if (ret == 0) {
    this->status = false;
    return (0);
  }
  throw (ThreadExcept());
  return (-1);
}

int Thread::cancel()
{
  return (pthread_cancel(this->thread));
}
