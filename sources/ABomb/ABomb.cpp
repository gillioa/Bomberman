
#include "ABomb.hpp"

ABomb::ABomb(unsigned int x, unsigned int y, Map * m, unsigned int r, unsigned int t, bombType ty, Player *play) : AObject(x, y, Bomb)
{
  this->map = m;
  this->range = r;
  this->timer = t;
  this->bType = ty;
  this->clock.initTime();
  this->on = true;
  this->map->atMap(x, y)->setIsWalk(false);
  this->p = play;
}

void		ABomb::setPlayer(Player *pl) {
  this->p = pl;
}

Player *	ABomb::getPlayer() {
  return (this->p);
}

bool		ABomb::getOn() const
{
  return (this->on);
}

std::list<Player*>	ABomb::explodeUp(std::list<t_explod *> & exp) const
{
  unsigned int	px = this->x;
  unsigned int  py = this->y;
  unsigned int	i = 0;
  Case *	cur = 0;
  std::list<Player *> l;

  while (i < this->range && px > 0) {
    i += 1;
    px -= 1;
    cur = this->map->atMap(px, py);
    l.splice(l.end(), this->map->getPlayersAt(px, py));
    exp.push_back(new s_explod(px, py, GUp));
    if (cur->getObj() && cur->getObj()->getType() == Wall) {
      if (dynamic_cast<AWall*>(cur->getObj())->getWallType() == Breakable)
	this->map->breakWall(px, py);
      return (l);
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bomb &&
	     dynamic_cast<ABomb*>(cur->getObj())->getOn() == true) {
      l.splice(l.end(), dynamic_cast<ABomb*>(cur->getObj())->explode(exp));
      this->map->atMap(px, py)->delObj();
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bonus)
      cur->delObj();
  }
  return (l);
}

std::list<Player*>	ABomb::explodeDown(std::list<t_explod *> & exp) const
{
  unsigned int	px = this->x;
  unsigned int  py = this->y;
  unsigned int	i = 0;
  Case *	cur = 0;
  std::list<Player *> l;

  while (i < this->range && px < (this->map->getWidth() - 1)) {
    i += 1;
    px += 1;
    cur = this->map->atMap(px, py);
    exp.push_back(new s_explod(px, py, GDown));
    l.splice(l.end(), this->map->getPlayersAt(px, py));
    if (cur->getObj() && cur->getObj()->getType() == Wall) {
      if (dynamic_cast<AWall*>(cur->getObj())->getWallType() == Breakable)
	this->map->breakWall(px, py);
      return (l);
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bomb &&
	     dynamic_cast<ABomb*>(cur->getObj())->getOn() == true) {
      l.splice(l.end(), dynamic_cast<ABomb*>(cur->getObj())->explode(exp));
      this->map->atMap(px, py)->delObj();
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bonus)
      cur->delObj();
  }
  return (l);
}

std::list<Player*>	ABomb::explodeLeft(std::list<t_explod *> & exp) const
{
  unsigned int	px = this->x;
  unsigned int  py = this->y;
  unsigned int	i = 0;
  Case *	cur = 0;
  std::list<Player *> l;

  while (i < this->range && py > 0) {
    i += 1;
    py -= 1;
    cur = this->map->atMap(px, py);
    exp.push_back(new s_explod(px, py, GLeft));
    l.splice(l.end(), this->map->getPlayersAt(px, py));
    if (cur->getObj() && cur->getObj()->getType() == Wall) {
      if (dynamic_cast<AWall*>(cur->getObj())->getWallType() == Breakable)
	this->map->breakWall(px, py); 
      return (l);
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bomb &&
	     dynamic_cast<ABomb*>(cur->getObj())->getOn() == true) {
      l.splice(l.end(), dynamic_cast<ABomb*>(cur->getObj())->explode(exp));
      this->map->atMap(px, py)->delObj();
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bonus)
      cur->delObj();
  }
  return (l);
}

std::list<Player*>	ABomb::explodeRight(std::list<t_explod *> & exp) const
{
  unsigned int	px = this->x;
  unsigned int  py = this->y;
  unsigned int	i = 0;
  Case *	cur = 0;
  std::list<Player *> l;

  while (i < this->range && py < (this->map->getLength() - 1)) {
    i += 1;
    py += 1;
    cur = this->map->atMap(px, py);
    exp.push_back(new s_explod(px, py, GRight));
    l.splice(l.end(), this->map->getPlayersAt(px, py));
    if (cur->getObj() && cur->getObj()->getType() == Wall) {
      if (dynamic_cast<AWall*>(cur->getObj())->getWallType() == Breakable)
	this->map->breakWall(px, py);
      return (l);
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bomb &&
    	     dynamic_cast<ABomb*>(cur->getObj())->getOn() == true) {
      l.splice(l.end(), dynamic_cast<ABomb*>(cur->getObj())->explode(exp));
      this->map->atMap(px, py)->delObj();
    }
    else if (cur->getObj() && cur->getObj()->getType() == Bonus)
      cur->delObj();
  }
  return (l);
}

std::list<Player*>	ABomb::explodeHere(std::list<t_explod *> & exp) const
{
  unsigned int	px = this->x;
  unsigned int  py = this->y;
  Case *	cur = 0;
  std::list<Player *> l;

  exp.push_back(new s_explod(px, py, GUp));
  cur = this->map->atMap(px, py);
  l.splice(l.end(), this->map->getPlayersAt(px, py));
  if (cur->getObj() && cur->getObj()->getType() == Wall &&
      dynamic_cast<AWall*>(cur->getObj())->getWallType() == Breakable) {
    this->map->breakWall(px, py);
    return (l);
  }
  else if (cur->getObj() && cur->getObj()->getType() == Bomb &&
	   dynamic_cast<ABomb*>(cur->getObj())->getOn() == true) {
    dynamic_cast<ABomb*>(cur->getObj())->explode(exp);
    this->map->atMap(px, py)->delObj();
  }
  else if (cur->getObj() && cur->getObj()->getType() == Bonus)
    cur->delObj();
  return (l);
}

std::list<Player *>	ABomb::explode(std::list<t_explod *> & exp)
{
  std::list<Player *> l;
  if (this->on) {    
    this->on = false;
    l = this->explodeUp(exp);
    l.splice(l.end(), this->explodeDown(exp));
    l.splice(l.end(), this->explodeRight(exp));
    l.splice(l.end(), this->explodeLeft(exp));
    l.splice(l.end(), this->explodeHere(exp));
    this->getPlayer()->setBombs(this->getPlayer()->getBombs() + 1);
    this->map->atMap(this->x, this->y)->setIsWalk(true);
  }
  return l;
}

bombType	ABomb::getBombType() const
{
  return (this->bType);
}

void		ABomb::startTimer()
{
  this->clock.initTime();
}

bool		ABomb::isReady()
{
  return (this->clock.isTimeElapsed(this->timer));
}
