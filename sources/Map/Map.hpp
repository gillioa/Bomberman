
#ifndef MAP_HPP
# define MAP_HPP

#include <vector>
#include "Case.hpp"
#include "AObject.hpp"
#include "BonusFactory.hpp"
#include "ABomb.hpp"

class Player;
class ABomb;

class Map
{
  SpawnBonus		bSpawn;
  std::vector<Case *>	map;
  unsigned int		length;
  unsigned int		width;
  Uint			density;
public:
  Map();
  Map(unsigned int, unsigned int, std::vector<Case *>);
  Map(unsigned int, unsigned int);
  Case	*		atMap(unsigned int, unsigned int);
  const Case *		access(unsigned int, unsigned int) const;
  void			removePlayer(Player *, unsigned int, unsigned int);
  void			setPlayer(Player *, unsigned int, unsigned int);
  bool			breakWall(unsigned int, unsigned int);
  void			setBomb(AObject *, unsigned int, unsigned int);
  ABomb			*setBomb(Uint, Uint, Uint, Uint, Player *);
  unsigned int		getWidth() const;
  unsigned int		getLength() const;
  std::vector<Case *>	getMap();
  const std::vector<Case *>	getCMap() const;
  std::list<Player *>	getPlayersAt(unsigned int, unsigned int);
  Map &			setWidth(unsigned int);
  Map &			setLength(unsigned int);
  void			setMapVector(std::vector<Case *>);
  void			setMapSpawner(SpawnBonus);
  Map			&setDensity(Uint);
  Uint			getDensity()const;
};

std::ostream	&operator<<(std::ostream &, const Map &);

#endif
