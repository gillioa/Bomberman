#ifndef SERIALIZE_HPP__

# define SERIALIZE_HPP__

#include "Core.hpp"

class Serialize
{
public:
	Serialize(Core &, const std::string &);
	~Serialize();
private:
	void _player(Player &);
	void _map(Map &);
	void _core(Core &);
	void _case(Case &);
	void _object(AObject *);
	void _descWall(AWall &);
	void _descBonus(ABonus &);
	void _IA(IA &);
private:
	unsigned int indentation;
	std::ofstream file;
	bool inArray;
	bool isAK;
	bool shouldComa;
private:
	void keyValue(const std::string &, bool);
	template <typename T>
	void keyValue(const std::string &, T);

	std::string stringOfBool(bool);

	void openBloc(const std::string &);
	void closeBloc();

	void openJson();
	void closeJson();

	void openArray(const std::string &);
	void closeArray();

	void indent();
	void forceAK();
	void forceComa();
	void noAK();
	void coma();
};

#endif // EOF - Serialize.hpp