
#include "BonusFactory.hpp"

bonusType	SpawnBonus::getRandBonus() const
{
  bonusType ret = static_cast<bonusType>(rand() % 5);
  return (ret);
}

ABonus	*SpawnBonus::speed(Uint x, Uint y) const
{
  return (new SpeedBoost(x, y));
}

ABonus	*SpawnBonus::range(Uint x, Uint y) const
{
  return (new RangeBoost(x, y));
}

ABonus	*SpawnBonus::nbBomb(Uint x, Uint y) const
{
  return (new BombNbBoost(x, y));
}

ABonus	*SpawnBonus::hp(Uint x, Uint y) const
{
  return (new HpBoost(x, y));
}

ABonus	*SpawnBonus::random(Uint x, Uint y) const
{
  return ((this->*create[static_cast<int>(this->getRandBonus() % 4)])(x, y));
}

SpawnBonus::~SpawnBonus()
{
}

ABonus	*SpawnBonus::createBonus(bonusType type, Uint x, Uint y) const
{
  ABonus	*tmp;
  try
    {
      if (type < 5)
	tmp = (this->*create[static_cast<int>(type)])(x, y);
      else
	tmp = (this->*create[static_cast<int>(type % 5)])(x, y);
      return (tmp);
    }
  catch (std::bad_alloc except)
    {
      std::cerr << "BadAlloc was caught : " << except.what() << std::endl;
      return (0);
    }
}

ABonus	*SpawnBonus::randomSpawn(Uint x, Uint y, Uint density) const
{
  Uint	res;
  Uint	rate = 105;
  
  rate -= density;
  if ((res = (rand() % rate)) < 5)
    return ((this->*create[res])(x, y));
  return (0);
}

SpawnBonus::SpawnBonus()
{
  srand(time(NULL));
  this->create.push_back(&SpawnBonus::speed);
  this->create.push_back(&SpawnBonus::range);
  this->create.push_back(&SpawnBonus::nbBomb);
  this->create.push_back(&SpawnBonus::hp);
  this->create.push_back(&SpawnBonus::random);
}
