#pragma once

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
#include "image.hh"
#include "AMenu.hh"
#include "Name.hh"
#include <list>
#include "scores.hpp"
#include "text.hh"

class MenuScore : public AMenu
{
  public:

    MenuScore(gdl::SdlContext &context, gdl::BasicShader &shader, gdl::Input &input);

    bool initialize();
    bool update();

    void draw();

  private:
    gdl::Input &input;
    Scores s;
    std::vector<Text> scoresText;

};


