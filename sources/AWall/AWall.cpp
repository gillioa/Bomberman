
#include "AWall.hpp"

AWall::AWall(unsigned int x, unsigned int y, objType ot) : AObject(x, y, ot) {
  this->type = Breakable;
}

AWall::AWall(unsigned int x, unsigned int y, objType ot, wallType t) : AObject(x, y, ot) {
  this->type = t;
}

void	AWall::setType(wallType t) {
  this->type = t;
}

wallType	AWall::getWallType() const {
  return (this->type);
}
