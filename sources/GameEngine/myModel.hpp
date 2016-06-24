//
// myModel.hpp for Bomberman in /home/courtu_r/tp/GDL
// 
// Made by courtu_r
// Login   <courtu_r@epitech.net>
// 
// Started on  Thu May 22 14:26:40 2014 courtu_r
// Last update Sun Jun 15 19:07:44 2014 courtu_r
//

#include <iostream>
#include <vector>
#include "Model.hh"
#include "AObjectGraph.hpp"

#ifndef MYMODEL
# define MYMODEL

typedef unsigned int Uint;

enum Action
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SETBOMB
  };

enum dir
  {
    GLeft = 90,
    GDown = 180,
    GRight = 270,
    GUp = 0
  };

class MyModel;

typedef void (MyModel::*moves)(gdl::Clock const &);

class	MyModel : public AObjectGraph
{
  std::vector<moves>		tests;
  std::map<Action, moves>		moveFuncs;
  std::map<dir, glm::vec3>	moveVec;
  glm::mat4	matrix;
  gdl::Model		*model;
  glm::vec3		pos;
  glm::vec3		truePos;
  float			rotX;
  float			rotY;
  float			rotZ;
  float			currAngle;
  float			scale;
  float			speed;
  void			moveLeft(gdl::Clock const &c);
  void			moveDown(gdl::Clock const &c);
  void			moveRight(gdl::Clock const &c);
  void			moveUp(gdl::Clock const &c);
public:
  MyModel(glm::mat4 matrix, int num, float scale, gdl::Model *model);
  glm::mat4	getTransfo() const;
  void	draw(gdl::AShader &s, gdl::Clock const &c);
  void	update(gdl::Clock const &c, Action dir);
  void	orientModel(dir);
  bool	initialize();
  const glm::vec3	getPosition() const;
  MyModel	&setPos(float , float );
  void	setAngle(dir angle);
  gdl::Model	*getModel() {
    return (this->model);
  };
};

#endif /*MYMODEL*/
