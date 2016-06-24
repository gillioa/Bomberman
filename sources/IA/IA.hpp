
#ifndef IA_HPP_
# define IA_HPP_

#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include <unistd.h>
#include "Player.hpp"
#include "Map.hpp" 

class IA
{
  Player * p;
  Map	 * m;
private:
  bool fleeBomb();
  bool defaultMove();
  bool bonusApproach();
  void bombeApproach();
  bool playerApproach();
  bool dodge();
  void initStat();
  bool loadStyle(const std::string &);
private:
  bool  parseIAScriptFile(const std::string & file);
  const std::vector<std::string> getRefTab() const;
public:
  IA &	setIntelligency(int);
  IA &	setSpeed(int);
  IA &	setAttack(int);
  IA &	setDefence(int);
  IA &	setFarming(int);
  IA &	setUsingBonus(int);
  int	getIntel() const;
  int	getSpeed() const;
  int	getAttack() const;
  int	getDefence() const;
  int	getFarming() const;
  int	getUseBonus() const;
private:
  void	setItem(const std::string &);
  int	getItemValue(const std::string &, int) const;
  int	intel;
  int	speed;
  int	attack;
  int	defence;
  int	farming;
  int	useBonus;
public:
  IA(Player *, Map *, const std::string &);
  IA(Player *, Map *);
  ~IA();
  static void	*play(void*);
  void move();
  void bomber();
public:
  Map * getMap() const;
  void	setMap(Map *);
  Player *getPlayer();
  bool	bonusApproachPow();
  bool  lookBonusUp();
  bool	lookBonusDown();
  bool	lookBonusLeft();
  bool	lookBonusRight();
  bool	bonusApproachSq();
  bool  lookBonusUpR();
  bool  lookBonusUpL();
  bool  lookBonusDownL();
  bool  lookBonusDownR();
  bool	playerApproachPow();
  bool	playerAppUp();
  bool	playerAppDown();
  bool	playerAppLeft();
  bool	playerAppRight();
  bool	dodgeUp();
  bool	dodgeDown();
  bool	dodgeRight();
  bool	dodgeLeft();
  bool	dodgePow();
  bool	fleeBombUp();
  bool	fleeBombDown();
  bool	fleeBombRight();
  bool	fleeBombLeft();
  bool  safeUp(unsigned int, unsigned int);
  bool  safeDown(unsigned int, unsigned int);
  bool  safeRight(unsigned int, unsigned int);
  bool  safeLeft(unsigned int, unsigned int);
  bool	safePow(double, double);
  bool	wallBomb();
  bool	wallBombUp();
  bool	wallBombDown();
  bool	wallBombLeft();
  bool	wallBombRight();
};

bool gameIsPaused(int k, bool newState);

#endif
