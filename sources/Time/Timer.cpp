//
// Timer.cpp for Bomberman in /home/courtu_r/BOMBERMAN/blowshitup/Sources/Time
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Thu May 15 09:53:41 2014 courtu_r
// Last update Thu May 15 10:42:07 2014 courtu_r
//

#include "Except.hpp"
#include "Timer.hpp"

Timer::Timer() {
  this->pause_time = 0;
  this->incre_pause = 0;
  this->init_pause = 0;
}

time_t	Timer::getCurrentTime()
{
  struct timeval	time;
  
  if (!(gettimeofday(&time, NULL)))
    return (time.tv_sec);
  else
    throw (TimerErr());
}

bool	Timer::initTime()
{
  try 
    {  
      this->init_time = this->getCurrentTime();
      return (true);
    }
  catch (TimerErr err)
    {
      err.printErr();
      return (false);
    }
}

bool	Timer::isTimeElapsed(Uint timeLimit)
{
  try
    {
      if (gameIsPaused(-1, true) == true) {
	if (this->init_pause == 0)
	  this->init_pause = this->getCurrentTime();
	this->incre_pause = this->getCurrentTime() - this->init_pause;
	return (false);
      }
      else {
	this->pause_time += this->incre_pause;
	this->incre_pause = 0;
	this->init_pause = 0;
      }
      if (this->getCurrentTime() - this->init_time > (timeLimit + this->pause_time))
	return true;
      else
	return (false);
    }
  catch (TimerErr err)
    {
      err.printErr();
      return (false);
    }
}
