
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "RandomMapGenerator.hpp"
#include "Except.hpp"

Uint RandomMapGenerator::GenerateRandomNumber(Uint min, Uint max) const
{
  Uint value;
  static int i;

  if (i == 0)
    srand(time(NULL));
  i++;
  while ((value = rand() % (max + 1)) < min);
  return (value);
}

void RandomMapGenerator::DeterminePosition(Uint nbPos, std::vector<Uint> pos, Uint sizeX, Uint sizeY, Uint divisor, Uint stat)
{
  if (nbPos != 1)
    {
      std::vector<Uint> pos1;
      std::vector<Uint> pos2;
      if (stat % 2 == 0)
	{
	  pos1.push_back(pos[0]);
	  pos1.push_back(pos[1]);
	  pos1.push_back(pos[0] + ((sizeX - 1) / divisor) - 1);
	  pos1.push_back(pos[3]);
	  pos2.push_back(pos1[2] + 1);
	  pos2.push_back(pos[1]);
	  pos2.push_back(pos[2]);
	  pos2.push_back(pos[3]);
	}
      else
	{
	  pos1.push_back(pos[0]);
	  pos1.push_back(pos[1]);
	  pos1.push_back(pos[2]);
	  pos1.push_back(pos[1] + (sizeY / divisor) - 1);
	  pos2.push_back(pos[0]);
	  pos2.push_back(pos1[3] + 1);
	  pos2.push_back(pos[2]);
	  pos2.push_back(pos[3]);
	}
      stat++;
      if (stat % 2 == 0)
      	divisor *= 2;
      DeterminePosition((nbPos / 2), pos1, sizeX, sizeY, divisor, stat);
      DeterminePosition((nbPos / 2) + (nbPos % 2), pos2, sizeX, sizeY, divisor, stat);
      return ;
    }
  Uint posX = GenerateRandomNumber(pos[0], pos[2]);
  Uint posY = GenerateRandomNumber(pos[1], pos[3]);
  this->vec[posX * (sizeY + 1) + (posY + posX)] = 'P';
  Uint def;
  def = checkPosX(posX, posY, sizeY + 1, pos);
  if (def == 1)
    this->vec[(posX - 1) * (sizeY + 1) + (posY + (posX - 1))] = '.';
  else
    this->vec[(posX + 1) * (sizeY + 1) + (posY + (posX + 1))] = '.';
  def = checkPosY(posX, posY, sizeY + 1, pos);
  if (def == 1)
    this->vec[posX * (sizeY + 1) + ((posY - 1) + posX)] = '.';
  else
    this->vec[posX * (sizeY + 1) + ((posY + 1) + posX)] = '.';
}

Uint RandomMapGenerator::checkPosX(Uint x, Uint y, Uint ref, std::vector<Uint> pos) const
{
  Uint front = 0;
  Uint bottom = 0;

  if (x - 1 >= pos[0])
    front++;
  if (x + 1 >= pos[2])
    bottom++;
  if (this->vec[(x + 1) * ref + y + (x + 1)] == 'L')
    bottom++;
  if (this->vec[(x - 1) * ref + y + (x - 1)] == 'L')
    front++;
  if (front != 2 && bottom != 2)
    return (0);
  else if (front == bottom)
    return (GenerateRandomNumber(1, 2));
  if (front > bottom)
    return (1);
  return (2);
}

Uint RandomMapGenerator::checkPosY(Uint x, Uint y, Uint ref, std::vector<Uint> pos) const
{
  Uint right = 0;
  Uint left = 0;

  if (y - 1 >= pos[1])
    left++;
  if (y + 1 >= pos[3])
    right++;
  if (this->vec[x * ref + (y - 1) + x] == 'L')
    left++;
  if (this->vec[x * ref + (y + 1) + x] == 'L')
    right++;
  if (left != 2 && right != 2)
    return (0);
  else if (right == left)
    return (GenerateRandomNumber(1, 2));
  if (left > right)
    return (1);
  return (2);
}

bool RandomMapGenerator::GenerateFile()
{
  Uint i;
  Uint j;
  Uint nbPosition = this->nPlayer;
  std::vector<Uint> pos;

  if (this->sX > 10000 || this->sY > 10000)
    throw (SizeTooBig());
  else if (this->sX < ((nbPosition * 3)) || this->sY < ((nbPosition * 3)))
    throw (SizeTooSmall(nPlayer));
  for (i = 0; i < this->sY + 2; i++)
    this->vec.push_back('x');
  for (i = 0; i < this->sX; i++) {
    this->vec.push_back('x');
    for (j = 0; j < this->sY; j++)
      this->vec.push_back('L');
    this->vec.push_back('x');
  }
  for (i = 0; i < this->sY + 2; i++)
    this->vec.push_back('x');
  pos.push_back(1);
  pos.push_back(1);
  pos.push_back(this->sX);
  pos.push_back(this->sY);
  DeterminePosition(nbPosition, pos, this->sX + 1, this->sY, 2, 0);
  for (i = 0; i < vec.size() - 1; i++) {
    if (this->vec[i] == 'L') {
      if (GenerateRandomNumber(0, 4) == GenerateRandomNumber(0, 4))
      	this->vec[i] = 'x';
      else if (GenerateRandomNumber(0, 2) == GenerateRandomNumber(0, 2))
      	this->vec[i] = '.';
    }
  }
  std::ofstream file(this->fileName.c_str());
  if (!file.is_open())
    throw (BadFile());
  file << (this->sX + 2) << "x" << (this->sY + 2) << std::endl;
  for (i = 0; i < (this->sX + 2) * (this->sY + 2); i++) {
    if (i % (this->sY + 2) == 0 && i != 0)
      file << std::endl;
    file << this->vec[i];
  }
  file << std::endl;
  return (true);
}

void RandomMapGenerator::setFileName(std::string const &name)
{
  this->fileName = name;
}

void RandomMapGenerator::setNbPlayer(Uint nb)
{
  this->nPlayer = nb;
}

void RandomMapGenerator::setSizeX(Uint nb)
{
  this->sX = nb;
}

void RandomMapGenerator::setSizeY(Uint nb)
{
  this->sY = nb;
}
