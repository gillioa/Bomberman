#pragma once


#include <iostream>
#include <string>

class Name
{

public:
	Name(const std::string &s);
	Name();
	void append(char c);
	std::size_t size() const;
	std::string toStdString() const;
	void deleteLast();
  std::string toStrippedStdString() const;
  void filled();


private:
	std::string s;
};
