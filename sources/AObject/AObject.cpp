
#include "AObject.hpp"

AObject::AObject(Uint x, Uint y, objType type)
{
  this->x = x;
  this->y = y;
  this->type = type;
}

Uint		AObject::getX() const
{
  return (this->x);
}

Uint		AObject::getY() const
{
  return (this->y);
}

objType		AObject::getType() const
{
  return (this->type);
}

AObject		&AObject::setX(Uint x)
{
  this->x = x;
  return (*this);
}

AObject		&AObject::setY(Uint y)
{
  this->y = y;
  return (*this);
}

AObject		&AObject::setType(objType type)
{
  this->type = type;
  return (*this);
}

bonusType	AObject::getBonusType() const
{
  return (Random);
}

wallType	AObject::getWallType() const
{
  return (Breakable);
}
