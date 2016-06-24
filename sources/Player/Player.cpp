#include <cstdio>
#include "Player.hpp"

Player::Player(Uint playId, std::string const &playName, double posX, double posY, std::map<eEventGdl, eEventBind> bind)
  : id(playId), x(posX), y(posY), binding(bind)
{
  this->name = playName;
  this->funcTab[Up] = &Player::tryMoveUp;
  this->funcTab[Down] = &Player::tryMoveDown;
  this->funcTab[Left] = &Player::tryMoveLeft;
  this->funcTab[Right] = &Player::tryMoveRight;
  this->funcTab[PutBomb] = &Player::tryPlaceBomb;
  this->score = 0;
  this->speed = 10;
  this->range = 2;
  this->hp = 1;
  this->nbBombs = 1;
  this->hasShield = false;
  this->canPush = false;
  this->direction = GDown;
  this->active = false;
}

Player::Player()
{
  this->funcTab[Up] = &Player::tryMoveUp;
  this->funcTab[Down] = &Player::tryMoveDown;
  this->funcTab[Left] = &Player::tryMoveLeft;
  this->funcTab[Right] = &Player::tryMoveRight;
  this->direction = GDown;
  this->active = false;
}

Player::~Player() {}

void	Player::setDirection(dir d) {
  this->direction = d;
}

dir	Player::getDirection() const {
  return (this->direction);
}

bool Player::isDead() const
{
  if (hp <= 0)
    return true;
  return false;
}

bool Player::eventHolding(Map *mapp, eEventGdl event)
{
  eEventBind key;
  std::map<eEventGdl, eEventBind>::iterator it;

  if (this->binding.count(event) <= 0)
    return (false);
  it = this->binding.find(event);
  key = it->second;
  return ((this->*funcTab[key])(mapp));
}

bool	Player::tryPickUpBonus(Uint x, Uint y, Map *map)
{
  Case	*pos = map->atMap(x, y);
  ABonus	*bonus;

  if ((pos->getObj() && pos->getObj()->getType() == Bonus))
    {
      bonus = dynamic_cast<ABonus *>(pos->getObj());
      if (bonus)
	*this = *this + bonus;
      map->setBomb(0, x, y);
      return (true);
    }
    return (false);
}

bool Player::tryMoveLeft(Map *mapp)
{
  double value = 0.02 * this->speed;;
  unsigned int px = static_cast<unsigned int>(this->x);
  unsigned int py = static_cast<unsigned int>(this->y);

  this->direction = GLeft;
  this->active = true;
  if (this->y - value < 0.0)
    return (false);
  if ((mapp->atMap(px, py)->canWalk() == false && mapp->atMap(px, static_cast<int>(this->y - value))->getObj() && 
       mapp->atMap(px, static_cast<int>(this->y - value))->getObj()->getType() == Bomb) && static_cast<Uint>(this->y - value) == py)
    {
      mapp->removePlayer(this, px, py);
      this->y -= value;
      mapp->setPlayer(this, px, static_cast<unsigned int>(this->y));
      this->tryPickUpBonus(px, py, mapp);
      return (true);
    }
  if (mapp->atMap(px, static_cast<unsigned int>(this->y - value))->canWalk() == false)
    return (false);
  mapp->removePlayer(this, px, py);
  this->y -= value;
  mapp->setPlayer(this, px, static_cast<unsigned int>(this->y));
  this->tryPickUpBonus(px, static_cast<unsigned int>(this->y), mapp);
  return (true);
}

bool Player::tryMoveRight(Map *mapp)
{
  double value = 0.02 * this->speed;;
  unsigned int px = static_cast<unsigned int>(this->x);
  unsigned int py = static_cast<unsigned int>(this->y);

  this->direction = GRight;
  this->active = true;
  if (static_cast<unsigned int>(this->y + value) >= mapp->getLength())
    return (false);
  if (mapp->atMap(px, py)->canWalk() == false && mapp->atMap(px, static_cast<unsigned int>(this->y + value))->getObj() && 
      mapp->atMap(px, static_cast<unsigned int>(this->y + value))->getObj()->getType() == Bomb && static_cast<Uint>(this->y + value) == py)
    {
      mapp->removePlayer(this, px, py);
      this->y += value;
      mapp->setPlayer(this, px, static_cast<unsigned int>(this->y));
      this->tryPickUpBonus(px, py, mapp);
      return (true);
    }
  if (mapp->atMap(px, static_cast<unsigned int>(this->y + value))->canWalk() == false)
    return (false);
  mapp->removePlayer(this, px, py);
  this->y += value;
  mapp->setPlayer(this, px, static_cast<unsigned int>(this->y));
  this->tryPickUpBonus(px, static_cast<unsigned int>(this->y), mapp);
  return (true);
}

