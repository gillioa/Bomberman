#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef unsigned int		Uint;

class Camera
{
private:
  glm::mat4		projection;
  glm::mat4		transformation;
public:
  Camera();
  virtual		~Camera();
  void			initialize(float w, float h);
  void			look(const glm::vec3& target);
  const glm::mat4&	getProjection(void) const;
  const glm::mat4&	getTransformation(void) const;
  void			translate(const glm::vec3 &);
  void			disableSplit(float, float);
};

#endif
