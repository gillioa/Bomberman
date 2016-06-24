#ifndef IMAGE_HH
#define IMAGE_HH

#include <OpenGL.hh>
#include <Game.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Model.hh>
#include <iostream>
#include <BasicShader.hh>
#include <Texture.hh>
#include <Geometry.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Image : public gdl::Texture {
public:

    Image();
    Image(const std::string&);

    virtual void constructFor2d(int x, int y);
    virtual void draw(gdl::AShader &shader, const glm::vec3 &scale = glm::vec3(1, 1, 1));

    bool getHover() const;

    Image &setHover(bool hover);

    void reset();

    virtual Image &updateHover(const glm::ivec2 &mousePos);

    virtual glm::ivec2 getPosition() const;

    virtual ~Image();

private:

    gdl::Geometry *geo;

protected:
  bool canDraw;
  bool isHover;
  int x;
  int y;

};

#endif
