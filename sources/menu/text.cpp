#include "text.hh"

Text::Text(gdl::Texture *font) : font(font) {
}

Text::Text() {
}

void Text::reset() {
	for (auto *i : this->geos) {
		delete i;
	}
	this->geos.clear();
}


void Text::constructFor2d(const std::string &text, int x, int y) {
	const float size = 1632.0f / 68.0f;
	float offset = 0.0f;
	std::size_t pos = 0;
	int xtmp;
	int ytmp;

	float percentOfLetter = (size) / 1632.0f;

	for (auto &i : text) {
		gdl::Geometry *letterGeo = new gdl::Geometry;

		letterGeo->setColor(glm::vec4(1, 1, 1, 1));

		xtmp = (x + (size * pos));
		ytmp = y;

		letterGeo->pushVertex(glm::vec3(xtmp, y, 0));
		letterGeo->pushVertex(glm::vec3(xtmp + size, ytmp, 0));
		letterGeo->pushVertex(glm::vec3(xtmp + size, ytmp + size, 0));
		letterGeo->pushVertex(glm::vec3(xtmp, ytmp + (size), 0));

		pos++;


		if (i >= 'a' && i <= 'z') {
			offset = (static_cast<float>((i - 'a') * size) / 1632.0f);
		} else if (i >= 'A' && i <= 'Z') {
			offset = (static_cast<float>((i - 'A' + 26) * size) / 1632.0f);
		} else if (i == ' ') {
			offset = -1.0;
		} else if (i == '_') {
			offset = (static_cast<float>((66) * size) / 1632.0f);
		} else if (i >= '0' && i <= '9') {
			offset = (static_cast<float>((i - '0' + 52) * size) / 1632.0f);
		} else if (i == '%') {
      offset = (static_cast<float>((67) * size) / 1632.0f);
		} else {
			throw "NonImplementedError";
    }

		letterGeo->pushUv(glm::vec2(offset, 0.9f));
		letterGeo->pushUv(glm::vec2(offset + (percentOfLetter) , 0.9f));
		letterGeo->pushUv(glm::vec2(offset + (percentOfLetter) , 0.1f));
		letterGeo->pushUv(glm::vec2(offset, 0.1f));

		letterGeo->build();

		this->geos.push_back(letterGeo);

	}

}

void Text::draw(gdl::AShader &shader, const glm::vec3 &scale) {
	glm::mat4 transform(1);

	transform = glm::scale(transform, scale);

	shader.bind();
	this->font->bind();

	for (auto &i : this->geos) {
		i->draw(shader, transform, GL_QUADS);
	}
}

Text::~Text()
{
	for (auto *i : this->geos) {
		delete i;
	}
}

void Text::setFont(gdl::Texture *font)
{
	this->font = font;
}
