//
// Except.hpp for Bomberman in /home/courtu_r/BOMBERMAN/blowshitup/Sources/Except
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Thu May 15 09:59:00 2014 courtu_r
// Last update Fri Jun 13 14:01:58 2014 courtu_r
//

#include <iostream>
#include <stdexcept>

#ifndef EXCEPT
# define EXCEPT

class	AExcept : public std::runtime_error
{
public:
  AExcept() : std::runtime_error("Exception raised") {};
  virtual ~AExcept() throw() {};
  virtual void printErr() const throw() {};
};

class	LoadErr : public AExcept
{
  std::string	file;
public:
  LoadErr(std::string file) {
    this->file = file;
  }
  ~LoadErr() throw() {};
  void	printErr() const throw() {
    std::cerr << "Failed to load file. File was : [" << this->file << "]" << std::endl;
  }
};

class TimerErr : public AExcept
{
public:
  TimerErr() {};
  ~TimerErr() throw() {};
  void	printErr() const throw() {
    std::cerr << "Failed to init a timer." << std::endl;
  }
};

class CorruptedData : public AExcept
{
public:
  CorruptedData() {};
  ~CorruptedData() throw() {};
  void	printErr() const throw() {
    std::cerr << "Save file has corrupted datas." << std::endl;
  }
};

class ThreadExcept : public AExcept
{
public:
  ThreadExcept() {};
  ~ThreadExcept() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : Cannot start thread." << std::endl;
  }
};

class CannotPlacePlayer2 : public AExcept
{
public:
  CannotPlacePlayer2() {};
  ~CannotPlacePlayer2() throw() {};
  void	printErr() const throw() {
    std::cerr << "Cannot place the second player in the map." << std::endl;
  }
};

class BadMapSize : public AExcept
{
public:
  BadMapSize() {};
  ~BadMapSize() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : size map is not correct." << std::endl;
  };
};

class BadCharMap : public AExcept
{
public:
  BadCharMap() {};
  ~BadCharMap() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : invalide character in map file." << std::endl;
  }
};

class CorruptedMap : public AExcept
{
public:
  CorruptedMap() {};
  ~CorruptedMap() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : Map corrupted." << std::endl;
  }
};

class BadFile : public AExcept
{
public:
  BadFile() {};
  ~BadFile() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : MapGenerator : Cannot open file." << std::endl;
  }
};

class SizeNotSet : public AExcept
{
public:
  SizeNotSet() {};
  ~SizeNotSet() throw() {};
  void	printErr() const throw() {
    std::cerr << "Stop : MapGenerator : Size not set, probably an empty file." << std::endl;
  }
};

class SizeTooBig : public AExcept
{
 public:
  SizeTooBig() {};
  ~SizeTooBig() throw() {};
  void	printErr() const throw() {
    std::cout << "Stop : size is too big to generate random map." << std::endl;
  }
};

class SizeTooSmall : public AExcept
{
  unsigned int nb;
 public:
  SizeTooSmall(unsigned int val) { this->nb = val; }
  ~SizeTooSmall() throw() {};
  void	printErr() const throw() {
    std::cout << "Stop : size is too small to generate random map for " << this->nb << " players." << std::endl;
  }
};

#endif /*EXCEPT*/
