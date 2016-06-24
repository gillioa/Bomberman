#include	"Plan.hpp"
#include <iostream>

Plan::Plan(double height, double width, double yCoord, gdl::Texture *texture)
{
  this->texture = texture;
  this->height =  height;
  this->width = width;
  this->yCoord = yCoord;
  this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
}

Plan::~Plan()
{
}

gdl::Geometry	*Plan::createPlan(float width, float height, float depth, const glm::vec4 &color)
{
  gdl::Geometry	*geometry = new gdl::Geometry();
  
  if (geometry == 0)
    return (0);
  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(0.0, height, 0.0));
  geometry->pushVertex(glm::vec3(-depth, height, 0.0));
  geometry->pushVertex(glm::vec3(-depth, height, -width));
  geometry->pushVertex(glm::vec3(0.0, height, -width));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  geometry->build();
  return (geometry);
}

gdl::Geometry	*Plan::createPlan(float width, float height, float depth)
{
  gdl::Geometry	*geometry = new gdl::Geometry();
  
  if (geometry == 0)
    return (0);
  geometry->pushVertex(glm::vec3(0.0, height, 0.0));
  geometry->pushVertex(glm::vec3(-depth, height, 0.0));
  geometry->pushVertex(glm::vec3(-depth, height, -width));
  geometry->pushVertex(glm::vec3(0.0, height, -width));
  geometry->pushUv(glm::vec2(0.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 0.0f));
  geometry->pushUv(glm::vec2(1.0f, 1.0f));
  geometry->pushUv(glm::vec2(0.0f, 1.0f));
  geometry->build();
  return (geometry);
}

bool Plan::initialize(gdl::Geometry *geo)
{
  this->speed = 10.0f;
  this->geometry = geo;
  return true;
}

void Plan::update(gdl::Clock const &c, gdl::Input &i)
{
  if (i.getKey(SDLK_UP))
    translate(glm::vec3(0, 0, -1) * static_cast<float>(c.getElapsed()) * this->speed);
  if (i.getKey(SDLK_DOWN))
    translate(glm::vec3(0, 0, 1) * static_cast<float>(c.getElapsed()) * this->speed);
  if (i.getKey(SDLK_LEFT))
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
  if (i.getKey(SDLK_RIGHT))
    translate(glm::vec3(1, 0, 0) * static_cast<float>(c.getElapsed()) * this->speed);
}

void Plan::moveOf(float newX, float newY)
{
  float	x = newX - this->pos.x;
  float y = newY - this->pos.y;
  
  this->translate(glm::vec3(-x, 0.0f, -y) * 1.0f);
  this->pos.x = newX;
  this->pos.y = newY;
}

void Plan::moveOf(int newX, int newY)
{
  int	x = newX - this->pos.x;
  int y = newY - this->pos.y;
  
  this->translate(glm::vec3(-x, 0.0f, -y) * 1.0f);
  this->pos.x = newX;
  this->pos.y = newY;
}

void Plan::draw(gdl::AShader &s, gdl::Clock const &)
{
  this->texture->bind();
  this->geometry->draw(s, getTransformation(), GL_QUADS);
}
