
#include "IA.hpp"

bool	IA::lookBonusUp() {
  const AObject	*obj;

  if (static_cast<int>(this->p->getX() <= 0))
    return (false);
  obj = this->m->atMap(this->p->getX() - 1, this->p->getY())->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() - 1), static_cast<double>(this->p->getY()))) {
    this->p->moveCaseUp(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusRight() {
  const AObject	*obj;
  if (static_cast<unsigned int>(this->p->getY()) >= (this->m->getLength() - 1))
    return (false);
  obj = this->m->atMap(this->p->getX(), this->p->getY() + 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX()), static_cast<double>(this->p->getY() + 1))) {
    this->p->moveCaseRight(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusLeft() {
  const AObject	*obj;
  if (static_cast<unsigned int>(this->p->getY()) == 0)
    return (false);
  obj = this->m->atMap(this->p->getX(), this->p->getY() - 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX()), static_cast<double>(this->p->getY() - 1))) {
    this->p->moveCaseLeft(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusDown() {
  const AObject	*obj;
  if (static_cast<unsigned int>(this->p->getX() >= (this->m->getWidth() - 1)))
    return (false);
  obj = this->m->atMap(this->p->getX() + 1, this->p->getY())->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() + 1), static_cast<double>(this->p->getY()))) {
    this->p->moveCaseDown(this->m);
    return (true);
  }
  return (false);
}

bool    IA::bonusApproachSq() {
  bool  (IA::*fn_ptr[4])();
  fn_ptr[0] = &IA::lookBonusUp;
  fn_ptr[1] = &IA::lookBonusRight;
  fn_ptr[2] = &IA::lookBonusLeft;
  fn_ptr[3] = &IA::lookBonusDown;

  unsigned int   i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}

bool	IA::lookBonusDownR() {
  const AObject	*obj;
  obj = this->m->atMap(this->p->getX() + 1, this->p->getY() + 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() + 1), static_cast<double>(this->p->getY()))) {
    this->p->moveCaseDown(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusDownL() {
  const AObject	*obj;
  obj = this->m->atMap(this->p->getX() + 1, this->p->getY() - 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() + 1), static_cast<double>(this->p->getY() - 1))) {
    this->p->moveCaseDown(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusUpR() {
  const AObject	*obj;
  obj = this->m->atMap(this->p->getX() - 1, this->p->getY() + 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() - 1), static_cast<double>(this->p->getY()))) {
    this->p->moveCaseUp(this->m);
    return (true);
  }
  return (false);
}

bool	IA::lookBonusUpL() {
  const AObject	*obj;
  obj = this->m->atMap(this->p->getX() - 1, this->p->getY() - 1)->getObj();
  if (obj && obj->getType() == Bonus &&
      this->safePow(static_cast<double>(this->p->getX() - 1), static_cast<double>(this->p->getY()))) {
    this->p->moveCaseUp(this->m);
    return (true);
  }
  return (false);
}

bool    IA::bonusApproachPow() {
  bool  (IA::*fn_ptr[8])();
  fn_ptr[0] = &IA::lookBonusUp;
  fn_ptr[1] = &IA::lookBonusRight;
  fn_ptr[2] = &IA::lookBonusLeft;
  fn_ptr[3] = &IA::lookBonusDown;
  fn_ptr[4] = &IA::lookBonusDownR;
  fn_ptr[5] = &IA::lookBonusDownL;
  fn_ptr[6] = &IA::lookBonusUpR;
  fn_ptr[7] = &IA::lookBonusUpL;

  unsigned int   i = 0;
  while (i < 8) {
    if ((this->*fn_ptr[i])() == true)
      return (true);
    i += 1;
  }
  return (false);
}
