
#ifndef BONUSFACTORY
# define BONUSFACTORY

#include <vector>
#include <cstdlib>
#include "ABonus.hpp"
#include "Bonus.hpp"

class	SpawnBonus
{
private:
  std::vector<ABonus *(SpawnBonus::*)(Uint, Uint) const>	create;
  ABonus	*speed(Uint, Uint) const ;
  ABonus	*range(Uint, Uint) const;
  ABonus	*nbBomb(Uint, Uint) const;
  ABonus	*hp(Uint, Uint) const;
  ABonus	*random(Uint, Uint) const;
public:
  SpawnBonus();
  ~SpawnBonus();
  ABonus	*randomSpawn(Uint x, Uint y, Uint density) const;
  ABonus	*createBonus(bonusType type, Uint x, Uint y) const;
  bonusType	getRandBonus() const;
};

#endif /*BONUSFACTORY*/
