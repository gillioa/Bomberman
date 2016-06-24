#include <unistd.h>
#include "Case.hpp"

Case::Case(unsigned int x, unsigned int y, bool w)
{
  this->x = x;
  this->y = y;
  this->isWalk = w;
  this->value = 0;
  this->obj = 0;
}

Case::Case(unsigned int x, unsigned int y)
{
  this->x = x;
  this->y = y;
  this->isWalk = false;
  this->value = 0;
  this->obj = 0;
}

Case::Case()
{
  this->x = 0;
  this->y = 0;
  this->isWalk = false;
  this->value = 0;
  this->obj = 0;
}

bool	Case::canWalk() const
{
  return (this->isWalk);
}

AObject *	 Case::getObj() const
{
  return (this->obj);
}

std::list<Player *> Case::getPlayers()
{
  return (this->players);
}

unsigned int   Case::getNbrPlayers() const
{
  return (this->players.size());
}

unsigned int   Case::getX() const
{
  return (this->x);
}

unsigned int   Case::getY() const
{
  return (this->y);
}

unsigned int   Case::getValue() const
{
  return (this->value);
}

Case &		 Case::setObj(AObject * obj)
{
  ScopedLock lock(this->m);
  this->obj = obj;
  return *this;
}

Case &		 Case::setX(unsigned int x)
{
  ScopedLock lock(this->m);
  this->x = x;
  return *this;
}

Case &		 Case::setY(unsigned int y)
{
  ScopedLock lock(this->m);
  this->y = y;
  return *this;
}

Case &		 Case::setXY(unsigned int x, unsigned int y)
{
  ScopedLock lock(this->m);
  this->x = x;
  this->y = y;
  return *this;
}

Case &		 Case::setIsWalk(bool w)
{
  ScopedLock lock(this->m);
  this->isWalk = w;
  return *this;
}

Case &		 Case::setValue(unsigned int v)
{
  ScopedLock lock(this->m);
  this->value = v;
  return *this;
}

Case &		 Case::addPlayer(Player * p)
{
  ScopedLock lock(this->m);
  this->players.push_front(p);
  return *this;
}

void		 Case::delPlayer(Player * p)
{
  ScopedLock lock(this->m);
  this->players.remove(p);
}

void		 Case::delAllPlayer()
{
  ScopedLock lock(this->m);
  if (this->players.size() != 0)
    this->players.clear();
}

void		 Case::delObj()
{
  ScopedLock lock(this->m);

  this->obj = 0;
}

void		 Case::setMutex(Mutex mut) {
  this->m = mut;
}

Mutex		 Case::getMutex() const {
  return (this->m);
}

std::ostream	&operator<<(std::ostream & os, const Case & toAff)
{
  os << "Case : posX -> " << toAff.getX() << " posY -> " << toAff.getY() << "." << std::endl;
  if (toAff.canWalk() == true)
    os << "This case is walkable and has value " << toAff.getValue() << "." << std::endl;
  else
    os << "This case is not walkable and has value " << toAff.getValue() << "." << std::endl;
  os << "There is " << toAff.getNbrPlayers() << " players on this case." << std::endl;
  if (toAff.getObj())
    os << "There is 1 object on this case." << std::endl;
  else
    os << "There is 0 object on this case." << std::endl;
  return os;
}
