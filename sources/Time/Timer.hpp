//
// Timer.hpp for Bomberman in /home/courtu_r/BOMBERMAN/blowshitup/Sources/Time
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Thu May 15 09:49:12 2014 courtu_r
// Last update Thu May 15 10:38:30 2014 courtu_r
//

#ifndef TIMER
# define TIMER

#include <sys/time.h>
#include <cstdlib>

typedef unsigned int Uint;

class	Timer
{
private:
  time_t	init_pause;
  time_t	incre_pause;
  time_t	pause_time;
  time_t	init_time;
  time_t	getCurrentTime();
public:
  Timer();
  ~Timer() {};
  bool		isTimeElapsed(Uint timeLimit);
  bool		initTime();
};

bool gameIsPaused(int, bool);

#endif /*TIMER*/
