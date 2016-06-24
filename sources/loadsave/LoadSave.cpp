#include <sstream>

#include "../JsonCPP/json/json.h"
#include "LoadSave.hpp"
#include "jsonexception.hpp"

LoadSave::LoadSave(Core & obj, const std::string & fileName)
{
	/* load the core save */
	_loadCore(obj, fileName);
	/* check if data is valid */
	checkValidity(obj);
}

LoadSave::~LoadSave() { }

void LoadSave::_loadCore(Core & obj, const std::string & fileName) const
{
	Json::Value  root;
	Json::Reader reader;

	std::ifstream test(fileName, std::ifstream::binary);
	bool parsingSuccessful  = reader.parse(test, root);

	if (parsingSuccessful)
	{
		/* json root file */
		Json::Value json_core = root.get("core", 42);

		/* different sections */
		Json::Value json_pla  = json_core.get( "players", "nok");
		Json::Value json_map  = json_core.get( "map"    , "nok");
		Json::Value json_iaj  = json_core.get( "ia"     , "nok");

		/* loading sections */
		_loadPlayers (obj, json_pla);
		_loadMap     (obj, json_map);
		_loadIA      (obj, json_iaj);


		/* set the core */
		obj.setSplitScreen( boolOfString(json_core.get("split", false).asString()));
		for (auto i : *obj.getPlayers() )
			obj.getMap()->setPlayer(i, i->getX(), i->getY());
		for (auto i : *obj.getIA() )
		{
			i->setMap(obj.getMap());
			obj.getMap()->setPlayer(i->getPlayer(), i->getPlayer()->getX(), i->getPlayer()->getY());
		}
	}
	else
	{
		std::cerr  << "Failed to parse configuration\n" << reader.getFormatedErrorMessages(); // Exception
    throw UnParsabledException();
	}
}

void LoadSave::_loadPlayers(Core & obj, Json::Value & json_players ) const
{
	Json::Value::iterator it = json_players.begin();

	/* iterate through the players */
	for (size_t i = 0; i < json_players.size() ; ++i)
	{
		/* set players attributes */
		Player *pl = new Player();
		pl
		->setId           ( DITEM("id")     )
		.setHp            ( DITEM("hp")     )
		.setSpeed         ( DITEM("speed")  )
		.setScore         ( DITEM("score")  )
		.setBombs         ( DITEM("bombs")  )
		.setRange         ( DITEM("range")  )
		.setX             ( DITEM("x")      )
		.setY             ( DITEM("y")      )
		.setName          ( SITEM("name")   )
		.setShield        ( BITEM("shield") )
		.setCanPush       ( BITEM("push")   )
		;

		/* add player to core */
		obj.addPlayer(pl);
		/* go to next player */
		it++;
	}
}

void LoadSave::_loadIA(Core & obj, Json::Value & json_ia ) const
{
	Json::Value::iterator it = json_ia.begin();

	/* iterate through the ia */
	for (size_t i = 0 ; i < json_ia.size() ; ++i )
	{
		Player * pl = new Player();
		Json::Value playerIAJson = (*it).get("player", "ok");
	
		/* load ia's players with attributes */
		_loadIAPlayer(*pl, playerIAJson);
		IA * nia = new IA(pl, 0);

		/* set the new IA attributes */
		nia
		->setIntelligency  (  DITEM("intel")    )
		.setSpeed          (  DITEM("speed")    )
		.setAttack         (  DITEM("attack")   )
		.setDefence        (  DITEM("defence")  )
		.setFarming        (  DITEM("farming")  )
		.setUsingBonus     (  DITEM("useBonus") )
		;

		/* add ia to the core */
		obj.setIA(nia);
		/* go to next ia */
		it++;
	}
}

void LoadSave::_loadIAPlayer(Player & obj, Json::Value & object) const
{
	/* set player attributes for the ia */
	obj
	.setId      ( DITEMN("id")     )
	.setHp      ( DITEMN("hp")     )
	.setX       ( DITEMN("x")      )
	.setY       ( DITEMN("y")      )
	.setName    ( SITEMN("name")   )
	.setRange   ( DITEMN("range")  )
	.setBombs   ( DITEMN("bombs")  )
	.setScore   ( DITEMN("score")  )
	.setShield  ( BITEMN("shield") )
	.setCanPush ( BITEMN("push")   )
	.setSpeed   ( DITEMN("speed")  )
	;
}

void LoadSave::_loadMap(Core & obj, Json::Value & json_map) const
{
	Map * mmap = new Map();

	/* set map attributes -> checked after laoding */
	mmap
	->setWidth( intOfString(json_map.get("width", 0).asString()) )
	.setLength( intOfString(json_map.get("length", 0).asString()) );

	/* set map cells */
	Json::Value json_cases = json_map.get("cases", 0);
	_loadCase( *mmap, json_cases);

	/* set the map to the core */
	obj.setMap(mmap);
}

void LoadSave::_loadCase(Map & obj, Json::Value & json_cases) const
{
	Json::Value::iterator it = json_cases.begin();
	std::vector<Case *> v;

	for (size_t i = 0 ; i < json_cases.size() ; ++i)
	{
		Case * c = new Case();
		Json::Value object_json = (*it).get("object", "ok");

		/* set cell attributes */
		c
		->setX( DITEM("x") )
		.setY( DITEM("y") )
		.setIsWalk( BITEM("canWalk") )
		.setValue( DITEM("value") )
		.setObj(0);

		/* if there is an object on the cell -> set it */
		if (!object_json.isString())
			c->setObj( _getCaseObj(*c, object_json));

		v.push_back(c);
		/* next cell */
		++it;
	}
	/* set the cells to the map */
	obj.setMapVector(v);
}

AObject * LoadSave::_getCaseObj(Case & ccase, Json::Value & object) const
{
	std::string type = object.get("type", "none").asString();

	/* build object if correct type, otherwise return 0 */
	if (type.compare("wall") == 0)
		return _buildWall(ccase, object);
	else if (type.compare("bonus") == 0)
		return _buildBonus(ccase, object);
	return 0;
}

AObject * LoadSave::_buildBonus(Case & src, Json::Value & object) const
{
	ABonus * bonus = new ABonus(src.getX(), src.getY(), Random);

	bonus
	->setSpeed     ( DITEMN("speed")     )
	.setScore      ( DITEMN("score")     )
	.setNbBombs    ( DITEMN("nbBombs")   )
	.setRange      ( DITEMN("range")     )
	.setTimeLimit  ( DITEMN("timeLimit") )
	.setHp         ( DITEMN("hp")        )
	.setType       ( static_cast<bonusType>(DITEMN("bonusType")))
	;

	return bonus;
}

AObject * LoadSave::_buildWall(Case & src, Json::Value & object) const
{
	std::string wallType = object.get("wallType", "Unbreakable").asString();
	AWall * wall = new AWall(src.getX(), src.getY(), Wall);

	/* build a wall */
	if (wallType.compare("Unbreakable") == 0)
		wall->setType(Unbreakable);
	else
		wall->setType(Breakable);
	return wall;
}

/* some tools */
double LoadSave::intOfString(const std::string & str) const
{
	/* get an int from a string */
	std::istringstream buffer(str);
	double value;
	buffer >> value;

	return value;
}

bool LoadSave::boolOfString(const std::string & str) const
{
	/* get a boolean from a string */
	if (str.compare("true") == 0)
		return true;
	return false;
}
