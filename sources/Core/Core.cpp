#include <iostream>
#include <vector>
#include <unistd.h>

#include "IA.hpp"
#include "Thread.hpp"
#include "Core.hpp"
#include "AWall.hpp"
#include "Player.hpp"
#include "myModel.hpp"
#include "MapGenerator.hpp"
#include "GameEngine.hpp"
#include "Serialize.hpp"
#include "LoadSave.hpp"

Core::Core() :
  iaDifficulty("easy"),
  playersName(2),
  isLoaded(false),
  noMapMenu(0),
  levelIaMenu(0),
  nbMaxIa(600)
{
  this->players = new std::vector<Player *>[2];
  ia = new std::vector<IA *>;
  this->density = 100;
}

Core::~Core()
{

}

bool gameIsPaused(int k, bool newState)
{
  static bool pause = false;

  if (k == 0)
    pause = newState;
  return pause;
}

void	Core::minusLifeP(Player * p)
{
  if (p) {
    if (p->getHp() > 0 && p->getShield() == false)
      p->setHp(p->getHp() - 1);
    if (p->getHp() == 0)
      map->atMap(p->getX(), p->getY())->delPlayer(p);
  }
}

void Core::explodeBomb(Player *player)
{
  std::list<ABomb *> bomb;
  std::list<ABomb *>::iterator it;
  std::list<Player *> pList;

  if (player) {
    bomb = player->getBombToExplode();
    it = bomb.begin();
    player->setActive(false);
    while (it != bomb.end())
      {
	if ((*it)->isReady() == true && (*it)->getOn() == true)
	  {
	    pList = (*it)->explode(this->explose);
	    std::for_each(pList.begin(), pList.end(), std::bind1st(std::mem_fun(&Core::minusLifeP),this));
	    (*it)->getMap()->atMap((*it)->getX(), (*it)->getY())->delObj();
	    it = bomb.erase(it);
	  }
	else
	  it++;
      }
  }
}

void Core::checkIa(IA *ia)
{
  explodeBomb(ia->getPlayer());
  ia->getPlayer()->updateBonus();
}

int Core::run()
{
  if (!this->isLoaded)
  {
    if (this->opt == New)
      this->map = MapGenerator::genMapFromFile(this->fileMapName, this->players, this->split, this->ia, this->nbIa, &playersName, this->iaDifficulty);
    else
      this->map = MapGenerator::genMapFromFile(this->fileMapName, this->players, this->split, this->ia, this->nbIa, &playersName, this->iaDifficulty);
  }
  if (players && (*players)[0] && (*players)[0]->getHp() == 0)
    map->atMap((*players)[0]->getX(), (*players)[0]->getY())->delPlayer((*players)[0]);
  if (split == true && (*players)[1] && (*players)[1]->getHp() == 0)
    map->atMap((*players)[1]->getX(), (*players)[1]->getY())->delPlayer((*players)[1]);
  this->map->setDensity(this->density);
  GameEngine	engine(this->map, this->context, this->shader, *this, this->split);

  if (this->players->size() >= 2) {
    if (!engine.initialize((*this->players)[0], (*this->players)[1], *(this->ia))) {
      std::cerr << "Fail init "<< std::endl;
      return 1;
    }
  }
  else
    if (!engine.initialize((*this->players)[0], 0,
      *ia)) {
      std::cerr << "Fail init "<< std::endl;
      return 1;
    }
  initIa();

  while (engine.update() && (((*this->players)[0] && (*this->players)[0]->getHp() > 0) || ((*this->players)[1] && (*this->players)[1]->getHp() > 0)))
  {
    if (engine.pauseAsked())
    {
      gameIsPaused(0, true);
      while (engine.pauseAsked())
      {
        usleep(100);
        std::for_each(this->players->begin(), this->players->end(),
            std::bind1st(std::mem_fun(&Core::explodeBomb),this));
        std::for_each(this->ia->begin(), this->ia->end(),
            std::bind1st(std::mem_fun(&Core::checkIa),this));
      }
      gameIsPaused(0, false);
    }
    engine.draw(this->explose);
    std::for_each(this->players->begin(),this->players->end(),std::bind1st(std::mem_fun(&Core::explodeBomb),this));
    std::for_each(this->ia->begin(),this->ia->end(),std::bind1st(std::mem_fun(&Core::checkIa),this));
  }
  killThreads();
  engine.disableSplit();
  return (0);
}

int Core::initIa()
{
  Thread *newThread;

  newThread = 0;
  std::vector<IA *>::iterator it;
  for (it = ia->begin(); it != ia->end(); it++)
    {
      newThread = new Thread();
      thread.push_back(newThread);
      newThread->startThread(IA::play, static_cast<void *>(*it));
    }
  return 0;
}

void Core::killThreads()
{
  for (auto &i : thread)
    i->cancel();
}

unsigned int Core::getNbIa() const
{
  return (this->nbIa);
}

void Core::setNbIa(unsigned int nb)
{
  this->nbIa = nb;
}

bool Core::getSplitScreen() const
{
  return (this->split);
}

void Core::setSplitScreen(bool splitScreen)
{
  this->split = splitScreen;
}

eOpt Core::getOpt() const
{
  return (this->opt);
}

void Core::setOpt(eOpt op)
{
  this->opt = op;
}

const std::string &Core::getFileMapName() const
{
  return (this->fileMapName);
}

void Core::setFileMapName(const std::string &file)
{
  this->fileMapName = file;
}

const gdl::SdlContext &Core::getContext() const
{
  return (this->context);
}

void Core::setContext(gdl::SdlContext &cont)
{
  this->context = cont;
}

const gdl::BasicShader &Core::getShader() const
{
  return (this->shader);
}

void Core::setShader(gdl::BasicShader &shad)
{
  this->shader = shad;
}

void Core::setPlayerName(std::string na, int n)
{
  this->playersName[n] = na;
}

std::string Core::getPlayerName(int noPlayer) const
{
  return playersName[noPlayer];
}

void Core::setDensity(Uint dens)
{
  this->density = dens;
}

void Core::setTotalTime(Uint tim)
{
  totalTime = tim;
}

unsigned int Core::getTotalTime() const
{
  return totalTime;
}

Uint	Core::getDensity() const
{
  return (this->density);
}

int	Core::getMaxNbIa(const std::string &map) const
{
  return (MapGenerator::countMapNbIa(map));
}
