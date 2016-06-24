#include	<iostream>
#include	"Cube.hpp"

Cube::Cube(double width, gdl::Texture *text)
{
  this->texture = text;
  this->width = width;
}

Cube::~Cube()
{
}

Cube::Cube(Cube *other) {
  this->width = other->getWidth();
  this->texture = other->getTexture();
  this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
  this->speed = 10.0f;
  this->hasColor = false;
}

gdl::Geometry	*Cube::createCube(float width, float begHeight)
{
  gdl::Geometry *geometry = new gdl::Geometry; 
  
  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3((width), begHeight + 0.0, (width)));
  geometry->pushVertex(glm::vec3((width), begHeight + (width), (width)));
  geometry->pushVertex(glm::vec3(0.0, begHeight + (width), (width)));
  geometry->pushVertex(glm::vec3(0.0, begHeight + 0.0, (width)));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3(width, begHeight + 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, begHeight + 0.0, 0.0));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3(width, begHeight + 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(width, begHeight + width, width));
  geometry->pushVertex(glm::vec3(width, begHeight + 0.0, width));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3(0.0,begHeight +  0.0, width));
  geometry->pushVertex(glm::vec3(0.0, begHeight + width, width));
  geometry->pushVertex(glm::vec3(0.0, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, begHeight + 0.0, 0.0));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  
  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3(width, begHeight + width, width));
  geometry->pushVertex(glm::vec3(width, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, begHeight + width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, begHeight + width, width));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(glm::vec4(1, 1, 1, 1));
  geometry->pushVertex(glm::vec3(width, begHeight + 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, begHeight + 0.0, width));
  geometry->pushVertex(glm::vec3(0.0, begHeight + 0.0, width));
  geometry->pushVertex(glm::vec3(0.0, begHeight + 0.0, 0.0));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  geometry->build();
  return (geometry);  
}

gdl::Geometry	*Cube::createCube(float width, const glm::vec4 &color)
{
  gdl::Geometry *geometry = new gdl::Geometry; 
  
  geometry->setColor(color);
  geometry->pushVertex(glm::vec3((width), 0.0, (width)));
  geometry->pushVertex(glm::vec3((width), (width), (width)));
  geometry->pushVertex(glm::vec3(0.0, (width), (width)));
  geometry->pushVertex(glm::vec3(0.0, 0.0, (width)));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(width, 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, 0.0, 0.0));

  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(width, 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, width, 0.0));
  geometry->pushVertex(glm::vec3(width, width, width));
  geometry->pushVertex(glm::vec3(width, 0.0, width));

  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(0.0, 0.0, width));
  geometry->pushVertex(glm::vec3(0.0, width, width));
  geometry->pushVertex(glm::vec3(0.0, width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, 0.0, 0.0));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  
  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(width, width, width));
  geometry->pushVertex(glm::vec3(width, width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, width, 0.0));
  geometry->pushVertex(glm::vec3(0.0, width, width));

  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));

  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(width, 0.0, 0.0));
  geometry->pushVertex(glm::vec3(width, 0.0, width));
  geometry->pushVertex(glm::vec3(0.0, 0.0, width));
  geometry->pushVertex(glm::vec3(0.0, 0.0, 0.0));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  geometry->build();
  return (geometry);
}

bool Cube::initialize(gdl::Geometry *geo)
{
  this->speed = 10.0f;
  this->geometry = geo;
  return true;
}

void Cube::update(gdl::Clock const &, const gdl::Input &)
{
}

void Cube::draw(gdl::AShader &s, gdl::Clock const &)
{
  this->texture->bind();
  this->geometry->draw(s, getTransformation(), GL_QUADS);
}

void	Cube::moveOf(int newX, int newY)
{
  newX += 1;
  newY += 1;
  int	x = newX - this->pos.x;
  int	y = newY - this->pos.y;
  
  this->translate(glm::vec3(-x, 0, -y) * static_cast<float>(this->width));
  this->pos.x = newX;
  this->pos.y = newY;
}

void	Cube::moveOf(float newX, float newY)
{
  newX += 1;
  newY += 1;
  float	x = newX - this->pos.x;
  float y = newY - this->pos.y;
  
  this->translate(glm::vec3(-x, 0.0f, -y) * static_cast<float>(this->width));
  this->pos.x = newX;
  this->pos.y = newY;
}
