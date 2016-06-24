#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "menuexception.hh"
#include "scores.hpp"
#include <stdlib.h>


Scores::Scores() : isParsedFile(false)
{
}

void Scores::parseFile(const std::string &filename)
{
  std::ifstream hFile(filename);
  std::string word;
  bool isAName = true;
  std::string name;

  this->scores.clear();

  if (!hFile)
  {
    throw UnreadableFileException();
  }

  while (!hFile.eof())
  {
    hFile >> word;

    if (isAName)
      name = word;
    else
      this->scores[name] = word;

    isAName = !isAName;
  }

  this->isParsedFile = true;
}


const std::map<std::string, std::string> &Scores::getScores() const
{
  if (!this->isParsedFile)
    throw FileNotParsedException();

  return this->scores;
}
