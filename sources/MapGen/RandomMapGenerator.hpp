#ifndef RANDOMMAPGENERATOR_HPP_
#define RANDOMMAPGENERATOR_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

typedef unsigned int Uint;

class RandomMapGenerator
{
private:
  Uint GenerateRandomNumber(Uint, Uint) const;
  void DeterminePosition(Uint, std::vector<Uint>, Uint, Uint, Uint, Uint);
  Uint checkPosX(Uint, Uint, Uint, std::vector<Uint>) const;
  Uint checkPosY(Uint, Uint, Uint, std::vector<Uint>) const;
  std::vector<char> vec;
  std::string fileName;
  Uint nPlayer;
  Uint sX;
  Uint sY;
public:
  bool GenerateFile();
  void setFileName(std::string const &);
  void setSizeX(Uint);
  void setSizeY(Uint);
  void setNbPlayer(Uint);
};

#endif
