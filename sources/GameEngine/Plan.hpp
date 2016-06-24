#ifndef _PLAN_HPP_
#define _PLAN_HPP_

#include <Texture.hh>
#include <Geometry.hh>
#include "AObjectGraph.hpp"

class Plan : public AObjectGraph
{
private:
  double		width;
  double		height;
  double		yCoord;
  gdl::Texture		*texture;
  gdl::Geometry		*geometry;
  float			speed;
  glm::vec3		pos;
public:
  Plan(double, double, double, gdl::Texture *);
  virtual ~Plan();
  virtual bool initialize(gdl::Geometry *);
  static gdl::Geometry	*createPlan(float, float, float, const glm::vec4 &);
  static gdl::Geometry	*createPlan(float, float, float);
  virtual void update(gdl::Clock const &, gdl::Input &);
  virtual void draw(gdl::AShader &, gdl::Clock const &);
  void	moveOf(float,float);
  void moveOf(int, int);
};

#endif
