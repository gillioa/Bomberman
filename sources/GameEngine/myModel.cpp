//
// myModel.cpp for Bomberman in /home/courtu_r/tp/GDL
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Fri May 23 12:58:37 2014 courtu_r
// Last update Sun Jun 15 19:07:43 2014 courtu_r
//

#include <cstdio>
#include "myModel.hpp"

MyModel::MyModel(glm::mat4 matrix, int, float scale, gdl::Model *model)
{ 
  this->model = model;
  this->matrix = matrix;
  this->currAngle = static_cast<float>(GRight);
  this->scale = scale;
  this->speed = 10.0;
  this->moveVec[GDown] = glm::vec3(0, 0, -1);
  this->moveVec[GUp] = glm::vec3(0, 0, 1);
  this->moveVec[GLeft] = glm::vec3(1, 0, 0);
  this->moveVec[GRight] = glm::vec3(-1, 0, 0);
  this->moveFuncs[UP] = &MyModel::moveUp;
  this->moveFuncs[DOWN] = &MyModel::moveDown;
  this->moveFuncs[LEFT] = &MyModel::moveLeft;
  this->moveFuncs[RIGHT] = &MyModel::moveRight;
}

bool		MyModel::initialize()
{
  return (true);
}

glm::mat4	MyModel::getTransfo() const
{
  glm::mat4 transform(1);
  
  transform = glm::translate(transform, this->pos);
  transform = glm::rotate(transform, currAngle, glm::vec3(0, 1, 0));
  transform = glm::scale(transform, glm::vec3(this->scale, this->scale, this->scale));
  return (transform);
}

void	MyModel::orientModel(dir direction)
{
  this->currAngle = static_cast<float>(direction);
}

void	MyModel::draw(gdl::AShader &s, gdl::Clock const &)
{
  this->model->draw(s, getTransfo(), 0.01666f);
}

void	MyModel::moveLeft(gdl::Clock const &c)
{
  this->currAngle = GLeft;
  this->pos += this->moveVec[static_cast<dir>(this->currAngle)] * this->speed * static_cast<float>(c.getElapsed());
}

void	MyModel::moveDown(gdl::Clock const &c)
{
  this->currAngle = GDown;
  this->pos += this->moveVec[static_cast<dir>(this->currAngle)] * this->speed * static_cast<float>(c.getElapsed());
}

void	MyModel::moveRight(gdl::Clock const &c)
{
  this->currAngle = GRight;
  this->pos += this->moveVec[static_cast<dir>(this->currAngle)] * this->speed * static_cast<float>(c.getElapsed());
}

void	MyModel::moveUp(gdl::Clock const &c)
{
  this->currAngle = GUp;
  this->pos += this->moveVec[static_cast<dir>(this->currAngle)] * this->speed * static_cast<float>(c.getElapsed());
}

void	MyModel::update(gdl::Clock const &c, Action dir)
{
  (this->*moveFuncs[dir])(c);
}

void	MyModel::setAngle(dir angle)
{
  this->currAngle = angle;
}

const glm::vec3	MyModel::getPosition() const
{
  return (this->pos);
}

MyModel	&MyModel::setPos(float x, float y)
{
  this->pos.x = (-x);
  this->pos.z = -y;
  return (*this);
}
