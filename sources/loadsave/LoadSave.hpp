#ifndef LOAD_SAVE_HPP

# define LOAD_SAVE_HPP

#include "../JsonCPP/json/json.h"
#include "Core.hpp"

void checkValidity(Core &);

class LoadSave
{
public:
	LoadSave(Core &, const std::string &);
	~LoadSave();
private: /* sections loading */
	void _loadCore     (Core &   , const std::string &) const;
	void _loadPlayers  (Core &   , Json::Value &)       const;
	void _loadMap      (Core &   , Json::Value &)       const;
	void _loadIA       (Core &   , Json::Value &)       const;
	void _loadIAPlayer (Player & , Json::Value &)       const;
	void _loadCase     (Map &    , Json::Value &)       const;
private: /* tools */
	double intOfString (const std::string &) const;
	bool   boolOfString(const std::string &) const;
private: /* object builds */
	AObject * _getCaseObj(Case &, Json::Value &) const;
	AObject * _buildBonus(Case &, Json::Value &) const;
	AObject * _buildWall (Case &, Json::Value &) const;
};

#define SITEM(x) (*it).get(x, "ok").asString()
#define DITEM(x) intOfString(SITEM(x))
#define BITEM(x) boolOfString(SITEM(x))

#define SITEMN(x) object.get(x, "ok").asString()
#define DITEMN(x) intOfString(SITEMN(x))
#define BITEMN(x) boolOfString(SITEMN(x))

#endif // EOF - LoadSave.hpp
