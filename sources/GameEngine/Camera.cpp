#include "Camera.hpp"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void	Camera::initialize(float w, float h)
{
  this->projection = glm::perspective(60.0f, w / h, 0.1f, 100.0f);
}

void	Camera::look(const glm::vec3& target)
{
  this->transformation = glm::lookAt(glm::vec3(target.x, 20, target.z - 5),
				     glm::vec3(target.x, target.y, target.z),
				     glm::vec3(0, 0, 1));
}

const glm::mat4&	Camera::getProjection(void) const
{
  return this->projection;
}

const glm::mat4&	Camera::getTransformation(void) const
{
  return this->transformation;
}

void	Camera::translate(const glm::vec3 &target)
{
  this->transformation = glm::translate(this->transformation, target);
  //this->transformation.translate(target);
}

void	Camera::disableSplit(float w, float h)
{
  this->projection = glm::perspective(60.0f, w / h, 0.1f, 100.0f);
}
