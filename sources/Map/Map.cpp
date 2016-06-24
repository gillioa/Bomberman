
#include "Map.hpp"

Map::Map() :
length(0),
width(0)
{
}

Map::Map(unsigned int l, unsigned int w)
{
  this->length = l;
  this->width = w;
}

Map::Map(unsigned int l, unsigned int w, std::vector<Case *> m)
{
  this->length = l;
  this->width = w;
  this->map = m;
}

ABomb	*Map::setBomb(Uint x, Uint y, Uint range, Uint timer, Player *play)
{
  ABomb	*bomb = new ABomb(x, y, this, range, timer, Classic, play);
  
  this->atMap(x, y)->setObj(bomb);
  return (bomb);
}

Case*   Map::atMap(unsigned int x, unsigned int y)
{
  unsigned int n = x * this->length + y;
  return (this->map[n]);
}

const Case * Map::access(unsigned int x, unsigned int y) const
{
  unsigned int n = x * this->length + y;
  return (this->map[n]);
}

void	Map::removePlayer(Player * p, unsigned int x, unsigned int y)
{
  this->atMap(x, y)->delPlayer(p);
}

void	Map::setPlayer(Player * p, unsigned int x, unsigned int y)
{
  this->atMap(x, y)->addPlayer(p);
}

bool	Map::breakWall(unsigned int x, unsigned int y)
{
  Case	*c = this->atMap(x, y);
  c->delObj();
  c->setIsWalk(true); 
  this->setBomb(this->bSpawn.randomSpawn(x, y, this->density), x, y);
  return (true);
}

void	Map::setBomb(AObject * obj, unsigned int x, unsigned int y)
{
  this->atMap(x, y)->setObj(obj);
}

std::vector<Case *>	Map::getMap()
{
  return (this->map);
}

const std::vector<Case *>	Map::getCMap() const
{
  return (this->map);
}

unsigned int		Map::getLength() const
{
  return (this->length);
}

unsigned int		Map::getWidth() const
{
  return (this->width);
}

std::ostream	&operator<<(std::ostream & os, const Map & toAff)
{
  std::cout << "Map : length is " << toAff.getLength() << " and width is " << toAff.getWidth() << "." << std::endl;
  return (os);
}

std::list<Player *>	Map::getPlayersAt(unsigned int x, unsigned int y)
{
  std::list<Player *> players;
  return (this->atMap(x, y)->getPlayers());
}

Map &			Map::setWidth(unsigned int value) {
  this->width = value;
  return *this;
}

Map &			Map::setLength(unsigned int value) {
  this->length = value;
  return *this;
}

void			Map::setMapVector(std::vector<Case*> vec) {
  this->map = vec;
}

void			Map::setMapSpawner(SpawnBonus sp) {
  this->bSpawn = sp;
}

Map			&Map::setDensity(Uint density)
{
  this->density = density;
  return (*this);
}

Uint			Map::getDensity() const
{
  return (this->density);
}
