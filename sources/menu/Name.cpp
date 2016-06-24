#include "Name.hh"


Name::Name() : s("___") {

}

Name::Name(const std::string &s)
{
  this->s = s;
  filled();
}

void Name::append(char c)
{
	for (auto &i : this->s)
  {
		if (i == '_') {
			i = c;
			return;
		}
	}
}

void Name::deleteLast()
{
	std::string::iterator it = this->s.end();

	for ( ; it != this->s.begin() ; --it) {
		if (*it != '_') {
			*it = '_';
			return;
		}
	}

	if (*(this->s.begin()) != '_') {
		this->s[0] = '_';
	}
}

std::size_t Name::size() const
{
  std::size_t count = 0;

	for (auto i : this->s) {
		if (i != '_') {
			++count;
		}
	}
	return count;
}

void Name::filled()
{
  if (this->s.size() < 3)
  {
    this->s += std::string(3 - this->s.size(), '_');
  }
}


std::string Name::toStdString() const
{
	return this->s;
}

std::string Name::toStrippedStdString() const
{
  std::string cpy = s;

  while (!cpy.empty() && cpy.back() == '_')
  {
    cpy.pop_back();
  }

  return cpy;
}
