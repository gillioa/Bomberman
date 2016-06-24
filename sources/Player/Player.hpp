#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <unistd.h>
#include <algorithm>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include "Map.hpp"
#include "ABonus.hpp"
#include "myModel.hpp"

class ABomb;
class Map;

enum eEventGdl
  {
  };

enum eEventBind
  {
    Up = 0,
    Down,
    Right,
    Left,
    PutBomb,
  };

typedef unsigned int Uint;

class Player
{
private:
  bool			active;
  Uint			id;
  Uint			speed;
  Uint			score;
  Uint			nbBombs;
  Uint			range;
  double		x;
  double		y;
  Uint			hp;
  std::string		name;
  std::list<ABonus *>	bonuses;
  std::list<ABomb *>	bombToExplode;
  std::map<eEventGdl, eEventBind> binding;
  typedef bool (Player::*func)(Map*);
  func			funcTab[5];
  ABomb			*classic;
  bool			canPush;
  bool			hasShield;
  dir			direction;
  bool tryPickUpBonus(Uint, Uint, Map *);
public:
  bool tryMoveUp(Map*);
  bool tryMoveDown(Map*);
  bool tryMoveRight(Map*);
  bool tryMoveLeft(Map*);
  bool tryPlaceBomb(Map*);
public:
  Player();
  Player(Uint, std::string const &, double, double, std::map<eEventGdl, eEventBind>);
  ~Player();
  void		setDirection(dir);
  dir		getDirection() const;
  bool		eventHolding(Map*, eEventGdl);
  std::list<ABomb *>getBombToExplode() const;
  Uint		getId() const;
  Player	&setId(Uint);
  Uint		getHp() const;
  Player	&setHp(Uint);
  double	getX() const;
  Player	&setX(double);
  double	getY() const;
  Player	&setY(double);
  std::string const &getName() const;
  Player	&setName(std::string const &);
  Uint		getRange() const;
  Player	&setRange(Uint);
  Uint		getBombs() const;
  Player	&setBombs(Uint);
  ABomb const *	getBombType() const;
  Player	&setBombType(ABomb *);
  Uint		getScore() const;
  Player	&setScore(Uint);
  bool		getShield() const;
  Player	&setShield(bool);
  bool		getCanPush() const;
  Player	&setCanPush(bool);
  Uint		getSpeed() const;
  Player	&setSpeed(Uint);
  Player	&operator+(ABonus *bonus);
  Player	&operator-(ABonus *bonus);
  Player	&updateBonus();
  bool		moveCaseLeft(Map *);
  bool		moveCaseRight(Map *);
  bool		moveCaseUp(Map *);
  bool		moveCaseDown(Map *);
  bool		isDead() const;
  const std::list<ABonus *> getBonuses() const;
  void		setActive(bool);
  bool		isActive() {
    return (this->active);
  };
};

std::ostream    &operator<<(std::ostream &, const Player &);

#endif
