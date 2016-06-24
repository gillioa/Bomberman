
#include "IA.hpp"

bool	IA::playerAppUp() {
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  unsigned int	i = 0;
  const AObject   *obj;

  while (px > 0) {
    px -= 1;
    if ((obj = this->m->atMap(px, py)->getObj())) {
      if (obj && obj->getType() == Wall)
	return (false);
    }
    else if (this->m->atMap(px, py)->getNbrPlayers() != 0 && i >= this->p->getRange() &&
	     this->safePow(static_cast<double>(px - 1), static_cast<double>(py))) {
      this->p->moveCaseUp(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::playerAppDown() {
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  unsigned int	i = 0;
  const AObject   *obj;

  while (px < (this->m->getWidth() - 1)) {
    px += 1;
    if ((obj = this->m->atMap(px, py)->getObj())) {
      if (obj && obj->getType() == Wall)
	return (false);
    }
    else if (this->m->atMap(px, py)->getNbrPlayers() != 0 && i >= this->p->getRange() &&
	     this->safePow(static_cast<double>(px + 1), static_cast<double>(py))) {
      this->p->moveCaseDown(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::playerAppLeft() {
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  unsigned int	i = 0;
  const AObject   *obj;

  while (py > 0) {
    py -= 1;
    if ((obj = this->m->atMap(px, py)->getObj())) {
      if (obj && obj->getType() == Wall)
	return (false);
    }
    else if (this->m->atMap(px, py)->getNbrPlayers() != 0 && i >= this->p->getRange() &&
	     this->safePow(static_cast<double>(px), static_cast<double>(py - 1))) {
      this->p->moveCaseLeft(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::playerAppRight() {
  unsigned int	px = this->p->getX();
  unsigned int	py = this->p->getY();
  unsigned int	i = 0;
  const AObject   *obj;

  while (py < (this->m->getLength() - 1)) {
    py -= 1;
    if ((obj = this->m->atMap(px, py)->getObj())) {
      if (obj && obj->getType() == Wall)
	return (false);
    }
    else if (this->m->atMap(px, py)->getNbrPlayers() != 0 && i >= this->p->getRange() &&
	     this->safePow(static_cast<double>(px), static_cast<double>(py + 1))) {
      this->p->moveCaseRight(this->m);
      return (true);
    }
    i += 1;
  }
  return (false);
}

bool	IA::playerApproachPow() {
  bool	(IA::*fn_ptr[4])();
  fn_ptr[0] = &IA::playerAppUp;
  fn_ptr[1] = &IA::playerAppDown;
  fn_ptr[2] = &IA::playerAppLeft;
  fn_ptr[3] = &IA::playerAppRight;

  unsigned int i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}
