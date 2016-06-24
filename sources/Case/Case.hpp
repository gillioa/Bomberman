
#ifndef CASE_HPP_
# define CASE_HPP_

#include <list>
#include <iostream>
#include <algorithm>
#include "ScopedLock.hpp"
#include "AObject.hpp"

class Player;

class Case
{
  unsigned int		x;
  unsigned int		y;
  bool			isWalk;
  unsigned int		value;
  std::list<Player *>	players;
  AObject *		obj;
  Mutex			m;
public:
  Case();
  Case(unsigned int, unsigned int);
  Case(unsigned int, unsigned int, bool);
  bool			 canWalk() const;
  AObject *		 getObj() const;
  std::list<Player *>	 getPlayers();
  unsigned int		 getNbrPlayers() const;
  unsigned int		 getX() const;
  unsigned int		 getY() const;
  unsigned int		 getValue() const;
  Case &		 setObj(AObject *);
  Case &		 setX(unsigned int);
  Case &		 setY(unsigned int);
  Case &		 setXY(unsigned int, unsigned int);
  Case &		 setIsWalk(bool);
  Case &		 setValue(unsigned int);
  Case &		 addPlayer(Player *);
  void			 delPlayer(Player *);
  void			 delAllPlayer();
  void			 delObj();
  void			 setMutex(Mutex);
  Mutex			 getMutex() const;
};

std::ostream	&operator<<(std::ostream &, const Case &);

#endif