bool Player::tryMoveDown(Map *mapp)
{
  double value = 0.02 * this->speed;;
  unsigned int px = static_cast<unsigned int>(this->x);
  unsigned int py = static_cast<unsigned int>(this->y);

  this->active = true;
  this->direction = GDown;
  if (static_cast<unsigned int>(this->x + value) >= mapp->getWidth())
    return (false);
  if (mapp->atMap(px, py)->canWalk() == false && mapp->atMap(static_cast<unsigned int>(this->x + value), py)->getObj() && 
      mapp->atMap(static_cast<unsigned int>(this->x + value), py)->getObj()->getType() == Bomb && static_cast<Uint>(this->x + value) == px)
    {
      mapp->removePlayer(this, px, py);
      this->x += value;
      mapp->setPlayer(this, static_cast<unsigned int>(this->x), py);
      this->tryPickUpBonus(px, py, mapp);
      return (true);
    }
  if (mapp->atMap(static_cast<unsigned int>(this->x + value), py)->canWalk() == false)
    return (false);
  mapp->removePlayer(this, px, py);
  this->x += value;
  mapp->setPlayer(this, static_cast<unsigned int>(this->x), py);
  this->tryPickUpBonus(static_cast<unsigned int>(this->x), py, mapp);
  return (true);
}

bool Player::tryMoveUp(Map *mapp)
{
  double value = 0.02 * this->speed;;
  unsigned int px = static_cast<unsigned int>(this->x);
  unsigned int py = static_cast<unsigned int>(this->y);

  this->active = true;
  this->direction = GUp;
  if (this->x - value < 0.0)
    return (false);
  if (mapp->atMap(px, py)->canWalk() == false && mapp->atMap(static_cast<int>(this->x - value) , py)->getObj() && 
      mapp->atMap(static_cast<int>(this->x - value), py)->getObj()->getType() == Bomb && static_cast<Uint>(this->x - value) == px)
    {
      mapp->removePlayer(this, px, py);
      this->x -= value;
      mapp->setPlayer(this, static_cast<unsigned int>(this->x), py);
      this->tryPickUpBonus(px, py, mapp);
      return (true);
    }
  if (mapp->atMap(static_cast<unsigned int>(this->x - value), py)->canWalk() == false)// &&
    return (false);
  mapp->removePlayer(this, px, py);
  this->x -= value;
  mapp->setPlayer(this, static_cast<unsigned int>(this->x), py);
  this->tryPickUpBonus(static_cast<unsigned int>(this->x), py, mapp);
  return (true);
}

bool	Player::moveCaseUp(Map *m) {
  unsigned int	px = static_cast<unsigned int>(this->x);

  
   while (static_cast<unsigned int>(this->x) != (px - 1)) {
  if (this->tryMoveUp(m) == false)
    return (false);
       usleep(100000);
     }
  return (true);
}

bool	Player::moveCaseDown(Map *m) {
  unsigned int	px = static_cast<unsigned int>(this->x);

   while (static_cast<unsigned int>(this->x) != (px + 1)) {
    if (this->tryMoveDown(m) == false)
      return (false);
       usleep(100000);
     }
  return (true);
}

bool	Player::moveCaseRight(Map *m) {
  unsigned int	py = static_cast<unsigned int>(this->y);

   while (static_cast<unsigned int>(this->y) != (py + 1)) {
    if (this->tryMoveRight(m) == false)
      return (false);
       usleep(100000);
     }
  return (true);
}

bool	Player::moveCaseLeft(Map *m) {
   unsigned int	py = static_cast<unsigned int>(this->y);

   while (static_cast<unsigned int>(this->y) != (py - 1)) {
    if (this->tryMoveLeft(m) == false)
      return (false);
       usleep(100000);
     }
  return (true);
}

