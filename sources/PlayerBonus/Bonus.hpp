//
// Bonus.hpp for Bomberman in /home/courtu_r/BOMBERMAN/blowshitup/Sources/PlayerBonus
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Mon May 12 15:49:50 2014 courtu_r
// Last update Sun Jun 15 19:11:39 2014 courtu_r
//

#include <ctime>
#include "ABonus.hpp"

#ifndef BONUSES
# define BONUSES

class	SpeedBoost	: public ABonus
{
public:
  SpeedBoost(Uint x, Uint y) : ABonus(x, y, Speed) {
    this->speed = 1;
    this->score = 10;
  }
};

class	RangeBoost	: public ABonus
{
public:
  RangeBoost(Uint x, Uint y) : ABonus(x, y, Range) {
    this->range = 1;
    this->score = 10;
  }
};

class	BombNbBoost	: public ABonus
{
public:
  BombNbBoost(Uint x, Uint y) : ABonus(x, y, Bombnb) {
    this->nbBombs = 1;
    this->score = 10;
  }
};

class	HpBoost		: public ABonus
{
public:
  HpBoost(Uint x, Uint y) : ABonus(x, y, Hp)
  {
    this->hp = 1;
    this->score = 10;
  }
};
  
#endif /*Bonus*/
