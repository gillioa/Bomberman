
#include <iterator>
#include <algorithm>
#include "Core.hpp"
#include "Except.hpp"

bool	checkObjectValidity(const AObject * obj) {
  if (obj->getType() > 2 || obj->getType() < 0)
    throw (CorruptedData());
  return true;
}

bool	checkCaseValidity(const Case * c) {
  if (c->getObj())
    return checkObjectValidity(c->getObj());
  return true;
}

bool	checkMapValidity(const Map * m) {
  if (m->getCMap().size() != m->getWidth() * m->getLength())
    throw (CorruptedData());
  std::for_each(m->getCMap().begin(), m->getCMap().end(), checkCaseValidity);
  return true;
}

bool	checkValidity(Core & core) {
  return true;
  std::vector<Player *>::const_iterator	it;
  checkMapValidity(core.getMap());
  for (it = core.getPlayers()->begin() ; it != core.getPlayers()->end() ; ++it) {
    if ((*it)->getX() < 0 || (*it)->getX() >= core.getMap()->getWidth() ||
	(*it)->getY() < 0 || (*it)->getY() >= core.getMap()->getLength())
      throw (CorruptedData());
  }
  return true;
}
