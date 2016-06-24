
#include "ABonus.hpp"

ABonus::ABonus(Uint x, Uint y, bonusType type, int speed, Uint score, Uint nbBombs, Uint range, Uint timeLimit, Uint hp) : AObject(x, y, Bonus)
{
  this->speed = speed;
  this->score = score;
  this->nbBombs = nbBombs;
  this->range = range;
  this->timeLimit = timeLimit;
  this->type = type;
  this->hp = hp;
}

int	ABonus::getSpeed() const
{
  return (this->speed);
}

Uint	ABonus::getTimeLimit() const
{
  return (this->timeLimit);
}

Uint	ABonus::getScore() const
{
  return (this->score);
}

Uint	ABonus::getNbBombs() const
{
  return (this->nbBombs);
}

Uint      ABonus::getRange() const
{
  return (this->range);
}

Uint	ABonus::getHp() const
{
  return (this->hp);
}

bonusType	ABonus::getType() const
{
  return (this->type);
}

ABonus		&ABonus::setSpeed(Uint speed)
{
  this->speed = speed;
  return (*this);
}

ABonus		&ABonus::setScore(Uint score)
{
  this->score = score;
  return (*this);
}

ABonus		&ABonus::setNbBombs(Uint nbBombs)
{
  this->nbBombs = nbBombs;
  return (*this);
}

ABonus		&ABonus::setRange(Uint range)
{
  this->range = range;
  return (*this);
}

ABonus		&ABonus::setTimeLimit(Uint timeLimit)
{
  this->timeLimit = timeLimit;
  return (*this);
}

ABonus		&ABonus::setType(bonusType type)
{
  this->type = type;
  return (*this);
}

ABonus		&ABonus::setHp(Uint hp)
{
  this->hp = hp;
  return (*this);
}

std::ostream	&operator<<(std::ostream &os, const ABonus &toAff)
{
  os << "Bonus with type : " << toAff.getType() << " Has as attributes : \n\t- hp : " << toAff.getHp() << "\n\t- speed : " << toAff.getSpeed() << "\n\t- score : " << toAff.getScore() << "\n\t- NbBombs : ";
  os << toAff.getNbBombs() << "\n\t- range : " << toAff.getRange() << "\n\t- timeLimit : " << toAff.getTimeLimit() << std::endl;
  return (os);
}

bool		ABonus::isTimeElapsed()
{
  return (this->timer.isTimeElapsed(this->timeLimit));
}

void		ABonus::startTimer()
{
  this->timer.initTime();
}

bonusType		ABonus::getBonusType() const
{
  return (this->type);
}
