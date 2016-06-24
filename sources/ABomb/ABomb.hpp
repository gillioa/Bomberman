
#ifndef ABOMB
# define ABOMB

#include <list>
#include <algorithm>
#include <iostream>
#include "Timer.hpp"
#include "Map.hpp"
#include "AWall.hpp"
#include "Player.hpp"
#include "Explod.hpp"

class Map;

enum bombType
  {
    Classic,
    Other
  };

class ABomb : public AObject
{
  Player	*p;
  Timer		clock;
  Map *		map;
  unsigned int	range;
  unsigned int	timer;
  bombType	bType;
  bool		on;
private:
  std::list<Player*>	explodeUp(std::list<t_explod *> &) const;
  std::list<Player*>	explodeDown(std::list<t_explod *> &) const;
  std::list<Player*>	explodeLeft(std::list<t_explod *> &) const;
  std::list<Player*>	explodeRight(std::list<t_explod *> &) const;
  std::list<Player*>	explodeHere(std::list<t_explod *> &) const;
public:
  ABomb(unsigned int, unsigned int, Map *, unsigned int, unsigned int, bombType, Player *);
  std::list<Player*>	explode(std::list<t_explod *> &);
  bombType		getBombType() const;
  void			startTimer();
  bool			isReady();
  bool			getOn() const;
  Map *			getMap() { return this->map; }
  void			setPlayer(Player *);
  Player *		getPlayer();
};

#endif
