
#ifndef AOBJECT
# define AOBJECT

typedef unsigned int Uint;

enum objType
  {
    Wall,
    Bomb,
    Bonus
  };

enum bonusType
  {
    Speed,
    Range,
    Bombnb,
    Hp,
    Random
  };

enum wallType
  {
    Breakable = 0,
    Unbreakable
  };


class AObject
{
private:
  objType	type;
protected:
  Uint		x;
  Uint		y;
public:
  AObject(Uint, Uint, objType);
  virtual ~AObject() {};
  Uint		getX() const;
  Uint		getY() const;
  objType	getType() const;
  AObject	&setX(Uint);
  AObject	&setY(Uint);
  AObject	&setType(objType);
  virtual bonusType	getBonusType() const;
  virtual wallType	getWallType() const;
};

#endif /*AOBJECT*/
