#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Except.hpp"
#include "Map.hpp"
#include "AWall.hpp"
#include "MapGenerator.hpp"

Map * MapGenerator::genMapFromFile(const std::string &fileName, std::vector<Player *> *players, bool splitScreen, std::vector<IA *> *ia, int nbIa, std::vector<std::string> *vec, const std::string &diff)
{
  return genMapFromFile(fileName.c_str(), players, splitScreen, ia, nbIa, vec, diff);
}

static std::vector<int> getSizeFromLine(const std::string &line)
{
  std::vector<int> k;
  std::string s = line;
  std::string delimiter = "x";
  std::string token;
  size_t pos = 0;

  while ((pos = s.find(delimiter)) != std::string::npos)
    {
      token = s.substr(0, pos);
      s.erase(0, pos + delimiter.length());
    }
  int x;
  int y;
  std::istringstream (token) >> x;
  std::istringstream (s) >> y;

  if (!x || x <= 0 || !y || y <= 0)
    throw (BadMapSize());
  k.push_back(x);
  k.push_back(y);

  return k;
}

static Case * getCaseFromLetter(char c, int x, int y, std::vector<Player *> *players, bool split, std::vector<IA *> *ia, int nbIa, std::vector<std::string> *vec, int &index, const std::string &IADiff, int &i)
{
  bool canWalk;
  Case * newCase;
  AObject *obj= 0;
  Player *player;
  IA *iaPlayer;

  std::map<eEventGdl, eEventBind> bind;
  if (c == 'L')
    {
      obj = new AWall(x, y, Wall, Breakable);
      canWalk = false;
    }
  else if (c == 'x')
    {
      obj = new AWall(x, y, Wall, Unbreakable);
      canWalk = false;
    }
  else if (c == '.')
    canWalk = true;
  else if (c == 'P')
    {
      if (i == 0)
	{
	  player = new Player(i, (*vec)[0], static_cast<double>(x), static_cast<double>(y), bind);
	  players->push_back(player);
	}
      else if (i == nbIa + 1 && split == true)
	{
	  player = new Player(i, (*vec)[1], static_cast<double>(x), static_cast<double>(y), bind);
	  players->push_back(player);
	  index++;
	}
      else if (i <= nbIa)
	{
	  player = new Player(i, "IA", static_cast<double>(x), static_cast<double>(y), bind);
	  iaPlayer = new IA(player, 0, "IAScript/" + IADiff + ".ia");
	  ia->push_back(iaPlayer);
	}
      canWalk = true;
      i++;
    }
  else
    throw (BadCharMap());
  newCase = new Case(x, y, canWalk);
  newCase->setObj(obj);
  return newCase;
}

Map * MapGenerator::genMapFromFile(const char fileName[], std::vector<Player *> *players, bool splitScreen, std::vector<IA *> *ia, int nbIa, std::vector<std::string> *vec, const std::string & diff)
{
  std::string line;
  std::ifstream file(fileName);
  std::vector<Case *> vectorCase;
  std::vector<std::string> v;
  bool sizeIsSet = false;
  std::vector<int> size;
  int x, y;
  Map *map;
  int index = 0;
  int i = 0;

  x = 0;
  y = 0;
  if (file.is_open())
    {
      while (getline( file,line ))
	{
	  if (!sizeIsSet)
	    {
	      size = getSizeFromLine(std::string(line));
	      sizeIsSet = true;
	    }
	  else
	    {
	      if (int(line.size()) != size[1]) {
		throw (CorruptedMap());
	      }
	      y = 0;
	      for ( std::string::iterator it= line.begin(); it!=line.end(); ++it)
		{
		  vectorCase.push_back(getCaseFromLetter(*it, x, y, players, splitScreen, ia, nbIa, vec, index, diff, i));
		  y++;
		}
	      x++;
	    }
	  v.push_back(line);
	}
      file.close();
    }
  else
    throw (BadFile());
  if (splitScreen == false)
    players->push_back(NULL);
  if (index == 0 && splitScreen == true)
    throw (CannotPlacePlayer2());
  else if (!sizeIsSet)
    throw (SizeNotSet());
  else if (x != size[0])
    throw (CorruptedMap());
  file.close();
  map = new Map(size[1], size[0], vectorCase);
  if (players->size() > 0)
    {
      for (auto &i : *players) {
	if (i)
	  map->setPlayer(i, i->getX(), i->getY());
      }
    }
  if (ia->size() > 0)
    {
      for (auto &i : *ia)
      	map->setPlayer(i->getPlayer(), i->getPlayer()->getX(), i->getPlayer()->getY());
      for (auto &i : *ia)
      	i->setMap(map);
    }
  return (map);
}

int MapGenerator::countMapNbIa(const std::string &map)
{
  std::ifstream file(map.c_str());
  int nbrIa = 0;
  std::string line;

  if (file.is_open())
    {
      while (getline( file,line ))
	{
	  for ( std::string::iterator it= line.begin(); it!=line.end(); ++it)
	    {
	      if ((*it) == 'P')
		nbrIa++;
	    }
	}
    }
  file.close();
  if (nbrIa - 2 < 0)
    throw (CorruptedMap());
  return (nbrIa - 2);
}
