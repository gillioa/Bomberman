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
#include "RandomMapGenerator.hpp"

class Menu : public AMenu
{
  public:

    enum ReturnCode
    {
      CONTINUECODE = 0,
      PLAYCODE,
      QUITCODE
    };

  Menu(gdl::SdlContext &context);
  Menu(gdl::SdlContext &context, gdl::BasicShader &shader);

    bool initialize();

    ReturnCode updateCode();
    bool update();

    virtual ~Menu();

    void startOptionJoueur();
    void startOptionPartie();
    void startChargerPartie();
    void startMenuScore();
    void startSubMenu(AMenu &menu);
    void resetCamera();

  private:
    gdl::Input input;
    std::map<int, void (Menu::*)()> ptr;

    Core *core;
    RandomMapGenerator *mapGen;
};
