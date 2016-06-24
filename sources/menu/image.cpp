#include "image.hh"

Image::Image() :
  gdl::Texture(),
  geo(0),
  canDraw(false)
{
}

Image::Image(const std::string &texturePath) :
  gdl::Texture(),
  geo(0),
  canDraw(false)
{
  this->load(texturePath);
}


void Image::constructFor2d(int x, int y)
{

  this->geo = new gdl::Geometry;

  this->x = x;
  this->y = y;
  this->geo->setColor(glm::vec4(1, 1, 1, 1));

  this->geo->pushVertex(glm::vec3(x, y, 0));
  this->geo->pushVertex(glm::vec3(this->getWidth() + x, y, 0));
  this->geo->pushVertex(glm::vec3(this->getWidth() + x, this->getHeight() + y, 0));
  this->geo->pushVertex(glm::vec3(x, this->getHeight() + y, 0));

  this->geo->pushUv(glm::vec2(0.0f, 1.0f));
  this->geo->pushUv(glm::vec2(1.0f, 1.0f));
  this->geo->pushUv(glm::vec2(1.0f, 0.0f));
  this->geo->pushUv(glm::vec2(0.0f, 0.0f));

  this->geo->build();

  this->canDraw = true;
}

void Image::reset() {
  if (this->geo)
    delete this->geo;
}

void Image::draw(gdl::AShader &shader, const glm::vec3 &scale)
{
  glm::mat4 transform(1);

  assert(canDraw == true);
  transform = glm::scale(transform, scale);
  shader.bind();
  this->bind();
  this->geo->draw(shader, transform, GL_QUADS);
}

Image::~Image()
{
  delete this->geo;
}

bool Image::getHover() const
{
  return this->isHover;
}

Image &Image::setHover(bool hover)
{
  this->isHover = hover;
  return *this;
}

glm::ivec2 Image::getPosition() const
{
  return glm::ivec2(this->x, this->y);
}

Image &Image::updateHover(const glm::ivec2 &mousePos){
  if ((mousePos.x > this->x)
    && (mousePos.x < (this->x + static_cast<int>(this->getWidth())))
    && (mousePos.y > this->y)
    && (mousePos.y < (this->y + static_cast<int>(this->getHeight())))){
    this->setHover(true);
  }else{
    this->setHover(false);
  }
  return *this;
}
