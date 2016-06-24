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
#include "Core.hpp"
#include "Name.hh"
#include "RandomMapGenerator.hpp"

class InGame : public AMenu
{
  public:

    enum ReturnCode
    {
      CONTINUECODE = 0,
      PLAYCODE,
      QUITCODE
    };

  InGame(gdl::SdlContext &context, gdl::BasicShader &shader, Core &core, gdl::Input &input);

    bool initialize();

    ReturnCode updateCode();
    bool update();

    virtual ~InGame();
  private:
    Name name;

    Core &core;
    gdl::Input &input;
};
