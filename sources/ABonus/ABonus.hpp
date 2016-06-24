
#ifndef ABONUS
# define ABONUS

#include <ostream>
#include <iostream>
#include <vector>
#include "Timer.hpp"
#include "AObject.hpp"

class	ABonus : public AObject
{
private:
  bonusType		type;
protected:
  Uint			hp;
  int			speed;
  Uint			score;
  Uint			nbBombs;
  Uint			range;
  Uint			timeLimit;
  Timer			timer;
public:
  ABonus(Uint, Uint, bonusType, int = 0, Uint = 0, Uint = 0, Uint = 0, Uint = 0, Uint = 0);
  ~ABonus(){};
  int			getSpeed() const;
  Uint			getTimeLimit() const;
  Uint			getScore() const;
  Uint			getNbBombs() const;
  Uint			getRange() const;
  bonusType		getBonusType() const;
  bonusType		getType() const;
  Uint			getHp() const;
  ABonus		&setSpeed(Uint);
  ABonus		&setScore(Uint);
  ABonus		&setNbBombs(Uint);
  ABonus		&setRange(Uint);
  ABonus		&setTimeLimit(Uint);
  ABonus		&setType(bonusType);
  ABonus		&setHp(Uint);
  bool			isTimeElapsed();
  void			startTimer();
};

std::ostream	&operator<<(std::ostream &os, const ABonus &toAff);

#endif /*ABONUS*/
