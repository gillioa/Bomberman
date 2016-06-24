#include <string>

#include "Core.hpp"
#include "Serialize.hpp"

Serialize::Serialize(Core &obj, const std::string &fileName) :
indentation(0),
inArray(false),
isAK(false),
shouldComa(false)
{
	file.open(fileName);
	if (file.is_open())
	{
		openJson();
		{
			_core(obj);
		}
		closeJson();
	}
}

Serialize::~Serialize()
{
	file.close();
}

void Serialize::_core(Core & obj)
{
	std::vector<Player *> *v;

	v = obj.getPlayers();
	openBloc("core");
	{
		keyValue( "density" , obj.getDensity() );
		keyValue( "split" , obj.getSplitScreen() );
		keyValue( "opt" , obj.getOpt() );
		forceAK();
		/* players */

		openArray("players");
		{
			for (auto &i : *v)
			{
				if (i)
				{
					_player(*i);
					shouldComa = true;
				}
			}
			shouldComa = false;
		}
		closeArray();

		file << std::endl;

		/* map */
		coma();
		inArray = false;
		openBloc("map");
		{
			keyValue("width", obj.getMap()->getWidth());
			keyValue("length", obj.getMap()->getLength());
			_map(*(obj.getMap()));
		}
		closeBloc();

		/* ia */
		forceAK();
		openArray("ia");
		{
			shouldComa = false;
			std::vector<IA *> * via = obj.getIA();
			for (auto &i : *via)
			{
				_IA(*i);
				shouldComa = true;
				forceAK();
				inArray = true;
			}
			shouldComa = false;
		}
		closeArray();
	}
	closeBloc();
}

void Serialize::_player(Player & obj)
{
	openBloc("players");
	{
		keyValue( "id", obj.getId() );
		keyValue( "hp", obj.getHp() );
		keyValue( "x", obj.getX() );
		keyValue( "y", obj.getY() );
		keyValue( "name", obj.getName() );
		keyValue( "range", obj.getRange() );
		keyValue( "bombs", obj.getBombs() );
		keyValue( "score", obj.getScore() );
		keyValue( "shield", obj.getShield() );
		keyValue( "push", obj.getCanPush() );
		keyValue( "speed", obj.getSpeed() );
		keyValue( "dead", obj.isDead() );
	}
	closeBloc();
}

void Serialize::_IA(IA & objP)
{
	forceAK();
	openBloc("ias");
	{
		keyValue( "intel", objP.getIntel() );
		keyValue( "speed", objP.getSpeed() );
		keyValue( "attack", objP.getAttack() );
		keyValue( "defence", objP.getDefence() );
		keyValue( "farming", objP.getFarming() );
		keyValue( "useBonus", objP.getUseBonus() );
		Player &obj = *(objP.getPlayer());
		{
			inArray = false;
			shouldComa = false;
			file << "," << std::endl;
			openBloc("player");
			{
				keyValue( "id", obj.getId() );
				keyValue( "hp", obj.getHp() );
				keyValue( "x", obj.getX() );
				keyValue( "y", obj.getY() );
				keyValue( "name", obj.getName() );
				keyValue( "range", obj.getRange() );
				keyValue( "bombs", obj.getBombs() );
				keyValue( "score", obj.getScore() );
				keyValue( "shield", obj.getShield() );
				keyValue( "push", obj.getCanPush() );
				keyValue( "speed", obj.getSpeed() );
				keyValue( "dead", obj.isDead() );
			}
			closeBloc();
		}
	}
	closeBloc();
}

void Serialize::_map(Map & obj)
{
	std::vector<Case *> v = obj.getMap();

	openArray("cases");
	{
		for (auto &i : v)
		{
			_case(*i);
			forceComa();
		}
	}
	closeArray();
}

void Serialize::_case(Case & obj)
{
	inArray = true;
	openBloc("");
	{
		keyValue("x", obj.getX() );
		keyValue("y", obj.getY() );
		keyValue("value", obj.getValue() );
		keyValue("canWalk", obj.canWalk() );

		if (obj.getObj())
		{
			inArray = false;
			shouldComa = false;
			file << "," << std::endl;
			openBloc("object");
			{
				_object(obj.getObj());
			}
			closeBloc();
			inArray = true;
		}
	}
	closeBloc();
}

void Serialize::_object(AObject * obj)
{
	AWall *testWall = 0;
	ABonus *testBonus = 0;

	testBonus = dynamic_cast<ABonus *>(obj);
	testWall = dynamic_cast<AWall *>(obj);

	if (testBonus)
		_descBonus(*testBonus);
	else if (testWall)
		_descWall(*testWall);
}

void Serialize::_descBonus(ABonus & obj)
{
	keyValue( "type" , "bonus");
	/* specs */
	keyValue( "hp", obj.getHp() );
	keyValue( "speed", obj.getSpeed() );
	keyValue( "score", obj.getScore() );
	keyValue( "nbBombs", obj.getNbBombs() );
	keyValue( "range", obj.getRange() );
	keyValue( "timeLimit", obj.getTimeLimit() );
	keyValue( "bonusType", obj.getType() );
}

void Serialize::_descWall(AWall & obj)
{
	keyValue( "type" , "wall");
	/* specs */
	if (obj.getWallType() == Breakable)
		keyValue( "wallType", "Breakable");
	else
		keyValue( "wallType", "Unbreakable");
}

/* tools */

void Serialize::keyValue(const std::string & key, bool value)
{
	keyValue(key, stringOfBool(value));
}

template <typename T>
void Serialize::keyValue(const std::string & key, T value)
{
	if (isAK)
		file << "," << std::endl;
	indent();
	file << "\"" << key << "\"" << "\t:\t" << "\"" << value << "\"";
	isAK = true;
}

void Serialize::openBloc(const std::string &blocName)
{
	if (shouldComa)
		coma();
	indent();
	if (!inArray)
	{
		file << "\"" << blocName << "\"" << ":" << std::endl;
		indent();
	}
	file << "{" << std::endl;
	indentation += 1;
	noAK();
}

void Serialize::closeBloc()
{
	indentation -= 1;
	if (isAK)
		file << std::endl;
	indent();
	file << "}" << std::endl;
	isAK = false;
}

void Serialize::openArray(const std::string &arrayName)
{
	if (isAK)
	{
		file << "," << std::endl;
	}
	indent();
	file << "\"" << arrayName << "\"" << ":" << std::endl;
	indent();
	file << "[" << std::endl;
	indentation += 1;
	inArray = true;
}

void Serialize::closeArray()
{
	indentation -= 1;
	indent();
	file << "]";
}

void Serialize::indent()
{
	for (unsigned int i = 0; i < indentation; ++i)
		file << "\t";
}

std::string Serialize::stringOfBool(bool v)
{
	if (v)
		return "true";
	return "false";
}

void Serialize::openJson()
{
	file << "{" << std::endl;
	indentation += 1;
}

void Serialize::closeJson()
{
	file << "}" << std::endl;
	indentation -= 1;
}

void Serialize::forceAK()
{
	isAK = true;
}

void Serialize::noAK()
{
	isAK = false;
}

void Serialize::coma()
{
	indent();
	file << "," << std::endl;
}

void Serialize::forceComa()
{
	shouldComa = true;
}