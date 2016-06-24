
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec4 getColor(unsigned int num, unsigned int total) {
  unsigned int	ec1 = 2 * (total / (num + 1) + 1 + (total % (num + 1)) * 55) % 0xFF;
  unsigned int	ec2 = 3 * (ec1 + total % (num + ((num + 1) % 8))) % 0xFF;
  unsigned int	ec3 = 4 * (ec2 + total / (num + (total / 2) + 1)) % 0xFF;
  return (glm::vec4(ec1 / 255.0, ec2 / 255.0, ec3 / 255.0, 1));
}
