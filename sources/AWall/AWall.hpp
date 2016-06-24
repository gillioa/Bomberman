
#ifndef AWALL_HPP__
# define AWALL_HPP__

#include "AObject.hpp"

class AWall : public AObject
{
  wallType	type;
public:
  AWall(unsigned int, unsigned int, objType);
  AWall(unsigned int, unsigned int, objType, wallType);
  virtual wallType	getWallType() const;
  void		setType(wallType);
};

#endif
