#ifndef TEXT_HH
#define TEXT_HH

#include <list>
#include "image.hh"

class Text {

public:

	Text(gdl::Texture *font);
	Text();

	void constructFor2d(const std::string &text, int x, int y);

	void draw(gdl::AShader &shader, const glm::vec3 &scale = glm::vec3(1, 1, 1));

	void setFont(gdl::Texture *font);

    virtual ~Text();

    void reset();


private:
	std::list<gdl::Geometry*> geos;
	gdl::Texture *font;
};

#endif