bool Player::tryPlaceBomb(Map *mapp)
{
  unsigned int	px = static_cast<unsigned int>(this->x);
  unsigned int	py = static_cast<unsigned int>(this->y);

  if (this->nbBombs > 0 &&
      (!(mapp->atMap(px, py)->getObj()) || (mapp->atMap(px, py)->getObj()->getType() != Bomb))) {
    this->nbBombs -= 1;
    this->bombToExplode.push_back(mapp->setBomb(px, py, this->range, static_cast<Uint>(2), this));
    return (true);
  }
  return (false);
}

std::list<ABomb *> Player::getBombToExplode() const
{
  return (bombToExplode);
}

Uint Player::getHp() const
{
  return (this->hp);
}

Player &Player::setHp(Uint hp)
{
  this->hp = hp;
  return (*this);
}

double Player::getX() const
{
  return (this->x);
}

Player &Player::setX(double x)
{
  this->x = x;
  return (*this);
}

double Player::getY() const
{
  return (this->y);
}

Player &Player::setY(double y)
{
  this->y = y;
  return (*this);
}

std::string const &Player::getName() const
{
  return (this->name);
}

Player &Player::setName(std::string const &name)
{
  this->name = name;
  return (*this);
}

Uint Player::getRange() const
{
  return (this->range);
}

Player &Player::setRange(Uint range)
{
  this->range = range;
  return (*this);
}

Uint Player::getBombs() const
{
  return (this->nbBombs);
}

Player &Player::setBombs(Uint nb)
{
  this->nbBombs = nb;
  return (*this);
}

ABomb const * Player::getBombType() const
{
  return (this->classic);
}

Player &Player::setBombType(ABomb *bomb)
{
  this->classic = bomb;
  return (*this);
}

Uint Player::getId() const
{
  return (this->id);
}

Player &Player::setId(Uint id)
{
  this->id = id;
  return (*this);
}

Player &Player::setScore(Uint score)
{
  this->score = score;
  return (*this);
}

Uint Player::getScore() const
{
  return (this->score);
}

bool Player::getShield() const
{
  return (this->hasShield);
}

Player &Player::setShield(bool shield)
{
  this->hasShield = shield;
  return (*this);
}

bool Player::getCanPush() const
{
  return (this->canPush);
}

Player &Player::setCanPush(bool push)
{
  this->canPush = push;
  return (*this);
}

Player &Player::setSpeed(Uint speed)
{
  this->speed = speed;
  return (*this);
}

Uint Player::getSpeed() const
{
  return (this->speed);
}

const std::list<ABonus *>	Player::getBonuses() const
{
  return (this->bonuses);
}

void				Player::setActive(bool stat) {
  this->active = stat;
}

Player	&Player::updateBonus()
{
  std::list<ABonus *>::iterator	it = bonuses.begin();
  std::list<ABonus *>::iterator	nextIt;

  if (bonuses.empty())
    return (*this);
  while (it != bonuses.end())
    {
      nextIt = it;
      nextIt++;
      if ((*it)->isTimeElapsed())
	*this = *this - *it;
      it = nextIt;
    }
  return (*this);
}

Player  &Player::operator+(ABonus *bonus)
{
  this->range += bonus->getRange();
  this->hp += bonus->getHp();
  this->speed += bonus->getSpeed();
  this->score += bonus->getScore();
  this->nbBombs += bonus->getNbBombs();
  if (this->speed > 20)
    this->speed = 20;
  return (*this);
}

Player &Player::operator-(ABonus *bonus)
{
  this->range -= bonus->getRange();
  this->hp -= bonus->getHp();
  this->speed -= bonus->getSpeed();
  this->nbBombs -= bonus->getNbBombs();
  return (*this);
}

std::ostream	&operator<<(std::ostream &os, const Player &play)
{
  std::list<ABonus *>	list = play.getBonuses();
  std::list<ABonus *>::const_iterator	it;

  os << std::boolalpha;
  os << "Player with id : " << play.getId() << ", at coords : " << play.getX() << ", " << play.getY();
  os << " has stats : " << std::endl << "\t- Hp : " << play.getHp() << "\n\t- Speed : " << play.getSpeed();
  os << "\n\t- Range : " << play.getRange() << "\n\t- Score : " << play.getScore() << "\n\t- NbBombs : ";
  os << play.getBombs() << "\n\t- Shield : " << play.getShield() << "\n\t- canPush : " << play.getCanPush() << std::endl;
  for (it = list.begin(); it != list.end(); it++)
    std::cout << **it;
  return (os);
}
