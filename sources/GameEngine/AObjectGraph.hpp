#ifndef _AOBJECT_HPP_
#define _AOBJECT_HPP_

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AObjectGraph
{
private:
  glm::vec3	position;
  glm::vec3	rotation;
  glm::vec3	scal;
  glm::vec3	pos;
public:
  AObjectGraph(): position(0, 0, 0), rotation(0, 0, 0),	scal(1, 1, 1) {
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
  }
  virtual ~AObjectGraph() {}
  virtual bool		initialize() { return true; } 
  virtual void		moveOf(int, int) {};
  virtual void		moveOf(float newX, float newY) {
    float	x = newX - this->pos.x;
    float y = newY - this->pos.y;
    
    this->translate(glm::vec3(-x, 0.0f, -y) * 1.0f);
    this->pos.x = newX;
    this->pos.y = newY;
  };
  virtual void		update(gdl::Clock const &, gdl::Input const &) { }
  virtual void		draw(gdl::AShader &, gdl::Clock const &) = 0;
  void			translate(glm::vec3 const &v) { this->position += v; }
  void			rotate(glm::vec3 const &axis, float angle) { this->rotation += axis * angle; }
  void			scale(glm::vec3 const &s) { this->scal *= s; }
  const	glm::vec3	getPosition(void) const { return position; }
  const	glm::vec3	getRotation(void) const { return rotation; }
  const glm::vec3	getScal(void) const { return scal; }
  glm::mat4		getTransformation() const
  {
    glm::mat4	transform(1);
    transform = glm::rotate(transform, this->rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, this->rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, this->rotation.z, glm::vec3(0, 0, 1));
    transform = glm::translate(transform, this->position);
    transform = glm::scale(transform, this->scal);
    return (transform);
  }
  int			x;
  int			y;
};

#endif
