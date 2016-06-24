
#include "IA.hpp"

IA::IA(Player * player, Map * map, const std::string & file)
{
  this->p = player;
  this->initStat();
  this->loadStyle(file);
  this->m = map;
}

IA::IA(Player * player, Map * map)
{
  this->m = map;
  this->p = player;
  this->initStat();
}

void	*IA::play(void * elem) {
  IA	*ia = static_cast<IA*>(elem);
  while (ia->p && ia->p->getHp() > 0) {
    ia->move();
    usleep(50000);
    if (ia->p && ia->p->getHp() >0)
      ia->bomber();
    while (gameIsPaused(-1,true))
      usleep(200);
  }
  ia->m->removePlayer(ia->p, ia->p->getX(), ia->p->getY());
  return (NULL);
}

IA::~IA() {}

bool	IA::defaultMove() {
  bool	t = false;

  if (this->intel >= 1 && this->p->getBombs() > 0) {
    if (this->p->getX() < (this->m->getWidth() / 2) &&
	this->safePow(this->p->getX() + 1.0, this->p->getY()) == true)
      t = this->p->moveCaseDown(this->m);
    if (this->p->getX() > (this->m->getWidth() / 2) && t == false &&
	this->safePow(this->p->getX() - 1.0, this->p->getY()) == true)
      t = this->p->moveCaseUp(this->m);
    if (this->p->getY() < (this->m->getLength() / 2) && t == false &&
	this->safePow(this->p->getX(), this->p->getY() + 1.0) == true)
      t = this->p->moveCaseRight(this->m);
    if (t == false)
      if (this->safePow(this->p->getX(), this->p->getY() - 1.0) == true &&
	  this->p->moveCaseLeft(this->m) == false &&
	  this->safePow(this->p->getX(), this->p->getY() + 1.0) == true)
	this->p->moveCaseRight(this->m);
  }
  return true;
}

bool	IA::bonusApproach() {
  bool	t = false;

  if (this->intel > 6 || this->farming > 4)
    t = this->bonusApproachPow();
  else if (this->intel > 3 || this->farming > 1)
    t = this->bonusApproachSq();
  return (t);
}

bool	IA::playerApproach() {
  bool	t = false;

  if (this->intel > 4 || this->attack > 6) {
    t = this->playerApproachPow();
    return (t);
  }
  else
    return (false);
}

bool	IA::dodge() {
  if (this->intel > 2 || this->defence > 2)
    return (this->dodgePow());
  return (false);
}

void	IA::move() {
  bool  (IA::*fn_ptr[4])();
  unsigned int i = 0;

  fn_ptr[0] = &IA::dodge;
  fn_ptr[1] = &IA::playerApproach;
  fn_ptr[2] = &IA::bonusApproach;
  fn_ptr[3] = &IA::defaultMove;
  while (i < 4) {
    if ((this->*fn_ptr[i])() == true)
      return ;
    i += 1;
  }
}

void	IA::bomber() {
  if (this->attack > 1 || this->intel > 2)
    if (this->fleeBomb() == false)
      this->wallBomb();
}

void	IA::initStat() {
  this->intel = 4;
  this->speed = 5;
  this->attack = 4;
  this->defence = 5;
  this->farming = 4;
  this->useBonus = 5;
}

IA &	IA::setIntelligency(int v) {
  this->intel = v;
  return *this;
}

IA &	IA::setSpeed(int v) {
  this->speed = v;
  return *this;
}

IA &	IA::setAttack(int v) {
  this->attack = v;
  return *this;
}

IA &	IA::setDefence(int v) {
  this->defence = v;
  return *this;
}

IA &	IA::setFarming(int v) {
  this->farming = v;
  return *this;
}

IA &	IA::setUsingBonus(int v) {
  this->useBonus = v;
  return *this;
}

int	IA::getItemValue(const std::string & line, int val) const {
  return ((line[val] - '0'));
}

const std::vector<std::string> IA::getRefTab() const
{
  std::vector<std::string> t;
  t.push_back("Intelligency=");
  t.push_back("Speed=");
  t.push_back("Attack=");
  t.push_back("Defence=");
  t.push_back("Farming=");
  t.push_back("Using bonus=");
  return (t);
}

void	IA::setItem(const std::string & line)
{
  const std::vector<std::string> t = getRefTab();

  IA &  (IA::*fn_ptr[6])(int);
  fn_ptr[0] = &IA::setIntelligency;
  fn_ptr[1] = &IA::setSpeed;
  fn_ptr[2] = &IA::setAttack;
  fn_ptr[3] = &IA::setDefence;
  fn_ptr[4] = &IA::setFarming;
  fn_ptr[5] = &IA::setUsingBonus;

  unsigned int   i = 0;
  while (i < t.size()) {
    if (t[i].compare(0, t[i].length(), line, 0, (line.length() - 1)) == 0)
      (this->*fn_ptr[i])(getItemValue(line, t[i].length()));
    i += 1;
  }
}

bool    IA::parseIAScriptFile(const std::string & file)
{
  std::string sLine = "";
  std::ifstream infile;
  unsigned int i = 0;

  infile.open(file.data());
  while (!infile.eof() && ++i < 100)
    {
      getline(infile, sLine);
      setItem(sLine);
    }
  infile.close();
  return (true);
}

bool	IA::loadStyle(const std::string & file) {
  parseIAScriptFile(file);
  return (true);
}

int	IA::getIntel() const {
  return (this->intel);
}

int	IA::getSpeed() const {
  return (this->speed);
}

int	IA::getAttack() const {
  return (this->attack);
}

int	IA::getDefence() const {
  return (this->defence);
}

int	IA::getFarming() const {
  return (this->farming);
}

int	IA::getUseBonus() const {
  return (this->useBonus);
}

void	IA::setMap(Map * map) {
  this->m = map;
}

Player *IA::getPlayer() {
  return (this->p);
}

Map *	IA::getMap() const {
  return this->m;
}
