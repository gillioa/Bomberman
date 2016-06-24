#ifndef MAP_GENERATOR_HPP__

# define MAP_GENERATOR_HPP__

#include <string>
#include <vector>
#include "Map.hpp"
#include "IA.hpp"

class MapGenerator
{
public:
  static Map * genMapFromFile(const std::string &file, std::vector<Player *> *, bool, std::vector<IA *> *, int, std::vector<std::string> *, const std::string &);
  static Map * genMapFromFile(const char [], std::vector<Player *> *, bool, std::vector<IA *> *, int, std::vector<std::string> *, const std::string &);
  static int countMapNbIa(const std::string &);
};

#endif // ! EOF - MapGenerator.hpp
