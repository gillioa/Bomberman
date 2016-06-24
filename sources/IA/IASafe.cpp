
#include "IA.hpp"

bool    IA::safeUp(unsigned int px, unsigned int py)
{
  int   i = 0;

  while ((i < 2 || i < this->defence) && px > 0) {
    px -= 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb)
      return (true);
    i += 1;
  }
  return (false);
}

bool    IA::safeDown(unsigned int px, unsigned int py)
{
  int   i = 0;

  while ((i < 2 || i < this->defence) && px < (this->m->getWidth() - 1)) {
    px += 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb)
      return (true);
    i += 1;
  }
  return (false);
}

bool    IA::safeRight(unsigned int px, unsigned int py)
{
  int   i = 0;

  while ((i < 2 || i < this->defence) && py < (this->m->getLength() - 1)) {
    py += 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb)
      return (true);
    i += 1;
  }
  return (false);
}

bool    IA::safeLeft(unsigned int px, unsigned int py)
{
  int   i = 0;

  while ((i < 2 || i < this->defence) && py > 0) {
    py -= 1;
    if (this->m->atMap(px, py)->getObj() && this->m->atMap(px, py)->getObj()->getType() == Bomb)
      return (true);
    i += 1;
  }
  return (false);
}

bool    IA::safePow(double x, double y)
{
  bool  (IA::*fn_ptr[4])(unsigned int, unsigned int);
  fn_ptr[0] = &IA::safeUp;
  fn_ptr[1] = &IA::safeDown;
  fn_ptr[2] = &IA::safeRight;
  fn_ptr[3] = &IA::safeLeft;

  if (this->intel < 2)
    return (true);
  unsigned int   i = 0;
  while (i < 4) {
    if ((this->*fn_ptr[i])(static_cast<unsigned int>(x), static_cast<unsigned int>(y)) == true)
      return (false);
    i += 1;
  }
  return (true);
}
