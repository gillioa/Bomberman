#ifndef _CUBE_HPP_
#define _CUBE_HPP_

#include <Texture.hh>
#include <Geometry.hh>
#include "AObjectGraph.hpp"

typedef unsigned int Uint;

class Cube : public AObjectGraph
{
private:
  double		width;
  std::string		textFile;
  gdl::Texture		*texture;
  gdl::Geometry		*geometry;
  glm::vec3		pos;
  float			speed;
  glm::vec4		color;
  bool			hasColor;
public:
  static gdl::Geometry	*createCube(float width, const glm::vec4 &);
  static gdl::Geometry	*createCube(float width, float);
  
  Cube(Cube *other); 
  Cube(double width, gdl::Texture *texture);
  //Cube(double width, gdl::Texture *texture, const glm::vec4 &color);
  virtual ~Cube();
  virtual bool initialize(gdl::Geometry *geo);
  virtual void update(gdl::Clock const &c, gdl::Input const &i);
  virtual void draw(gdl::AShader &s, gdl::Clock const &c);
  virtual void moveOf(int x, int y);
  virtual void moveOf(float x, float y);
  double	getWidth() const {
    return (this->width);
  };
  gdl::Texture	*getTexture() {
    return (this->texture);
  };
  gdl::Geometry	*getGeometry() const {
    return (this->geometry);
  };
};

#endif
