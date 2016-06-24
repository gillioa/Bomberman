
#include "IA.hpp"

bool	IA::wallBombUp()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  if (px > 0 && py > 0 && px < (this->m->getWidth() - 1) && py < (this->m->getLength() - 1) &&
      this->m->atMap(px - 1, py)->canWalk() == true &&
      (this->m->atMap(px - 1, py - 1)->canWalk() == true || this->m->atMap(px - 1, py + 1)->canWalk() == true) &&
      this->safePow(static_cast<double>(px - 1), static_cast<double>(py - 1)) == true &&
      this->safePow(static_cast<double>(px - 1), static_cast<double>(py + 1)) == true) {
    this->p->tryPlaceBomb(this->m);
    this->p->moveCaseUp(this->m);
    return (true);
  }
  return (false);
}

bool	IA::wallBombDown()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  if (px > 0 && py > 0 && px < (this->m->getWidth() - 1) && py < (this->m->getLength() - 1) &&
      this->m->atMap(px + 1, py)->canWalk() == true &&
      (this->m->atMap(px + 1, py - 1)->canWalk() == true || this->m->atMap(px + 1, py + 1)->canWalk() == true) &&
      this->safePow(static_cast<double>(px + 1), static_cast<double>(py - 1)) == true &&
      this->safePow(static_cast<double>(px + 1), static_cast<double>(py + 1)) == true) {
    this->p->tryPlaceBomb(this->m);
    this->p->moveCaseDown(this->m);
    return (true);
  }
  return (false);
}

bool	IA::wallBombRight()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  if (px > 0 && py > 0 && px < (this->m->getWidth() - 1) && py < (this->m->getLength() - 1) &&
      this->m->atMap(px, py + 1)->canWalk() == true &&
      (this->m->atMap(px - 1, py + 1)->canWalk() == true || this->m->atMap(px + 1, py + 1)->canWalk() == true) &&
      this->safePow(static_cast<double>(px - 1), static_cast<double>(py + 1)) == true &&
      this->safePow(static_cast<double>(px + 1), static_cast<double>(py + 1)) == true) {
    this->p->tryPlaceBomb(this->m);
    this->p->moveCaseRight(this->m);
    return (true);
  }
  return (false);
}

bool	IA::wallBombLeft()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  if (px > 0 && py > 0 && px < (this->m->getWidth() - 1) && py < (this->m->getLength() - 1) &&
      this->m->atMap(px, py - 1)->canWalk() == true &&
      (this->m->atMap(px - 1, py - 1)->canWalk() == true || this->m->atMap(px + 1, py - 1)->canWalk() == true) &&
      this->safePow(static_cast<double>(px - 1), static_cast<double>(py - 1)) == true &&
      this->safePow(static_cast<double>(px + 1), static_cast<double>(py - 1)) == true) {
    this->p->tryPlaceBomb(this->m);
    this->p->moveCaseLeft(this->m);
    return (true);
  }
  return (false);
}

bool	IA::wallBomb()
{
  bool  (IA::*fn_ptr[4])();
  fn_ptr[0] = &IA::wallBombUp;
  fn_ptr[1] = &IA::wallBombDown;
  fn_ptr[2] = &IA::wallBombRight;
  fn_ptr[3] = &IA::wallBombLeft;

  unsigned int	i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}

bool	IA::fleeBombUp()
{
  unsigned int	i = 0;
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  while (i < this->p->getRange() && px > 0 && 
	 (static_cast<int>(i) < this->attack || this->attack >= 8 || this->intel > 9)) {
    px -= 1;
    if (this->m->atMap(px, py)->getNbrPlayers() > 0) {
      this->p->tryPlaceBomb(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::fleeBombDown()
{
  unsigned int	i = 0;
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  while (i < this->p->getRange() && px < (this->m->getWidth() - 1) &&
	 (static_cast<int>(i) < this->attack || this->attack >= 8 || this->intel > 9)) {
    px += 1;
    if (this->m->atMap(px, py)->getNbrPlayers() > 0) {
      this->p->tryPlaceBomb(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::fleeBombRight()
{
  unsigned int	i = 0;
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  while (i < this->p->getRange() && py < (this->m->getLength() - 1) &&
	 (static_cast<int>(i) < this->attack || this->attack >= 8 || this->intel > 9)) {
    py += 1;
    if (this->m->atMap(px, py)->getNbrPlayers() > 0) {
      this->p->tryPlaceBomb(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::fleeBombLeft()
{
  unsigned int	i = 0;
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();

  while (i < this->p->getRange() && py > 0 &&
	 (static_cast<int>(i) < this->attack || this->attack >= 8 || this->intel > 9)) {
    py -= 1;
    if (this->m->atMap(px, py)->getNbrPlayers() > 0) {
      this->p->tryPlaceBomb(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::fleeBomb()
{
  bool  (IA::*fn_ptr[4])();
  fn_ptr[0] = &IA::fleeBombUp;
  fn_ptr[1] = &IA::fleeBombDown;
  fn_ptr[2] = &IA::fleeBombRight;
  fn_ptr[3] = &IA::fleeBombLeft;

  unsigned int	i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}

bool	IA::dodgeUp()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  int	i = 0;

  while ((i < 2 || i < this->defence) && px > 0) {
    px -= 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb) {
      if (this->p->moveCaseRight(this->m) == false && this->p->moveCaseLeft(this->m) == false &&
	  this->p->moveCaseDown(this->m) == false)
	this->p->moveCaseUp(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::dodgeDown()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  int	i = 0;

  while ((i < 2 || i < this->defence) && px < (this->m->getWidth() - 1)) {
    px += 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb) {
      if (this->p->moveCaseRight(this->m) == false && this->p->moveCaseLeft(this->m) == false &&
	  this->p->moveCaseUp(this->m) == false)
	this->p->moveCaseDown(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::dodgeRight()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  int	i = 0;

  while ((i < 2 || i < this->defence) && py < (this->m->getLength() - 1)) {
    py += 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb) {
      if (this->p->moveCaseUp(this->m) == false && this->p->moveCaseDown(this->m) == false &&
	  this->p->moveCaseLeft(this->m) == false)
	this->p->moveCaseRight(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::dodgeLeft()
{
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  int	i = 0;

  while ((i < 2 || i < this->defence) && py > 0) {
    py -= 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb) {
      if (this->p->moveCaseUp(this->m) == false && this->p->moveCaseDown(this->m) == false &&
	  this->p->moveCaseRight(this->m) == false)
	this->p->moveCaseLeft(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::dodgePow()
{
  bool  (IA::*fn_ptr[4])();
  fn_ptr[0] = &IA::dodgeUp;
  fn_ptr[1] = &IA::dodgeDown;
  fn_ptr[2] = &IA::dodgeRight;
  fn_ptr[3] = &IA::dodgeLeft;

  unsigned int   i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}
