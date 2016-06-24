#ifndef CORE_HPP__
# define CORE_HPP__

#include <list>
#include <algorithm>
#include <SdlContext.hh>
#include "IA.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Thread.hpp"
#include "Explod.hpp"
#include <BasicShader.hh>

enum eOpt
  {
    New = 0,
    Save
  };

class Core
{
public:
  Core();
  ~Core();
  int	run();
  int	initIa();
  void	killThreads();
  void	explodeBomb(Player *);
  void	checkIa(IA *);
  void	minusLifeP(Player *);
  unsigned int getNbIa() const;
  void setNbIa(unsigned int);
  bool getSplitScreen() const;
  void setSplitScreen(bool);
  eOpt getOpt() const;
  void setOpt(eOpt);
  const std::string &getFileMapName() const;
  void setFileMapName(const std::string &);
  const gdl::SdlContext &getContext() const;
  void setContext(gdl::SdlContext &);
  const gdl::BasicShader &getShader() const;
  void setShader(gdl::BasicShader &);
  std::vector<Player *> *getPlayers() const { return this->players; }
  std::vector<IA *> * getIA() const { return this->ia; }
  Map * getMap() const { return this->map; }

  void setPlayerName(std::string, int n);
  std::string getPlayerName(int) const;

  void setTotalTime(Uint);
  unsigned int getTotalTime() const;
  void setDensity(Uint);
  Uint	getDensity() const;
  void addPlayer(Player *pl) { players->push_back(pl); }
  void setMap(Map *m) { map = m; }
  void setIaDifficulty(std::string &dif) { this->iaDifficulty = dif; }
  void setIA(IA *p) { ia->push_back(p); }
  int getMaxNbIa(const std::string &) const;

  bool getIsLoaded() const { return this->isLoaded; }
  void setIsLoaded(bool b) { this->isLoaded = b; }

  std::string getFileName() const { return this->filename; }
  void setFileName(const std::string &filename) { this->filename = filename; }

  void setNoMapForMenu(int n) { this->noMapMenu = n;}
  int getNoMapForMenu() const { return this->noMapMenu; }

  void setLevelIaMenu(int n) { this->levelIaMenu = n;}
  int getLevelIaMenu() const  {return  this->levelIaMenu; }


  void setMaxIa(int n) { this->nbMaxIa = n; }
  int getMaxIa() const { return nbMaxIa; }

private:
  Map * map;
  std::vector<Thread *> thread;
  std::vector<Player *> *players;
  std::vector<IA *> *ia;
  std::list<t_explod *> explose;
  std::string iaDifficulty;
  unsigned int nbIa;
  bool split;
  eOpt opt;
  std::string fileMapName;
  gdl::SdlContext context;
  gdl::BasicShader shader;
  std::vector<std::string> playersName;
  Uint totalTime;
  Uint density;
  bool isLoaded;

  int noMapMenu;
  int levelIaMenu;

  int nbMaxIa;
  std::string filename;
  // Graphique
  // Menu
};

#endif // ! EOF - Core.hpp
